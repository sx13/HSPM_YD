#ifndef VVVF_H
#define VVVF_H
#include "DSP2833x_Device.h"
//=====================================================

typedef struct{
				void 	(*pfnCalc)();	//计算函数指针
				void	(*pfnReset)();	//复位函数指针
				void 	(*pfnInit)();	//初始化函数指针
			//输入
	            float32  fFreqRefGive;   //系统（ARM）给定频率
				float32  fFreqRefMin;   //最小频率
	            float32  fFreqRefBase;  //基准频率
	            float32  fFreqRefPoint1;   //VF曲线频率点1
	            float32  fFreqRefPoint2;  //VF曲线频率点2

	            float32  fVoltRefMin;     //最小电压
	            float32  fVoltRefMax;     //最大电压
	            float32  fVoltRefPoint1;   //VF曲线电压点1
	            float32  fVoltRefPoint2;  //VF曲线电压点2

	       //输出
	            float32  fTheta_base;    //角度输出
	            float32  fVoltageAmp;    //电压幅值/调制比

	            float32  fVFPhseCoffic;
}TypeSysVVVFCal;

//===================VVVFVar的默认初始化变量========================================
#define VVVFVal_DEFAULTS {\
							(void (*)(Uint32))fnVVVFCtrlInterface, \
							(void (*)(Uint32))fnVVVFVarReset, \
							(void (*)(Uint32))fnVVVFVarInit, \
							0.0,0.0,0.0,0.0,0.0, \
							0.0,0.0,0.0,0.0, \
							0.0,0.0,0.0}

extern TypeSysVVVFCal  SysVVVFCtrl;
extern void fnVVVFCtrlInterface(TypeSysVVVFCal *p);
extern void fnVVVFVarReset(TypeSysVVVFCal *p);
extern void fnVVVFVarInit(TypeSysVVVFCal *p);
//===== 电抗器测试参数结构体 ================================
typedef struct {
	                void (*pfnCalc)();	//计算函数指针
                //参数
					float32 fVoltageAmpSet;
					float32 fVoltageAmpSetLast;
					float32 fVoltageAmp_temp;
					float32 fTheta_base;

					Uint16  Enable;

                } TypeSysConTestParam;

                //初始值
#define SysConTestParam_DEFAULTS  {\
                                    (void (*)(Uint32))fnUnitTestingInterface, \
                		            0.0,0.0,0.0,0.0,0}

extern TypeSysConTestParam  SysConTest;
extern void fnUnitTestingInterface(TypeSysConTestParam *p);



#endif
