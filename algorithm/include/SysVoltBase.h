#ifndef SYSVoltBASE_H
#define SYSVoltBASE_H
#include "DSP2833x_Device.h"
//=====================================================

typedef struct{
	void 	(*pfnCalc)();	//计算函数指针
	void	(*pfnReset)();	//复位函数指针
	void 	(*pfnInit)();	//初始化函数指针
	
	
	float32 fUu_base; 	//U相调制波
	float32 fUv_base;	//v相调制波
	float32	fUw_base;	//w相调制波
	Uint16  uCarrCount;	//载波计数最大值
	Uint16  uChopCount;
	Uint16  uUu_Fib;    //写入光纤板调制波数据
	Uint16  uUv_Fib;    //写入光纤板调制波数据
	Uint16  uUw_Fib;    //写入光纤板调制波数据
	Uint16  chopwave_Fib;
	

}TypeVoltBaseCal;



//===================电压基波计算的默认初始化变量========================================
#define SysVoltBaseCal_DEFAULTS {\
							(void (*)(Uint32))fnSysVoltBaseCalc, \
							(void (*)(Uint32))fnSysVoltBaseReset, \
							(void (*)(Uint32))fnSysVoltBaseInit, \
							0.0,0.0,0.0,25000,0,0,0\
	                            }

extern void fnSysVoltBaseInit(TypeVoltBaseCal *p);
extern void fnSysVoltBaseReset(TypeVoltBaseCal *p);
extern void fnSysVoltBaseCalc(TypeVoltBaseCal *p);
extern TypeVoltBaseCal  SysVoltBase;
#endif
