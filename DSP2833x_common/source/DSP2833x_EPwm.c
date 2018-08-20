//###########################################################################
//
// FILE:   DSP2833x_EPwm.c
//
// TITLE:  DSP2833x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V142 $
// $Release Date: November  1, 2016 $
// $Copyright: Copyright (C) 2007-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//
// InitEPwm - This function initializes the ePWM(s) to a known state.
//
void 
InitEPwm(void)
{
    //
    // Initialize ePWM1/2/3/4/5/6
    //
}

//
// InitEPwmGpio - This function initializes GPIO pins to function as ePWM pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
void 
InitEPwmGpio(void)
{
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();
#if DSP28_EPWM4
    InitEPwm4Gpio();
#endif // endif DSP28_EPWM4
#if DSP28_EPWM5    
    InitEPwm5Gpio();
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
    InitEPwm6Gpio();
#endif // endif DSP28_EPWM6 
}

//
// InitEPwm1Gpio - This function initializes GPIO pins to function as ePWM1
// 
void 
InitEPwm1Gpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)   

    //
    // Configure ePWM-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be ePWM1 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

//
// InitEPwm2Gpio - This function initializes GPIO pins to function as ePWM2
//
void 
InitEPwm2Gpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)

    //
    // Configure ePWM-2 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be ePWM2 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    EDIS;
}

//
// InitEPwm3Gpio - This function initializes GPIO pins to function as ePWM3
//
void 
InitEPwm3Gpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)

    //
    // Configure ePWM-3 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be ePWM3 functional
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
}

#if DSP28_EPWM4
//
// InitEPwm4Gpio - This function initializes GPIO pins to function as ePWM4
//
void 
InitEPwm4Gpio(void)
{
    EALLOW;
    
    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)

    //
    // Configure ePWM-4 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be ePWM4 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

    EDIS;
}
#endif // endif DSP28_EPWM4  

#if DSP28_EPWM5
//
// InitEPwm5Gpio - This function initializes GPIO pins to function as ePWM5
//
void 
InitEPwm5Gpio(void)
{
    EALLOW;
    
    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)

    //
    // Configure ePWM-5 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be ePWM5 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B

    EDIS;
}
#endif // endif DSP28_EPWM5

#if DSP28_EPWM6
//
// InitEPwm6Gpio - This function initializes GPIO pins to function as ePWM6
//
void 
InitEPwm6Gpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    // Enable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up on GPIO11 (EPWM6B)

    //
    // Configure ePWM-6 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be ePWM6 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B

    EDIS;
}
#endif // endif DSP28_EPWM6  

//
// InitEPwmSyncGpio - This function initializes GPIO pins to function as ePWM 
// Synch pins
//
void 
InitEPwmSyncGpio(void)
{
    EALLOW;
    
    //
    // Configure EPWMSYNCI
    //

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;  //Enable pull-up on GPIO6 (EPWMSYNCI)
    //GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;//Enable pull-up on GPIO32 (EPWMSYNCI)    

    //
    // Set qualification for selected pins to asynch only
    // This will select synch to SYSCLKOUT for the selected pins.
    // Comment out other unwanted lines.
    //
    
    //
    // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;
    
    //
    //Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)
    //
    //GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;   

    //
    // Configure EPwmSync pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPwmSync 
    // functional pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;  //Enable pull-up on GPIO6(EPWMSYNCI)
    //GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;//Enable pull-up on GPIO32(EPWMSYNCI)    

    //
    // Configure EPWMSYNC0
    //

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    
    //
    // Enable pull-up on GPIO6 (EPWMSYNC0)
    //
    //GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
    
    //
    // Enable pull-up on GPIO33 (EPWMSYNC0)
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;

    //
    // Enable pull-up on GPIO6 (EPWMSYNC0)
    //
    //GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;
    
    //
    // Enable pull-up on GPIO33 (EPWMSYNC0)
    //
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;
}

//
// InitTzGpio -  This function initializes GPIO pins to function as Trip Zone
// (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
void 
InitTzGpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user. 
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up on GPIO15 (TZ4)

    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ5)
    //GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ5)

    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ6) 
    //GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ6)  

    //
    // Set qualification for selected pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.  
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (TZ4)

    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ5)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ5)

    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ6) 
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ6)  

    //
    // Configure TZ pins using GPIO regs
    // This specifies which of the possible GPIO pins will be TZ functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // Configure GPIO15 as TZ4

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ5
    //GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ5

    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ6               
    //GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ6  

    EDIS;
}

void InitEPwm1Example()
{
   EPwm1Regs.TBPRD = 6000;                        // Set timer period
   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;

   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   EPwm1Regs.CMPA.half.CMPA = 1000;

   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on Zero
   EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;


   EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
   EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;

   EPwm1Regs.DBCTL.all = 0xb;
   EPwm1Regs.DBFED = 0;
   EPwm1Regs.DBRED = 0;
   EPwm1Regs.TZSEL.all = 0;
   EPwm1Regs.TZCTL.all = 0;
   EPwm1Regs.TZEINT.all = 0;
   EPwm1Regs.TZFLG.all = 0;
   EPwm1Regs.TZFRC.all = 0;
   EPwm1Regs.ETSEL.all = 0;
   EPwm1Regs.ETFLG.all = 0;
   EPwm1Regs.ETCLR.all = 0;
   EPwm1Regs.ETFRC.all = 0;
   EPwm1Regs.PCCTL.all = 0;
}

void InitEPwm2Example()
{
   EPwm2Regs.TBPRD = 6000;                        // Set timer period
   EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;          // Slow just to observe on the scope

   // Setup compare
   EPwm2Regs.CMPA.half.CMPA = 3000;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM2A on Zero
   EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;


   EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;           // Set PWM2A on Zero
   EPwm2Regs.AQCTLB.bit.CAD = AQ_SET;

   EPwm2Regs.DBCTL.all = 0xb;
   EPwm2Regs.DBFED = 0;
   EPwm2Regs.DBRED = 0;
   EPwm2Regs.TZSEL.all = 0;
   EPwm2Regs.TZCTL.all = 0;
   EPwm2Regs.TZEINT.all = 0;
   EPwm2Regs.TZFLG.all = 0;
   EPwm2Regs.TZFRC.all = 0;
   EPwm2Regs.ETSEL.all = 0;
   EPwm2Regs.ETFLG.all = 0;
   EPwm2Regs.ETCLR.all = 0;
   EPwm2Regs.ETFRC.all = 0;
   EPwm2Regs.PCCTL.all = 0;
}

void InitEPwm3Example()
{
   EPwm3Regs.TBPRD = 600;                         // Set timer period
   EPwm3Regs.TBPHS.half.TBPHS = 0x0000;            // Phase is 0
   EPwm3Regs.TBCTR = 0x0000;                       // Clear counter


   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV4;          // Slow so we can observe on the scope

   // Setup compare
   EPwm3Regs.CMPA.half.CMPA = 3000;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;              // Set PWM3A on Zero
   EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;


   EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;            // Set PWM3A on Zero
   EPwm3Regs.AQCTLB.bit.CAD = AQ_SET;

   EPwm3Regs.TZSEL.bit.OSHT6 = 0;
   EPwm3Regs.TZSEL.bit.CBC6 = 0;
   EPwm3Regs.TZSEL.bit.OSHT1 = 0;
   EPwm3Regs.TZSEL.bit.CBC1 = 0;

   EPwm3Regs.DBCTL.all = 0xb;
   EPwm3Regs.DBFED = 0;
   EPwm3Regs.DBRED = 0;
   EPwm3Regs.TZSEL.all = 0;
   EPwm3Regs.TZCTL.all = 0;
   EPwm3Regs.TZEINT.all = 0;
   EPwm3Regs.TZFLG.all = 0;
   EPwm3Regs.TZFRC.all = 0;
   EPwm3Regs.ETSEL.all = 0;
   EPwm3Regs.ETFLG.all = 0;
   EPwm3Regs.ETCLR.all = 0;
   EPwm3Regs.ETFRC.all = 0;
   EPwm3Regs.PCCTL.all = 0;
}

void InitEPwm4Example()
{
   EPwm4Regs.TBPRD = 6000;                         // Set timer period
   EPwm4Regs.TBPHS.half.TBPHS = 0x0000;            // Phase is 0
   EPwm4Regs.TBCTR = 0x0000;                       // Clear counter


   // Setup TBCLK
   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV4;          // Slow so we can observe on the scope

   // Setup compare
   EPwm4Regs.CMPA.half.CMPA = 3000;

   // Set actions
   EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;              // Set PWM3A on Zero
   EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;


   EPwm4Regs.AQCTLB.bit.CAU = AQ_CLEAR;            // Set PWM3A on Zero
   EPwm4Regs.AQCTLB.bit.CAD = AQ_SET;

   EPwm4Regs.DBCTL.all = 0xb;
   EPwm4Regs.DBFED = 0;
   EPwm4Regs.DBRED = 0;
   EPwm4Regs.TZSEL.all = 0;
   EPwm4Regs.TZCTL.all = 0;
   EPwm4Regs.TZEINT.all = 0;
   EPwm4Regs.TZFLG.all = 0;
   EPwm4Regs.TZFRC.all = 0;
   EPwm4Regs.ETSEL.all = 0;
   EPwm4Regs.ETFLG.all = 0;
   EPwm4Regs.ETCLR.all = 0;
   EPwm4Regs.ETFRC.all = 0;
   EPwm4Regs.PCCTL.all = 0;


}

void InitPwm(void)
{
	InitEPwm1Gpio();
	InitEPwm2Gpio();
	InitEPwm3Gpio();
	InitEPwm4Gpio();

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	InitEPwm1Example();
	InitEPwm2Example();
	InitEPwm3Example();
	InitEPwm4Example();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
}
//
// End of file
//

