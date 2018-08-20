/* 历史版本
// Version: V1.0
// Date: 	Dec 21, 2010
// Author:	csc @QH
//==========================================================================
// Version: V1.1
// Date: 	Dec 21, 2010
// Author:	csc @QH

//==========================================================================
// 
// 文件名:	DSP2833x_Flash.c
//
// 用途:	DSP28335的Flash寄存器初始化
//
// 说明:	InitFlash函数必须在RAM中运行

//==========================================================================
*/

#include "DSP2833x_Device.h"  
#include "DSP2833x_GlobalPrototypes.h"  
//将fnInitFlash定位到ramfuncs空间，不在flash中运行
#pragma CODE_SECTION(fnInitFlash, "ramfuncs");
 void fnInitFlash(void)
 {
   //#if FLASH_LOAD 
     //  MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);//ramfuncs从flash复制到ram中运行
   //#endif
   EALLOW;
   //使能flash流水线操作
   FlashRegs.FOPT.bit.ENPIPE = 1;
   //Flash页面读取等待时间，SYSCLKOUT的倍数
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;
   //Flash随机读取等待时间，SYSCLKOUT的倍数
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;
   //OTP读取等待时间，SYSCLKOUT的倍数
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 8;
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
   EDIS;
   asm(" RPT #1 || NOP");
}

//==========================================================================
// End of file.
//==========================================================================


























