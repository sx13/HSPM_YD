/*
//===========================================================================
//
// 文件名:	DSP2833x_PieCtrl.c
//
// 用途:   DSP28335的PIE控制寄存器初始化
//
//
// 说明:
//			包括PIE控制寄存器初始化 fnInitPieCtrl（）
// 			和PIE使能函数			fnEnableInterrupts()
*/



#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
//#include "Modbus.h"
//===========================================================================
// InitPieCtrl: 
// This function initializes the PIE control registers to a known state.
//
void fnInitPieCtrl(void)
{
    //
    // Disable Interrupts at the CPU level
    //
    DINT;

    //
    // Disable the PIE
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

    //
    // Clear all PIEIER registers
    //
    PieCtrlRegs.PIEIER1.all = 0;
    PieCtrlRegs.PIEIER2.all = 0;
    PieCtrlRegs.PIEIER3.all = 0;
    PieCtrlRegs.PIEIER4.all = 0;
    PieCtrlRegs.PIEIER5.all = 0;
    PieCtrlRegs.PIEIER6.all = 0;
    PieCtrlRegs.PIEIER7.all = 0;
    PieCtrlRegs.PIEIER8.all = 0;
    PieCtrlRegs.PIEIER9.all = 0;
    PieCtrlRegs.PIEIER10.all = 0;
    PieCtrlRegs.PIEIER11.all = 0;
    PieCtrlRegs.PIEIER12.all = 0;

    //
    // Clear all PIEIFR registers
    //
    PieCtrlRegs.PIEIFR1.all = 0;
    PieCtrlRegs.PIEIFR2.all = 0;
    PieCtrlRegs.PIEIFR3.all = 0;
    PieCtrlRegs.PIEIFR4.all = 0;
    PieCtrlRegs.PIEIFR5.all = 0;
    PieCtrlRegs.PIEIFR6.all = 0;
    PieCtrlRegs.PIEIFR7.all = 0;
    PieCtrlRegs.PIEIFR8.all = 0;
    PieCtrlRegs.PIEIFR9.all = 0;
    PieCtrlRegs.PIEIFR10.all = 0;
    PieCtrlRegs.PIEIFR11.all = 0;
    PieCtrlRegs.PIEIFR12.all = 0;
}	
//===========================================================================
// EnableInterrupts: 
// This function enables the PIE module and CPU interrupts
void fnEnableInterrupts()
{
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;//使能外部中断1（XINT1）
	PieCtrlRegs.PIEIER1.bit.INTx5 = 1;//使能外部中断2（XINT2）
	
	XIntruptRegs.XINT1CR.bit.POLARITY = 0;//下降沿触发
	XIntruptRegs.XINT2CR.bit.POLARITY = 0;//下降沿触发
	
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;//使能XINT1组中断
	XIntruptRegs.XINT2CR.bit.ENABLE = 1;//使能XINT2组中断
	
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
	PieCtrlRegs.PIEIER3.bit.INTx3 = 1;
	PieCtrlRegs.PIEIER3.bit.INTx4 = 1;
	
	IER |= M_INT1; //使能1级CPU中断
	IER |= M_INT3;
	IER |= M_INT7;

	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;// Enable the PIE
	PieCtrlRegs.PIEACK.all = 0xFFFF;// Enables PIE to drive a pulse into the CPU

	ERTM;
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;// Start all the timers synced
	EDIS;

	EINT;
}

//===========================================================================
// End of file.
//===========================================================================
