// TI File $Revision: /main/11 $
// Checkin $Date: May 12, 2008   14:30:08 $
//###########################################################################
//
// FILE:   DSP2833x_GlobalPrototypes.h
//
// TITLE:  Global prototypes for DSP2833x Examples
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x Header Files V1.20 $
// $Release Date: August 1, 2008 $
//###########################################################################

#ifndef DSP2833x_GLOBALPROTOTYPES_H
#define DSP2833x_GLOBALPROTOTYPES_H


#ifdef __cplusplus
extern "C" {
#endif

extern void InitAdc(void);
extern void DMAInitialize(void);

//
// DMA Channel 1
//
extern void DMACH1AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH1BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH1TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH1WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH1ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize, Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH1(void);

extern void InitEPwm1Gpio();
extern void InitEPwm2Gpio();
extern void InitEPwm3Gpio();
extern void InitEPwm4Gpio();
extern void InitEPwm5Gpio();
extern void InitEPwm6Gpio();

extern void InitEPwm1Example(void);
extern void InitEPwm2Example(void);
extern void InitEPwm3Example(void);
extern void InitEPwm4Example(void);
//extern void InitEPwm5Example(void);
//extern void InitEPwm6Example(void);
extern void InitPwm(void);

extern void fnInitEQep(void);
extern void SysCtl_Debug(void);
extern void InitAdc(void);
extern void fnInitAdc(void);
extern void InitPeripherals(void);
extern void delay_loop(void);
extern void InitSysCtrl(void);
extern void fnInitXintf16Gpio();
extern void InitPll(Uint16 pllcr, Uint16 clkindiv);
extern void InitPeripheralClocks(void);
extern void DSP28x_usDelay(Uint32 Count);
extern void ADC_cal(void);
extern void fnDisDog(void);
extern void fnInitClock(void);
extern void fnInitFlash(void);
extern void fnInitXintf(void);
extern void fnInitPieVectTable(void);
extern void fnInitPieCtrl(void);
extern void fnInitGpio(void);
extern void fnInitSPI(void);
extern void fnEnableInterrupts(void);
extern void fnSysPeripheralInit(void);


#define KickDog ServiceDog     // For compatiblity with previous versions
extern void ServiceDog(void);
extern Uint16 CsmUnlock(void);

//                 CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results

extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);


//---------------------------------------------------------------------------
// External symbols created by the linker cmd file
// DSP28 examples will use these to relocate code from one LOAD location
// in either Flash or XINTF to a different RUN location in internal
// RAM
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
extern Uint16 RamfuncsLoadSize;

extern Uint16 XintffuncsLoadStart;
extern Uint16 XintffuncsLoadEnd;
extern Uint16 XintffuncsRunStart;
extern Uint16 XintffuncsLoadSize;

#ifdef __cplusplus
}
#endif // extern "C" 

#endif   // - end of DSP2833x_GLOBALPROTOTYPES_H

//===========================================================================
// End of file.
//===========================================================================


