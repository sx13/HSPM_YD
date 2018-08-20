/* 
//=======================================================
// 
// 文件名:	DSP2833x_SysPerInit.c
//
// 用途:	系统外设初始化
//
// 说明:	

//========================================================
*/
#include "DSP2833x_Device.h"    
#include "DSP2833x_GlobalPrototypes.h"
#include "DSP2833x_Examples.h"

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;

void fnSysPeripheralInit(void)
{
	fnDisDog();//禁止看门狗
	fnInitClock();//设置时钟

	//================初始化Flash========================================
	MemCopy((Uint16*)&RamfuncsLoadStart, (Uint16*)&RamfuncsLoadEnd, (Uint16*)&RamfuncsRunStart);

	fnInitFlash();

	//==============设置外部空间=====================================
	fnInitXintf();
	//==============初始化中断向量表到一个确定状态===================
	fnInitPieVectTable();
	//==============初始化中断设置，所有中断使能清零=================
	fnInitPieCtrl();
	//============设置Gpio=========================================
	fnInitGpio();
	//============初始化AD=========================================
	InitAdc();//
		   //
	fnInitAdc();//

	//==========初始化EPWM==========================================
	//InitPwm();
}



//======================================


