/* 历史版本
// Version: V1.0
// Date: 	Nov 24, 2012
// Author:	chenchangjaing @YD
//==========================================================================
// 
// 文件名:	DSP2833x_Clock.c
//
// 用途:	DSP28335时钟设置，外设时钟配置
//
// 说明:	包括锁相环时钟设置、外设时钟配置

//==========================================================================
*/

#include "DSP2833x_Device.h"     	// 寄存器定义
#include "DSP2833x_Examples.h"   // Examples Include File
//==========================================================================
// PLL初始化程序 150MHz copy from TI
// system control and interrupts page 48 49
//==========================================================================
void fnInitPll(Uint16 val, Uint16 divsel)
{
   // Make sure the PLL is not running in limp mode
   if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
   {

      asm("        ESTOP0");
   }
	// 改变PLLCR前，DIVSEL必须为0
   if (SysCtrlRegs.PLLSTS.bit.DIVSEL != 0)
   {
       EALLOW;
       SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
       EDIS;
   }

   // 赋值PLLCR
   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {
      	EALLOW;
      	// Before setting PLLCR turn off missing clock detect logic
      	SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
      	SysCtrlRegs.PLLCR.bit.DIV = val;
     	EDIS;


		while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)
    	{
	      // 等待新的锁相完成
    	}

    	EALLOW;
    	SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
    	EDIS;
    }

    // 赋值DIVSEL
	if((divsel == 1)||(divsel == 2))
	{
		EALLOW;
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = divsel;
	    EDIS;
	}

	// 若DIVSEL=3，分步赋值，避免电平波动
	if(divsel == 3)
	{
		EALLOW;
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = 2;
	    DELAY_US(50L);
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = 3;
	    EDIS;
    }
}

//--------------------------------------------------------------------------
// 外设时钟初始化
//---------------------------------------------------------------------------

void fnInitPeripheralClocks(void)
{
    EALLOW;

    //
    // HISPCP/LOSPCP prescale register settings, normally it will be set to
    // default values
    //
    SysCtrlRegs.HISPCP.all = 0x0001;
    SysCtrlRegs.LOSPCP.all = 0x0002;

    //
    // XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT
    // XTIMCLK = SYSCLKOUT/2
    //
    XintfRegs.XINTCNF2.bit.XTIMCLK = 1;

    //
    // XCLKOUT = XTIMCLK/2
    //
    XintfRegs.XINTCNF2.bit.CLKMODE = 1;

    //
    // Enable XCLKOUT
    //
    XintfRegs.XINTCNF2.bit.CLKOFF = 0;

    //
    // Peripheral clock enables set for the selected peripherals.
    // If you are not using a peripheral leave the clock off
    // to save on power.
    //
    // Note: not all peripherals are available on all 2833x derivates.
    // Refer to the datasheet for your particular device.
    //
    // This function is not written to be an example of efficient code.
    //
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC

    //
    //                          *IMPORTANT*
    // The ADC_cal function, which  copies the ADC calibration values from TI
    // reserved OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs
    // automatically in the Boot ROM. If the boot ROM code is bypassed during
    // the debug process, the following function MUST be called for the ADC to
    // function according to specification. The clocks to the ADC MUST be
    // enabled before calling this function.
    // See the device data manual and/or the ADC Reference
    // Manual for more information.
    //
    ADC_cal();

    SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;   // I2C
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
    SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;   // SCI-B
    SysCtrlRegs.PCLKCR0.bit.SCICENCLK = 1;   // SCI-C
    SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;   // SPI-A
    SysCtrlRegs.PCLKCR0.bit.MCBSPAENCLK = 1; // McBSP-A
    SysCtrlRegs.PCLKCR0.bit.MCBSPBENCLK = 1; // McBSP-B
    SysCtrlRegs.PCLKCR0.bit.ECANAENCLK=1;    // eCAN-A
    SysCtrlRegs.PCLKCR0.bit.ECANBENCLK=1;    // eCAN-B

    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Disable TBCLK within the ePWM
    SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
    SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
    SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3
    SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;  // ePWM4
    SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;  // ePWM5
    SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;  // ePWM6
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TBCLK within the ePWM

    SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 1;  // eCAP3
    SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 1;  // eCAP4
    SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK = 1;  // eCAP5
    SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK = 1;  // eCAP6
    SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;  // eCAP1
    SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 1;  // eCAP2
    SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;  // eQEP1
    SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = 1;  // eQEP2

    SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer 0
    SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 1; // CPU Timer 1
    SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 1; // CPU Timer 2

    SysCtrlRegs.PCLKCR3.bit.DMAENCLK = 1;       // DMA Clock
    SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;     // XTIMCLK
    SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;    // GPIO input clock

    EDIS;
}

//---------------------------------------------------------------------------
// Example: CsmUnlock:
//---------------------------------------------------------------------------
// This function unlocks the CSM. User must replace 0xFFFF's with current
// password for the DSP. Returns 1 if unlock is successful.

#define STATUS_FAIL          0
//#define STATUS_SUCCESS       1

Uint16 CsmUnlock()
{
    volatile Uint16 temp;

    // Load the key registers with the current password. The 0xFFFF's are dummy
	// passwords.  User should replace them with the correct password for the DSP.

    EALLOW;
    CsmRegs.KEY0 = 0xFFFF;
    CsmRegs.KEY1 = 0xFFFF;
    CsmRegs.KEY2 = 0xFFFF;
    CsmRegs.KEY3 = 0xFFFF;
    CsmRegs.KEY4 = 0xFFFF;
    CsmRegs.KEY5 = 0xFFFF;
    CsmRegs.KEY6 = 0xFFFF;
    CsmRegs.KEY7 = 0xFFFF;
    EDIS;

    // Perform a dummy read of the password locations
    // if they match the key values, the CSM will unlock

    temp = CsmPwl.PSWD0;
    temp = CsmPwl.PSWD1;
    temp = CsmPwl.PSWD2;
    temp = CsmPwl.PSWD3;
    temp = CsmPwl.PSWD4;
    temp = CsmPwl.PSWD5;
    temp = CsmPwl.PSWD6;
    temp = CsmPwl.PSWD7;

    // If the CSM unlocked, return succes, otherwise return
    // failure.
    if (CsmRegs.CSMSCR.bit.SECURE == 0) return 1;//STATUS_SUCCESS;
    else return STATUS_FAIL;

}

void fnInitClock(void)
{
   // 设置时钟
   // DSP28_PLLCR and DSP28_DIVSEL are defined in DSP2833x_Parameters.h
   fnInitPll(DSP28_PLLCR,DSP28_DIVSEL);

   // 初始化外设时钟
   fnInitPeripheralClocks();
}

//===========================================================================
// End of file.
//===========================================================================
