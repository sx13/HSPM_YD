/*
// Version: V1.0
// Date: 	Oct 25, 2012
// Author:	csc @YD
//===========================================================================
//
// 文件名:	DMC_GlobalPrototypes.h
//
// 用途:	电机控制库全局定义头文件，包含各功能模块的头文件。	
//
//===========================================================================
*/


#ifndef SYSCTL_ALLHEADERS_H
#define SYSCTL_ALLHEADERS_H
//============================

#include "C28x_FPU_FastRTS.h"
#include <math.h>
#include "MathBasic.h"
#include "DSP2833x_DefaultIsr.h"
#include "DSP2833x_GlobalPrototypes.h"
//#include "SysCtl_RunMoore.h"
#include "SysCtl_SysMoore.h"
#include "SysCtl_AnalogProcess.h"
#include "SysCtl_ConstDef.h"
#include "SysCtl_GlobalVar.h"

#include "DSP2833x_EPwm_defines.h"       // Macros used for PWM examples.
#include "DSP2833x_Dma_defines.h"
#include "COMMInterface.h"
#include "SysCtl_CsvParamDef.h"

#include "FpgaInf.h"

#include "SysVoltBase.h"
#include "VVVF.h"
///===========矢量控制============
#include "cur_vol_model.h"
//#include "DMC_CLARKE.h"
#include "DMC_Filter.h"
#include "DMC_Filter1Order.h"
#include "DMC_Inertia1order.h"
//#include "DMC_PARK.h"   //headers commented by YP 20180119
#include "DMC_PI.h"     //headers commented by YP 20180119
//#include "DmcLib.h"
#include "Exciting_Current.h"
//#include "filter.h"
//#include "iClarke.h"    //headers commented by YP 20180119
#include "Interg.h"
//#include "ipark.h"    //headers commented by YP 20180119
#include "LPF.h"    //headers commented by YP 20180119

#include "Ratelimit.h"
#include "Rms_out.h"

#include "Slip.h"
#include "speed_kpki.h"
#include "vc_slvc_parameter.h"
#include "Vector_SpeedTest.h"
#include "Vectorcontrol.h"
    //headers added by YP 20180119
#include "Svpwm.h"
#include "common_struct.h"
#include "PMSM_Control.h"
#endif
//===========================================================================
// No more
//===========================================================================
