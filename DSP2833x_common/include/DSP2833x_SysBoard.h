/*
// Version: V1.0
// Date: 	Apr 4, 2013
// Author:	Myj @YD
//===========================================================================
//
// 文件名:	DSP2833x_SysBoard.h
//
// 用途:
//		1. 定义核心板FPGA寄存器地址
//		2. 定义光纤板FPGA寄存器地址
//		3. 函数声明
//===========================================================================
*/

#ifndef DSP2833X_SYSBOARD_H
#define DSP2833X_SYSBOARD_H

//============系统IO=============================
#define IO_Reset GpioDataRegs.GPBDAT.bit.GPIO48

#define pCS_ReadIO ((volatile Uint16 *)0x002808F8)     //系统IO输入
#define pCS_WriteIO ((volatile Uint16 *)0x002808F9)    //系统IO输出

//============读FPGA控制字=======================

//==========板卡确认信息地址================
#define pBUSBDAddrBase	((volatile Uint16 *)0x00004fe0)  //第一块板信息
#define RightInfo1  0x01
#define RightInfo2  0x81
#define FaultInfo1  0x11
#define FaultInfo2  0x91

//==========AD输出宏定义===========================
#define pCS_ADCONV ((volatile Uint16 *)0x002808F5)//AD启动
#define pCS_ADRD1 ((volatile Uint16 *)0x002808F6)//读AD1，网侧
#define pCS_ADRD2 ((volatile Uint16 *)0x002808F7)//读AD2，机侧

//==========DA输出宏定义===========================

#define pDA_Enable ((volatile Uint16 *)0x002808F4) //DA输出使能

#define pDA_Out1 ((volatile Uint16 *)0x002808F0)   //DA1输出
#define pDA_Out2 ((volatile Uint16 *)0x002808F1)   //DA2输出
#define pDA_Out3 ((volatile Uint16 *)0x002808F2)   //DA3输出
#define pDA_Out4 ((volatile Uint16 *)0x002808F3)   //DA4输出

//===============编码器位置信号定义===================
#define pCS_CoderPosition 	((volatile Uint16 *)0x00004C01)//编码器位置
#define pCS_CoderRound 		((volatile Uint16 *)0x00004C02)//编码器圈数
#define pCS_CoderDirWrite 	((volatile Uint16 *)0x00004C04)//编码器方向给定
#define pCS_CoderDirRead 	((volatile Uint16 *)0x00004C03)//编码器实际运行方向
#define pEncoder_ForwordReg (*((volatile Uint16 *)0x00004fc1))//编码器正反向
#define pEncoderReadFlag	(*((volatile Uint16 *)0x00004fc3))//全局控制寄存器
#define pEncoderPulseReg	(*((volatile Uint16 *)0x00004fc6))//全局控制寄存器

//=========外部函数声明 =====================================
extern void fnInitFibBoardCarClear(Uint16 uSysSeriesNum1);
extern void fnSysCellEn(Uint16 uSysSeriesNum);
extern void fnCellBypassClear(Uint16 Temp);
extern void fnInitFibBoardCar(Uint16 Temp);
extern void fnSysFibBoardInit(void);
extern void fnCellFaultRegClear();
extern void fnCellLockReset(void);
extern void fnSysFibHeartVersion(void);
#endif


