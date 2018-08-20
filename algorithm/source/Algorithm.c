#include "SysCtl_AllHeaders.h"

/***********************************************************
//函数名称：fnSysVoltBaseInit
//函数功能：基波电压处理初始化
//函数参数：无
************************************************************/
void fnSysVoltBaseInit(TypeVoltBaseCal *p)
{
  p->fUu_base = 0.0;
  p->fUv_base = 0.0;
  p->fUw_base = 0.0;
  p->uCarrCount = uPeriodCounter;
  p->uUu_Fib = 0;
  p->uUv_Fib = 0;
  p->uUw_Fib = 0;
}
/***********************************************************
//函数名称：fnSysVoltBaseReset
//函数功能：基波电压处理复位
//函数参数：无
************************************************************/
void fnSysVoltBaseReset(TypeVoltBaseCal *p)
{
  p->fUu_base = 0.0;
  p->fUv_base = 0.0;
  p->fUw_base = 0.0;
  p->uCarrCount = uPeriodCounter;
  p->uUu_Fib = 0;
  p->uUv_Fib = 0;
  p->uUw_Fib = 0;
}
/***********************************************************
//函数名称：fnSysVoltBaseCalc
//函数功能：基波电压计算接口float->int
//函数参数：无
************************************************************/
void fnSysVoltBaseCalc(TypeVoltBaseCal *p)
{
	float32  fUuBoost = 0.5;
	float32  fUvBoost = 0.5;
	float32  fUwBoost = 0.5;

	fUuBoost = 0.5 * (1.0 + p->fUu_base);//U相电压抬升
                                        //
 	fUvBoost = 0.5 * (1.0 + p->fUv_base);//V相电压抬升
                                        //
 	fUwBoost = 0.5 * (1.0 + p->fUw_base);//W相电压抬升
                                        //
	 p->uUu_Fib = (Uint16)(fUuBoost * p->uCarrCount);//U光纤板电压
												   //
	 p->uUv_Fib = (Uint16)(fUvBoost * p->uCarrCount);//V光纤板电压
												   //
	 p->uUw_Fib = (Uint16)(fUwBoost * p->uCarrCount);//W光纤板电压
										   //
	 if(p->uUu_Fib > p->uCarrCount)
		 p->uUu_Fib = p->uCarrCount;//
						   //
	 if(p->uUv_Fib > p->uCarrCount)
		 p->uUv_Fib = p->uCarrCount;//
						   //
	 if(p->uUw_Fib > p->uCarrCount)
		 p->uUw_Fib = p->uCarrCount;//

	InvModuWave(p->uUu_Fib,p->uUv_Fib,p->uUw_Fib);

	DEP_DSP_GPWM_ENABLE = 1;
	//DEP_DSP_GPWM_ENABLE = 3;

}
