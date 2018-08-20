
/*
//===========================================================================
//
// 文件名:	sysCtl_ConstDef.h
//
// 用途:	
//		1. 定义标准数据类型
//		2. 定义数学常数
//		3. 定义DSP时钟频率及相关设置常量
//		4. 定义其它测试用常量
//
//===========================================================================
*/

#ifndef SYSCTL_CONSTDEF_H
#define SYSCTL_CONSTDEF_H

//===========================================================================
// 定义28335的数据类型
//===========================================================================
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int                int16;
typedef long               int32;
typedef long long          int64;
typedef unsigned int       Uint16;
typedef unsigned long      Uint32;
typedef unsigned long long Uint64;
typedef float              float32;
typedef long double        float64;
#endif
//==========  逻辑常量定义  ==========
#define TRUE		1
#define FALSE		0
//==========  CPU时钟设置.  ====================
//	SYSCLKOUT = CLKIN * DSP28_PLLCR / N(DSP28_DIVSEL)
//	CLKIN is a 30MHz;  DSP28_PLLCR=10;   DSP28_DIVSEL=2;
// 	SYSCLKOUT = 150 MHz
//======================================================

#define NORMALMOD           0x00   //正常起动
#define FLYMOD              0x01   //飞车起动
#define BRAKEMOD            0x02   //制动起动

//===== 故障类型宏定义 ======

#define HErr_OVFault              0x80   //过压
//======计算常数宏定义=======
#define fPeriodCounter       2500 //27719.0
#define uPeriodCounter       25000
#define PeriodTimeus          500.0
#define PeriodTime (fusToS)*(PeriodTimeus)//系统控制周期，S单位
                                         //
#define D1ByPeriod (1.0)/(PeriodTimeus)//周期倒数
                                       //
#define uSTous 1000000.0//s 转换us转换系数
                        //
#define TimerCoffic (uSTous)*(D1ByPeriod)//定时器时间系数
                                         //
#define fusToS 0.000001//us转换S系数
                       //
#define KAnalog 0.0004884//  2/4095   ///0.00015259022//AD采样换算系数10/65535
                              //
//#define DC_VoltScalCoe  0.5979004//0.322372// 1000/3102 直流母线电压计算系数//15.7.1ZH.J 改为 2449/4096

#define Rec_CurrScalCoe 0.6105// 2500/4095整流侧电流计算系数

#define PowerCalLPFCutFre 30.0//
                              //
#define PowerCalLPFSampFre 5988.0//

#define DAOutCoffic 204.75 ///0-20mA

//#define fDetatheta           0.015707963

#define LowSpeed 5.0

#define MidSpeed 25.0

#define HighSpeed 40.0

#define PhseCoffic 0.0014891148924     ///237us

#define AnalogIToVolt 0.12696          //模拟板卡20mA输入转为2.5392V给DSP（2.5392/20 = 0.12696）

#define SpeedObserveUTO 0.009

#define KCapSpeedClk 9000000.0

#define KOmegBase 0.10471975512

#define ParaMesTime 0.2

#define ParaMes_DetaTheta 0.05215

#define VFDCurLPFTCon    0.0104876

#define PI            3.14159265
#define PI2      	  6.28318531 
#define N_PI2		  (-1.0)*(PI2)//                                    //
#define f4_D_3PI      (4.0/3.0)*(PI)//
#define f2_D_3PI      (2.0/3.0)*(PI)//

#define VFPhseCoffic  0.00314159265
#endif  



//===========================================================================
// NO MORE
//===========================================================================

