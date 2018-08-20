/* 历史版本
// Version: V1.0
// Date: 	Oct 17, 2012
// Author:	csc @YD
//==========================================================================
// 
// 文件名:	DSP2833x_GPIO.c
//
// 用途:	DSP28335通用IO口设置
//
// 说明:	

//==========================================================================
*/

#include "DSP2833x_Device.h"     // DSP2833x头文件

void fnInitGpio(void)
{
   EALLOW;

  //看门狗IO初始化
   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;//General IO
   GpioCtrlRegs.GPADIR.bit.GPIO15  = 1;//OutPut
   GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 0;//Synch to Sysclkout
   GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;//Enable Pullup 


   // 编码器IO初始化
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;    // Enable pull-up on GPIO24 (EQEP2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;    // Enable pull-up on GPIO25 (EQEP2B)

    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;  // Sync to SYSCLKOUT GPIO24 (EQEP2A)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;  // Sync to SYSCLKOUT GPIO25 (EQEP2B)

    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 2;   // Configure GPIO24 as EQEP2A
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 2;   // Configure GPIO25 as EQEP2B

   //功能IO设置
   //硬件封锁输出
   GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;//General IO
   GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;//OutPut
   GpioCtrlRegs.GPBPUD.bit.GPIO48 = 0;//Enable PullUp
   GpioCtrlRegs.GPBQSEL2.bit.GPIO48 = 0;//Sync to Sysclkout

   //外部中断IO设置(GPIO17)，主中断处理
   GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;
   GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;//General IO
   GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;//Input
   GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 17;//GPIO17===XINT1 T\Z\1
   //
   //故障中断
//   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;//General IO,Xint2 Source // Tz2改为Tz6
//   GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;//Input
//   GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 12;//GPIO13 ===XINT2 T\Z\6

 //输出备用
   GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;//General IO
   GpioCtrlRegs.GPADIR.bit.GPIO26  = 1;//outPut
   GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;//Synch to Sysclkout
   GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;//Enable Pullup 

   GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;//General IO
   GpioCtrlRegs.GPADIR.bit.GPIO27  = 0;//inPut

   GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;//General IO
   GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;//OutPut

   GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;//General IO
   GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;//inPut
   GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0;//General IO
   GpioCtrlRegs.GPBDIR.bit.GPIO59 = 0;//inPut

  EDIS;
   GpioDataRegs.GPBDAT.bit.GPIO48 = 1;//
   GpioDataRegs.GPBDAT.bit.GPIO49 = 1;
   GpioDataRegs.GPADAT.bit.GPIO26 = 0;
}	
	
//===========================================================================
// End of file.
//===========================================================================
