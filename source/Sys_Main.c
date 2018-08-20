/*
//========================================================
// 
// 文件名:	Main.c
//
// 用途:	系统主函数
//
*/
//==========================================================
#include "DSP2833x_Device.h"     // DSP2833x头文件
#include "SysCtl_AllHeaders.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "DSP2833x_Examples.h"



extern void fnSysParamterRef(void);
// Prototype statements for functions found within this file.
__interrupt void epwm1_isr(void);
__interrupt void epwm2_isr(void);
__interrupt void epwm3_isr(void);
__interrupt void epwm4_isr(void);
//=========================================================

void DISABLE_PWM(void)
{
	EALLOW;
	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
	EDIS;
	EPwm1Regs.AQCSFRC.all = 5; //0101 A1B1 enforce to low constant
	EPwm2Regs.AQCSFRC.all = 5;
	EPwm3Regs.AQCSFRC.all = 5;
	EPwm4Regs.AQCSFRC.all = 5;
	EPwm1Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm2Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm3Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm4Regs.DBCTL.bit.OUT_MODE = 0;
}

void ENABLE_PWM(void)
{
	EALLOW;
	GpioDataRegs.GPASET.bit.GPIO1 = 1;
	EDIS;
	EPwm1Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm2Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm3Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm4Regs.DBCTL.bit.OUT_MODE = 0;
	EPwm1Regs.AQCSFRC.all = 0xF;
	EPwm2Regs.AQCSFRC.all = 0xF;
	EPwm3Regs.AQCSFRC.all = 0xF;
	EPwm4Regs.AQCSFRC.all = 0xF;
}

void main(void)
{
//	Uint16 i;

	DINT;//关中断
	                       //
	fnSysPeripheralInit();//系统外设初始,化DSP2833x_SysPerInit.c

	CpuTimer0Regs.PRD.all = 75000000;
	CpuTimer0Regs.TPR.all = 1;
	CpuTimer0Regs.TPRH.all = 0;
	CpuTimer0Regs.TCR.bit.TSS  = 1;   //Stop Timer0 for now
	
	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.EPWM1_INT = &epwm1_isr;
	PieVectTable.EPWM2_INT = &epwm2_isr;
	PieVectTable.EPWM3_INT = &epwm3_isr;
	PieVectTable.EPWM4_INT = &epwm4_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers
	
	fnSysHMICommInit();//HMI初始化

	fnSystemInitParam();//系统参数初始化

	//*sInComm.DSPHandshakeWord = (Uint16)0xAA55;

	fnEnableInterrupts();//系统开中断
	//SysMoore.SysStateNew = SystemReady;//
	//============初始化DMA=========================================
	DMAInitialize();

	DMASource1 = &DMABuf1[0];
   	DMACH1AddrConfig(DMADest1,DMASource1);
	DMACH1BurstConfig(31,2,2);         //Will set up to use 32-bit datasize, pointers are based on 16-bit words
	DMACH1TransferConfig(3,2,2);      //so need to increment by 2 to grab the correct location
	DMACH1WrapConfig(0x1000,0,0x1000,0);
    DMACH1ModeConfig(DMA_XINT1,PERINT_ENABLE,ONESHOT_ENABLE,CONT_DISABLE,SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,THIRTYTWO_BIT,CHINT_END,CHINT_ENABLE);

    //=======系统主循环===============================
 	for(;;)
 	{
		SysMoore.pfnSysMooreCal(&SysMoore);//系统状态执行
										  //
		sInComm.pfnReadFPGA(&sInComm);//HMI参数上传

		fnSysParamterRef();//非周期数据更新
    }

}
