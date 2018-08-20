
#include "DSP2833x_Device.h"    
#include "SysCtl_AllHeaders.h"


union TranFU
{
	float Float_data;
	Uint32  Long_data;
}TRANS_FU;
//------写内部FLASH-----------//
void MyCallbackFunction(void); 
void Example_MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);
Uint16 fWriteIntFlash(Uint16 *uBuffer,Uint16 ulength);

void WriteToFPGA(COMMUN *p);
//Uint16 CopyZoneDefaul(Uint16 StartAddr,Uint16 LEN,COMMUN *p);

/***************************公用函数****************************************************/
Uint16 GetFuncIDByte(Uint16 ucFunID);/* 获取功能码 */
Uint16 RetFuncID(Uint16 ucFunID,Uint16 ucDeviceID);/* 返回功能码 */
Uint16 GetFirstChar(Uint16 ucWord);/* 获取一个字节中的第一个字节 */
Uint16 GetLastChar(Uint16 ucWord);/* 获取一个字节中的第二个字节 */

Uint16 GetFirstChar(Uint16 ucWord)
{
    return ucWord>>8;
}
Uint16 GetLastChar(Uint16 ucWord)
{
    return ucWord&0xff;
}
Uint16 GetFuncIDByte(Uint16 ucFunID)
{
    return ucFunID>>8;
}
Uint16 RetFuncID(Uint16 ucFunID,Uint16 ucDeviceID)
{
    return (ucFunID<<8 | (ucDeviceID&0x00ff));
}

void DisplayWave(COMMUN *p)
{

	    /* 一个波形数据为4字节,使用了相连的两个地址保存 */
		*(pWaveParamStart)=p->DSP_RAM[p->CHANLEADDR[0]>>1];           ///向数组CHANLE0内存CHANLEADDR[0]对应的RAM区数据
		*(pWaveParamStart+1)=p->DSP_RAM[(p->CHANLEADDR[0]>>1)+1];

		*(pWaveParamStart+2)=p->DSP_RAM[p->CHANLEADDR[1]>>1];          ///同上
		*(pWaveParamStart+3)=p->DSP_RAM[(p->CHANLEADDR[1]>>1)+1];

		*(pWaveParamStart+4)=p->DSP_RAM[p->CHANLEADDR[2]>>1];
		*(pWaveParamStart+5)=p->DSP_RAM[(p->CHANLEADDR[2]>>1)+1];

		*(pWaveParamStart+6)=p->DSP_RAM[p->CHANLEADDR[3]>>1];
		*(pWaveParamStart+7)=p->DSP_RAM[(p->CHANLEADDR[3]>>1)+1];

		*(pWaveParamStart+8)=p->DSP_RAM[p->CHANLEADDR[4]>>1];
		*(pWaveParamStart+9)=p->DSP_RAM[(p->CHANLEADDR[4]>>1)+1];

		*(pWaveParamStart+10)=p->DSP_RAM[p->CHANLEADDR[5]>>1];
		*(pWaveParamStart+11)=p->DSP_RAM[(p->CHANLEADDR[5]>>1)+1];

}

void FaultWaveMemory(COMMUN *p)
{
	Uint16 i,value;   
	float32 *address;
	/* 记录上次故障信息 ，上次故障还没有传完，不允许记录新的故障信息*/	
	if (1 == p->uFaultLStop)
	{
		return;
	}	
	
	/* 无故障，循环记录前400个点的信息 */	
	if (0 == p->uFaultFlag)
	{
		for(i=0;i<16;i++)
		{
			address=(float32*)(p->DSP_RAM+(p->uFaultCHADDR[i]>>1));
			value=*address;
			*(p->pFaultWbuf+1000*i+p->uFaultMNum)=*(p->DSP_RAM+(value>>1));
			*(p->pFaultWbuf+1000*i+p->uFaultMNum+1)=*(p->DSP_RAM+(value>>1)+1);
		}
		p->uFaultMNum+=2;
		if(p->uFaultMNum>798) p->uFaultMNum=0;
	}	
 	else
	{
		for(i=0;i<16;i++)
		{
			address=(float32*)(p->DSP_RAM+(p->uFaultCHADDR[i]>>1));
			value=*address;
			*(p->pFaultWbuf+800+1000*i+p->uFaultANum)=*(p->DSP_RAM+(value>>1));
			*(p->pFaultWbuf+800+1000*i+p->uFaultANum+1)=*(p->DSP_RAM+(value>>1)+1);
		}
		p->uFaultANum+=2;
		if(p->uFaultANum>198) 
		{
			p->uFaultANum=0;
			p->uFaultLStop=1;
		}
	}

}

/*初始化通讯功能函数*/
void InitCommun(COMMUN *p)
{
	p->uFaultMNum=0;
	p->uFaultANum=0;
	p->uFaultLStop=0;        ////清除停止缓冲标志
	p->uFaultFlag=0;         ////清除故障标志


    /* 波形读写指针 */
    p->uWaveWriePos = 0;
    p->uWaveReadPos = 0;
    p->WavePack = 0;
    p->ucMaxWaveID=0;
}

/*读FPGA内数据*/
void ReadFromFPGA(COMMUN *p)
{
	Uint16 ReadNum,ByteNum=0,HandshakeCode;
	HandshakeCode=*(p->ARMHandshakeWord)&0x00ff;    ////读握手字

	switch(HandshakeCode)                          ////根据握手字执行响应功能
	{
	case READ_PARAM_RTS:     /////读参数
		for(ReadNum=0;ReadNum<3;ReadNum++)
		{
			p->ReadFpgaS2[ReadNum]=*(p->ReceiveStartAdd+ReadNum);
		}
		p->WaveINTReadNum=0;
		
		WriteToFPGA(p);
		break;
	case WRITE_PARAM_RTS:    ////写参数,数据长度不包括帧头帧尾
	    for(ReadNum=0;ReadNum<3;ReadNum++)
		{
			p->ReadFpgaS2[ReadNum]=*(p->ReceiveStartAdd+ReadNum);
		}
		ByteNum= p->ReadFpgaS2[2]/2;
		for(ReadNum=3;ReadNum<ByteNum + 3;ReadNum++)
		{
			p->ReadFpgaS2[ReadNum] = *(p->ReceiveStartAdd+ReadNum);
		}
		p->WaveINTReadNum=0;
		WriteToFPGA(p);
		
		//FPGA_SetCarrier(p->ReadFpgaS2[1],p->ReadFpgaS2[2]);
		break;
	case RESTORE_DEF_RTS:    ////恢复出厂设置
		for(ReadNum=0;ReadNum<2;ReadNum++)
		{
			p->ReadFpgaS2[ReadNum]=*(p->ReceiveStartAdd+ReadNum);
		}
		
		*(p->DSPtoARMStartAdd)=RetFuncID(RESTORE_DEF_ACK,p->ReadFpgaS2[0]);
        /* 起始地址 */
        *(p->DSPtoARMStartAdd+1)=0;
        /* 长度 */
        *(p->DSPtoARMStartAdd+2)=2;
		/* 默认可以读写成功 */
		* (p->DSPtoARMStartAdd+3)=0x01;
		//* (p->DSPtoARMStartAdd+3)=0x0f;
		*(p->DSPHandshakeWord)=RESTORE_DEF_ACK;
		if(RESTORE_DEF_RTS == GetFuncIDByte(p->ReadFpgaS2[0]))
		//uReDefSuc=CopyZoneDefaul(0,1000,p);
//		CopyZoneDefaul(0,1000,p);
		break;
	case CHANGE_DEF_RTS:   ////变更出厂设置，将下载的参数写入到出厂区flash
        for(ReadNum=0;ReadNum<3;ReadNum++)
		{
			p->ReadFpgaS2[ReadNum]=*(p->ReceiveStartAdd+ReadNum);
		}
		p->ReadFpgaS2[3] = 0;
		ByteNum= p->ReadFpgaS2[2]/2;
		for(ReadNum=4;ReadNum<ByteNum + 3;ReadNum++)
		{
			p->ReadFpgaS2[ReadNum] = *(p->ReceiveStartAdd+ReadNum);
		}
        WriteToFPGA(p);
		break;
	case WRITE_CHANNEL_RTS:    /* 写通道信息 */
		for(ReadNum=0;ReadNum<9;ReadNum++)   
		{
			p->ReadFpgaS2[ReadNum]=*(p->ReceiveStartAdd+ReadNum);
		}
        WriteToFPGA(p);
		p->uSampRate=p->ReadFpgaS2[8];     ////采样率
        /*  系统采样率为2K，所以波形采样率最大为2K，此处计算多少个采样周期去缓冲波形 */
        p->uSampRate=2000/p->uSampRate;                        
        p->uSampIntervalbuf=p->uSampRate;
		p->uSampInterval=p->uSampIntervalbuf;
		for(ReadNum=0;ReadNum<6;ReadNum++)   
		{ 
			p->CHANLEADDR[ReadNum]=p->ReadFpgaS2[ReadNum+2];
		}
       	* (p->DSPtoARMStartAdd)=RetFuncID(WRITE_CHANNEL_ACK,p->ReadFpgaS2[0]);
        * (p->DSPtoARMStartAdd+1)=0;
		*(p->DSPHandshakeWord)=WRITE_CHANNEL_ACK;
		break;
    case READ_WAVE_RTS:    ///读波形数据
		break;    
	case READ_FAULTWAVE_RTS:     /////读故障波形 ，先读取故障信息，再读取故障波形
		break;
	default:

		break;
	}
    
	*(p->ARMHandshakeWord) = 0;
}

/*根据下发命令，返回数据帧*/
void WriteToFPGA(COMMUN *p)
{
	Uint16 ReadNum,ByteNum=0,DataNum =0;
	Uint16 StartAddress; 

 //   static Uint16 bHasReadWave = I2C_FALSE;
 //   static Uint16 uLastTimeStamp = 0;
 //   Uint16 uRequireSendStamp =0;
	switch(GetFirstChar(p->ReadFpgaS2[0]))
	{
	case READ_PARAM_RTS://///读参数
		StartAddress=p->ReadFpgaS2[1]/2;
		ByteNum= p->ReadFpgaS2[2]/2;
        /* 功能码 */
        *(p->DSPtoARMStartAdd) = RetFuncID(READ_PARAM_ACK,p->ReadFpgaS2[0]);
        *(p->DSPtoARMStartAdd + 1)=StartAddress*2;
        *(p->DSPtoARMStartAdd + 2)=ByteNum*2;
        
		for(ReadNum=0;ReadNum<ByteNum;ReadNum++)      ////根据地址返回RAM内数据
		{
			*(p->DSPtoARMStartAdd+3+ReadNum)= *(p->DSP_RAM+StartAddress+ReadNum);
		}
		*(p->DSPHandshakeWord)=READ_PARAM_ACK;	
		break;
	case WRITE_PARAM_RTS:
		StartAddress=p->ReadFpgaS2[1]/2;
		ByteNum=p->ReadFpgaS2[2]/2;
		for(ReadNum=0;ReadNum<ByteNum;ReadNum++)
		{
			* (p->DSP_RAM+StartAddress+ReadNum)= p->ReadFpgaS2[3+ReadNum];
		}
        /* 返回内容 */
        *(p->DSPtoARMStartAdd) = RetFuncID(WRITE_PARAM_ACK,p->ReadFpgaS2[0]);
        *(p->DSPtoARMStartAdd + 1)=StartAddress*2;
        *(p->DSPtoARMStartAdd + 2)=ByteNum*2;
		*(p->DSPHandshakeWord)=WRITE_PARAM_ACK;

	    //载波频率更新
	    if(StartAddress == 766 //开关频率
	    || StartAddress == 768 //斩波频率
		|| StartAddress == 770 //斩波占空比
		|| StartAddress == 772 //DSP主中断频率倍数
		|| StartAddress == 774 //光纤斩波使能
		|| (StartAddress == 0 && ByteNum == 1000) //初始化，需要设置
		)  //1532/2=766
	    {
	    	SysConTest.Enable = 1;
	    }


		break;
    case CHANGE_DEF_RTS:  
    	StartAddress=p->ReadFpgaS2[1]/2; 
        DataNum= p->ReadFpgaS2[2]/4;
        for(ReadNum=0;ReadNum<DataNum;ReadNum++)
		{	
	// 	    Write_MR25H40_nDW(StartAddress+ReadNum*2,(Uint32*)(p->ReadFpgaS2+ReadNum*2+4),1);
		}

		* (p->DSPtoARMStartAdd)=RetFuncID(CHANGE_DEF_ACK,p->ReadFpgaS2[0]);
		/* 起始地址 */
		* (p->DSPtoARMStartAdd+1)=0x0;
        /* 长度 */
        * (p->DSPtoARMStartAdd+2)=0x2;
        /* 成功标志 */
        * (p->DSPtoARMStartAdd+3)=0x1;
		
		*(p->DSPHandshakeWord)=CHANGE_DEF_ACK;
        break;
    case WRITE_CHANNEL_RTS:    /* 写通道信息 */
		p->uSampRate=p->ReadFpgaS2[8];     ////采样率
        /* 系统采样率为2K，所以波形采样率最大为2K，此处计算多少个采样周期去缓冲波形 */
        p->uSampRate=2000/p->uSampRate;                        
        p->uSampIntervalbuf=p->uSampRate;
		p->uSampInterval=p->uSampIntervalbuf;
		for(ReadNum=0;ReadNum<6;ReadNum++)   
		{ 
			p->CHANLEADDR[ReadNum]=p->ReadFpgaS2[ReadNum+2];
		}
       	* (p->DSPtoARMStartAdd)=RetFuncID(WRITE_CHANNEL_ACK,p->ReadFpgaS2[0]);
        * (p->DSPtoARMStartAdd+1)=0;
		*(p->DSPHandshakeWord)=WRITE_CHANNEL_ACK;
		break;    
	default:
		break;
	}
}

void InitWrFlash(Uint16 FlashStAddr,Uint32 *StartAddr,Uint16 LEN)
{
	Uint16 ulen;
	for(ulen=0;ulen<LEN;ulen++)
	{
	//	Write_MR25H40_nDW(FlashStAddr+ulen*2,StartAddr+ulen,1);
	}
}

void InitWrFlashF32(Uint16 FlashStAddr,float32 *StartAddr,Uint16 LEN)
{
	Uint16 ulen;
	Uint32 u2temp;

	for(ulen=0;ulen<LEN;ulen++)
	{	
		TRANS_FU.Float_data = *(StartAddr + ulen);
		u2temp = TRANS_FU.Long_data;
		TRANS_FU.Long_data = (TRANS_FU.Long_data<<16)|(u2temp>>16);
	//	Write_MR25H40_nDW(FlashStAddr+ulen*2,&TRANS_FU.Long_data,1);
	}
}



//===========================================================================
// No more.


