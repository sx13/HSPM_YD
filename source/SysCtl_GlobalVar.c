
/*
//===========================================================================
//
// 文件名:    SysCtl_GlobalVar.c
//
// 用途:   	  系统全局结构体变量定义
//
//===========================================================================
*/
#include "DSP2833x_Device.h"
#include "SysCtl_AllHeaders.h"
#pragma DATA_SECTION(DMABuf1,"DMARAML4");
Uint16 HMIBuffer[2000] = {0};
Uint32  uDMA_Addr = 0;
volatile Uint16 DMABuf1[BUF_SIZE];//DMA数据缓冲区
volatile Uint16 *DMADest1 = (volatile Uint16 *)0x200000;
volatile Uint16 *DMASource1;
volatile Uint16 *pARMParamRdFlag = (volatile Uint16 *)0x2803fc;//ARM芯片参数准备就绪标志，DSP读到0xCE认为ARM就绪
volatile Uint16 *RdDSPtoARM = (volatile Uint16 *)0x2803fd;  //DSP芯片主循环正常，循环写0xfa
volatile float32 *pOffsetRam = ((float32*) (HMIBuffer + 928));  //读零漂设置值起始地址
volatile Uint16 *pWaveParamStart = (volatile Uint16 *)0x200020; //波形参数传递起始地址DSP->ARM

TypeSysMoore SysMoore = SysMoore_DEFAULTS;
TypeSysRatedParameter SysRatedParameter = SysRatedParameter_DEFAULTS;
union SysErrIndex_REG SysErrIndexReg;
union SysCtl_REG  SysCtlReg;
union DSPFault_REG DSPFaultCodeReg;
union ARMErr_REG ARMFaultReg;
COMMUN sInComm = COMM_DEFAULTS;
SCOPEDATA *ScopeDATAUpLoad = (SCOPEDATA*)&HMIBuffer[1384];//csv地址映射

TypeSysOffsetParameter SysSampOffset = SysOffsetParameter_DEFAULTS;
TypeSysSamScaParameter SysSamScaParameter = SysSamScaParameter_DEFAULTS;
TypeSysProParameter SysProParamReg = SysProParameter_DEFAULTS;
TypeSysBaseValue SysBaseValue = SysBaseValue_DEFAULTS;
TypeSamDSPtoARM  SysSamDSPtoARM = TypeSamDSPtoARM_DEFAULTS;
TypeAnalogInput AnalogInput = AnalogInput_DEFAULTS;
TypeSysEnvironParameter SysEnviConfg = SysEnvironParameter_DEFAULTS;
TypeDAChoose DAOut = TypeDAChoose_DEFAULTS;
TypeSYSCTRL SysCtlParameter = SYSCtrl_DEFAULTS;

//===========算法=======
TypeVoltBaseCal  SysVoltBase = SysVoltBaseCal_DEFAULTS; //系统电压基波计算
TypeSysConTestParam  SysConTest = SysConTestParam_DEFAULTS;//电抗器测试
TypeSysVVVFCal  SysVVVFCtrl = VVVFVal_DEFAULTS;  //VVVF控制结构体

//=========================矢量控制====================

VCANDSLVCORPARA VC_SLVC_PARAMETER = VCANDSLVCORPARA_DEFAULTS;
VECTOR_ST SpeedTest = VECTOR_ST_DEFAULTS;
CLARKE Vol_clarke = CLARKE_DEFAULTS;
ICLARKE Vol_iclarke = ICLARKE_DEFAULTS;
IPARK Vol_ipark = IPARK_DEFAULTS;
CLARKE Cur_clarke = CLARKE_DEFAULTS;
//CLARKE OutVolt_clarke = CLARKE_DEFAULTS;
PARK Cur_park = PARK_DEFAULTS;
LPF_PLL2  LPF_W = LPF_PLL_DEFAULTS2;
LPF_PLL3 Spd_LPF = LPF_PLL_DEFAULTS3;
RATELIMIT Ratelimit = RATELIMIT_DEFAULTS;
INTERG Interg_phsAlpha = INTERG_DEFAULTS;
INTERG Interg_phsBeta = INTERG_DEFAULTS;
INTERG Interg_Deta = INTERG_DEFAULTS;
INTERG Interg_Vector = INTERG_DEFAULTS;
//INTERG interg_pf = INTERG_DEFAULTS;
PIREG SpeedTestPI = PIREG_DEFAULTS;
PIREG SpeedControl = PIREG_DEFAULTS;
PIREG CurrentControl_M = PIREG_DEFAULTS;
PIREG CurrentControl_T = PIREG_DEFAULTS;
PIREG PhrPI = PIREG_DEFAULTS;
SLIP Slipspeed = SLIP_DEFAULTS;
EXCITCURRENT ExcitingCurrent = EXCITCURRENT_DEFAULTS;
VECTORCONTROL Vector_Control = VECTORCONTROL_DEFAULTS;
SFILTER1OR CurrentFilter_D = SFILTER1OR_DEFAULTS;
SFILTER1OR CurrentFilter_Q = SFILTER1OR_DEFAULTS;
//PARAMETERTEST Parameter_Test = PARAMETERTEST_DEFAULTS;
//RMS_OUT Rms_Para_Vol = RMS_OUT_DEFAULTS;
//RMS_OUT Rms_Para_Cur = RMS_OUT_DEFAULTS;
//RMS_OUT Rms_Grid_PhaseVolt = RMS_OUT_DEFAULTS;
SPEEDKPKI SpeedKpKi = SPEEDKPKI_DEFAULTS;
SFILTER1OR ErFilter1_Alpha = SFILTER1OR_DEFAULTS;
SFILTER1OR ErFilter2_Alpha = SFILTER1OR_DEFAULTS;
SFILTER1OR ErFilter3_Alpha = SFILTER1OR_DEFAULTS;
SFILTER1OR PhrCurFilter_Alpha = SFILTER1OR_DEFAULTS;
SFILTER1OR ErFilter1_Beta = SFILTER1OR_DEFAULTS;
SFILTER1OR ErFilter2_Beta = SFILTER1OR_DEFAULTS;
SFILTER1OR ErFilter3_Beta = SFILTER1OR_DEFAULTS;
SFILTER1OR PhrCurFilter_Beta = SFILTER1OR_DEFAULTS;
INTERG Interg_PhrVolAlpha = INTERG_DEFAULTS;
INTERG Interg_PhrVolBeta = INTERG_DEFAULTS;
INERTIA1OR Inertia_PhrVolAlpha = INERTIA1OR_DEFAULTS;
INERTIA1OR Inertia_PhrVolBeta = INERTIA1OR_DEFAULTS;
SPDESTCURVOL SpeedTest_CurVol = SPDESTCURVOL_DEFAULTS;
CLARKE CurPhr_clarke = CLARKE_DEFAULTS;
CLARKE VolPhr_clarke = CLARKE_DEFAULTS;
PIREG SpeedTestPI_CurVol = PIREG_DEFAULTS;
INTERG Interg_CurVol = INTERG_DEFAULTS;
//float32 fFrAct;
Uint16 uInterCount = 0;
Uint32 uSoftStartCount = 0;
//Uint16 uGridCount = 0;
Uint16 uDirCount=0;
Uint16 uDirCountMax=0;

PMSM_Control PMSM = PMSM_Control_DEFAULTS;  //Added by YP 20180119
float fTimeCount = 0.0;

Uint16 SquareCount = 0;
float iq_load = 0.06;	//Added by SX 20180422
//VCTRLPARAM VectorCtrlPAMA = VCTRLPARAM_DEFAULTS;
//VCTRLPARAM SynVectorCtrlPAMA = VCTRLPARAM_DEFAULTS;
//===========================================================================
// No more.
//===========================================================================
