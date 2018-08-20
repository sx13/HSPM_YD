/*
//===========================================================================
//
// 文件名:	DSP2833x_Xintf.c
//
// 用途:  	外部空间初始化
//
// 说明:
//			包括外部空间初始化 	fnInitXintf（）
// 			IO定义				fnInitXintf32Gpio()
*/


#include "DSP2833x_Device.h"     	// DSP2833x Headerfile Include File

//===========================================================================
// InitXINTF的IO设置

void fnInitXintf16Gpio()
{
 EALLOW;
 GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 3;  // XD15
 GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 3;  // XD14
 GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 3;  // XD13
 GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 3;  // XD12
 GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 3;  // XD11
 GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 3;  // XD10
 GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 3;  // XD19
 GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 3;  // XD8
 GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 3;  // XD7
 GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 3;  // XD6
 GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 3;  // XD5
 GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 3;  // XD4
 GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 3;  // XD3
 GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 3;  // XD2
 GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 3;  // XD1
 GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 3;  // XD0

 GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 3;  // XA0/XWE1n
 GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 3;  // XA1
 GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;  // XA2
 GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3;  // XA3
 GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 3;  // XA4
 GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 3;  // XA5
 GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 3;  // XA6
 GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 3;  // XA7

 GpioCtrlRegs.GPCMUX2.bit.GPIO80 = 3;  // XA8
 GpioCtrlRegs.GPCMUX2.bit.GPIO81 = 3;  // XA9
 GpioCtrlRegs.GPCMUX2.bit.GPIO82 = 3;  // XA10
 GpioCtrlRegs.GPCMUX2.bit.GPIO83 = 3;  // XA11
 GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 3;  // XA12
 GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 3;  // XA13
 GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 3;  // XA14
 GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 3;  // XA15
 GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 3;  // XA16
 GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 3;  // XA17
 GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 3;  // XA18
 GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // XA19

 GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 3;  // XREADY
 GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 3;  // XRNW
 GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 3;  // XWE0

 GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 3;  // XZCS0
 GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 3;  // XZCS7
 GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // XZCS6
 EDIS;
}

//===========================================================================
// 在外部空间访问时，不要更改访问时钟

void fnInitXintf(void)
{
 // Timing for all zones based on XTIMCLK = SYSCLKOUT(150MHz)
 EALLOW;
 // 所有ZONE的XTIMCLK设置
 //0 XTIMCLK = SYSCLKOUT
 //1 XTIMCLK = SYSCLKOUT/2
 // XTIMCLK = 150MHz
 XintfRegs.XINTCNF2.bit.XTIMCLK = 1;
 //0 XCLKOUT = XTIMCLK
 //1 XCLKOUT = XTIMCLK/2
 XintfRegs.XINTCNF2.bit.CLKMODE = 0;//
 // Disable XCLKOUT 150MHz
 XintfRegs.XINTCNF2.bit.CLKOFF = 0;
 //============================================ 
 // Zone 0
 // 1 double(75Mhz); 0 one(150Mhz)
 XintfRegs.XTIMING0.bit.X2TIMING = 1;//
 // Size must be either:
 // 0,1 = x32 or
 // 1,1 = x16 other values are reserved
 XintfRegs.XTIMING0.bit.XSIZE = 3;
 // Zone will sample XREADY signal
 XintfRegs.XTIMING0.bit.USEREADY = 0;//
                                     //
 //XintfRegs.XTIMING0.bit.READYMODE = 1;// sample asynchronous
                                      //
 XintfRegs.XTIMING0.bit.XWRLEAD = 3;//
                                    //
 XintfRegs.XTIMING0.bit.XWRACTIVE = 7;//
                                      //
 XintfRegs.XTIMING0.bit.XWRTRAIL = 3;//
                                     //
 // Zone read timing
 XintfRegs.XTIMING0.bit.XRDLEAD = 3;//
                                    //
 XintfRegs.XTIMING0.bit.XRDACTIVE = 7;//
                                      // 
 XintfRegs.XTIMING0.bit.XRDTRAIL = 3;//
                                    //
 // Zone 6------------------------------------
 // double all Zone read/write lead/active/trail timing
 // 1 double(75Mhz); 0 one(150Mhz)
 XintfRegs.XTIMING6.bit.X2TIMING = 0;////////0
 // Size must be either:
 // 0,1 = x32 or
 // 1,1 = x16 16位
 XintfRegs.XTIMING6.bit.XSIZE = 3;
 // XREADY不用
 XintfRegs.XTIMING6.bit.USEREADY = 0;
 //XintfRegs.XTIMING6.bit.READYMODE = 1;// sample asynchronous	
 // 写时序
 XintfRegs.XTIMING6.bit.XWRLEAD = 1;
 XintfRegs.XTIMING6.bit.XWRACTIVE = 1;
 XintfRegs.XTIMING6.bit.XWRTRAIL = 1;
 // 读时序
 XintfRegs.XTIMING6.bit.XRDLEAD = 1;
 XintfRegs.XTIMING6.bit.XRDACTIVE = 1;
 XintfRegs.XTIMING6.bit.XRDTRAIL = 1;

 // Zone 7------------------------------------
 // double all Zone read/write lead/active/trail timing
 XintfRegs.XTIMING7.bit.X2TIMING = 0;
 // Size must be either:
 // 0,1 = x32 or
 // 1,1 = x16 other values are reserved
 XintfRegs.XTIMING7.bit.XSIZE = 3;
 // Zone will sample XREADY signal
 XintfRegs.XTIMING7.bit.USEREADY = 0;//
 //XintfRegs.XTIMING7.bit.READYMODE = 1;  // sample asynchronous

 // When using ready, ACTIVE must be 1 or greater
 // Lead must always be 1 or greater
 // Zone write timing
 XintfRegs.XTIMING7.bit.XWRLEAD = 1;
 XintfRegs.XTIMING7.bit.XWRACTIVE = 1;
 XintfRegs.XTIMING7.bit.XWRTRAIL = 1;
 // Zone read timing
 XintfRegs.XTIMING7.bit.XRDLEAD = 1;
 XintfRegs.XTIMING7.bit.XRDACTIVE = 1;
 XintfRegs.XTIMING7.bit.XRDTRAIL = 1;
 // Bank switching
 // Assume Zone 7 is slow, so add additional BCYC cycles
 // when ever switching from Zone 7 to another Zone.
 // This will help avoid bus contention.
 XintfRegs.XBANK.bit.BCYC = 7;
 XintfRegs.XBANK.bit.BANK = 7;

 //XintfRegs.XINTCNF2.bit.WRBUFF=3;
 
 EDIS;
 //Force a pipeline flush to ensure that the write to
 //the last register configured occurs before returning.
 fnInitXintf16Gpio();
 //InitXintf32Gpio();
}

//===========================================================================
// No more.
//===========================================================================
