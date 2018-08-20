// 沈阳远大电力电子
// 2013.5.24
//###########################################################################
//
// 文件名称:   COMMInterface.h
//
// 功能: 与界面通讯头文件，将函数和参数封装在同一结构体.
//
//###########################################################################
// 版本号: COMMInterface.h V1.3 $
// 制作人: 姜旭东
//###########################################################################


#ifndef COMMINTERFACE_H
#define COMMINTERFACE_H
//#include "DSP2833x_I2c_defines.h"
/***************************功能码   张永军 增加 2014.2.13****************************************************/
#define READ_PARAM_RTS      0x03 /* ARM读参数 */
#define READ_PARAM_ACK        0x93 /* 读参数响应 */
#define WRITE_PARAM_RTS     0x0a /* 写参数 */
#define WRITE_PARAM_ACK       0x9a /* 写参数响应 */
#define RESTORE_DEF_RTS     0x07 /* 恢复出厂设置 */
#define RESTORE_DEF_ACK       0x97 /* 恢复出厂设置响应 */
#define CHANGE_DEF_RTS      0x08 /* 更改出厂设置 */
#define CHANGE_DEF_ACK        0x98 /* 更改出厂设置响应 */
#define READ_WAVE_RTS       0x13 /* 读波形数据 */
#define READ_WAVE_ACK         0x83 /* 读波形数据响应 */
#define READ_FAULTINFO_RTS  0x09 /* 故障信息 */
#define READ_FAULTINFO_ACK    0x99 /* 读故障信息响应 */
#define WRITE_CHANNEL_RTS   0x10 /* 写通道信息 */
#define WRITE_CHANNEL_ACK     0x80 /* 写通道信息响应 */
#define READ_FAULTWAVE_RTS  0x14 /* 故障波形 */
#define READ_FAULTWAVE_ACK    0x84 /* 故障波形响应 */
/***************************************************************************************************************/

#define TimeStamp_Indexed  2198                       /////时间戳偏址
#define WaveData_Indexed  2200                       /////波形数据偏址	
extern void InitWrFlash(Uint16 FlashStAddr,Uint32 *StartAddr,Uint16 LEN);//////初始化FLASH存储区
extern void DSP28x_usDelay(Uint32 Count);

#define DELAY_US1(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)6.667L ) - 9.0L) / 5.0L)
/*union TranFU
{
  float Float_data;
  Uint32  Long_data;
}TRANS_FU;
*/
typedef struct {

	/*函数指针*/
	void (*pfnWaveDisplay)();       // 指向波形显示函数的指针
	void (*pfnReadFPGA)();         // 指向读FPGA函数的指针
	void (*pfnInit)();            // 指向初始化函数的指针
	void (*pfnFWaveLoad)();        // 指向故障波形缓存函数的指针

	/*输入参数*/
	Uint32 u2LineNumber;                   // 输入：生产线号
	Uint32 u2SerialNumber;                 // 输入：产品系列号
	Uint32 u2ProductNumber;                // 输入：产品版本号
	Uint32 u2FactoryNumber;                // 输入：内部编号
	Uint16 * ARMHandshakeWord;             ///// ARM向DSP发送的握手字
	Uint16 * DSPHandshakeWord;             ///// DSP向ARM发送的握手字
	Uint16 * ReceiveStartAdd;              //////接收帧起始地址
	Uint16 * DSPtoARMStartAdd;             //////DSP to arm返回帧起始地址
	Uint16 * WaveID_ADD;                  //////返回波形ID的起始地址 
	Uint16 * WaveData_StartADD;           //////波形数据起始地址
	Uint16 * DSP_RAM;                      ////DSP内部RAM起始地址
	Uint16 uFaultCHADDR[16];               ////故障通道地址
	Uint16 uFaultFlag;                     ////发生故障标志，当为1时，发生新故障，记录故障后100个点的信息
										   ////  由主控自己来消除，复位时清楚该标志
	Uint16 uFaultCode;                     ///// 故障编号
	Uint16 FlashPramaCount;               /////存储在FLASH内参数的数量
	Uint16 uDateInfoAddr;                 ////日期信息起始地址
	Uint16 uTimeInfoAddr;                 ////时间信息起始地址
	float32 *fInitFlashADD;
	Uint16 uInitFlashNum;
	Uint32 u2InitFlashFV;

	/*内部变量*/
	Uint16 ReadFpgaS2[1200];
	Uint16 WaveINTReadNum;                ///中断读波形数据次数
	Uint16 WavePack;                     ////返回波形包计数
	Uint16 uSampRate;                 //////采样率
	Uint16 uSampInterval;             ////采样间隔数
	Uint16 uSampIntervalbuf;             ////采样间隔数缓冲
	Uint16 CHANLEADDR[6];
	/*
	一次保存10包数据
	20*50*4/2
	*/
//	Uint16 CHANLE0[1000];
//	Uint16 CHANLE1[1000];
//	Uint16 CHANLE2[1000];
//	Uint16 CHANLE3[1000];
//	Uint16 CHANLE4[1000];
//	Uint16 CHANLE5[1000];
	Uint16 WaveID[10];/* 记录波形ID */
	Uint16 ucMaxWaveID;
	/* 波形读写指针 */
	Uint16 uWaveWriePos;
	Uint16 uWaveReadPos;

	Uint32 u2StartAddressRead;
	Uint32 u2StartAddressWrite;
	Uint16 * pFaultWbuf;       /////故障波形缓存区
	Uint16 uFaultMNum;        /////故障前缓冲区存储引导
	Uint16 uFaultANum;        ////故障后缓冲区存储引导
	Uint16 uFaultLStop;       ////故障缓存停止标志
	Uint16 pTimeInfo[7];   /////读取时间信息
	Uint16 uRefreshTC;       /////刷新时间的计数

	//I2CMSG *CurrentMsgPtr;

	/*输出参数*/
	Uint16 uWrFlashErr;           ////写FLASH过程错误信息

} COMMUN;

void DisplayWave(COMMUN *p);
void InitCommun(COMMUN *p);
void ReadFromFPGA(COMMUN *p);
void FaultWaveMemory(COMMUN *p);


#define COMM_DEFAULTS 	{ \
						(void (*)(Uint32))DisplayWave, \
						(void (*)(Uint32))ReadFromFPGA, \
						(void (*)(Uint32))InitCommun, \
						(void (*)(Uint32))FaultWaveMemory \
						}
void DisplayWave(COMMUN *PP);

extern COMMUN sInComm;
#endif 







