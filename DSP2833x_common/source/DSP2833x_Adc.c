// TI File $Revision: /main/5 $
// Checkin $Date: October 23, 2007   13:34:09 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x Header Files V1.20 $
// $Release Date: August 1, 2008 $
//###########################################################################


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_GlobalPrototypes.h"
#define ADC_usDELAY  5000L

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
 {
  extern void DSP28x_usDelay(Uint32 Count);
  EALLOW;
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
  EDIS;
  AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
 }
void fnInitAdc(void)
{
 AdcRegs.ADCTRL1.bit.CPS = 1;//Fclk = Clk/2
 AdcRegs.ADCTRL1.bit.ACQ_PS = 1;//2个时钟的采保时间
 AdcRegs.ADCTRL1.bit.CONT_RUN = 0;//启停转换模式
 AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;//0双排序器工作模式1级联模式
 AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;//复位SEQ1--CONV00
 AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;//复位SEQ2--CONV08
 AdcRegs.ADCTRL3.bit.ADCCLKPS = 1;//clk = HSPCLK/4
 AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;//顺序采样模式
 AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 7;//SEQ1最大转换数8
 AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;//使能中断请求
 AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;//
 
 AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;	//设置ADCINA0作为第1个变换
 AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 8;	//设置ADCINB0作为第2个变换
 AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 1;	//设置ADCINA1作为第3个变换
 AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 9;	//设置ADCINB1作为第4个变换
 AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 2;	//设置ADCINA2作为第5个变换
 AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 10;	//设置ADCINB2作为第6个变换
 AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 3; 	//设置ADCINA3作为第7个变换
 AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 11;	//设置ADCINB3作为第8个变换
 AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 4;
 AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 5;////
 AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 6;////
 AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 7;////
 AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 13;
 AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 13;
 AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 14;
 AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 14;

}

//===========================================================================
// End of file.
//===========================================================================
