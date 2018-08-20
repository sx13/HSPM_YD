/*
// Version: V1.0 文件创建
// Date: 	Dec 12, 2012
// Author:	chenchangjiang @YD
//==========================================================================
//
// 文件名:	SysCtl_GlobalVar.h
//
// 用途:    全局结构体外部声明
//
//==========================================================================
*/

#ifndef SYSCTL_GlOBALVAR_H
#define SYSCTL_GlOBALVAR_H

#define BUF_SIZE   0x80  // Sample buffer size
#define FltWord_DSPtoARM   *(volatile Uint16*)&DMABuf1[98] //DSP故障字传递至ARM
#define FreqEn_DSPtoARM   *(volatile Uint16*)&DMABuf1[100] //频率计算使能
#define DAC_DSPtoARM1      *(volatile float32*)(0x200040)//周期性DAC数据传递
#define DAC_DSPtoARM2      *(volatile float32*)(0x200042)//周期性DAC数据传递
#define StMach_ARMtoDSP    *(volatile Uint16*)(0x280500) //ARM状态机
#define FreqRef_ARMtoDSP   *(volatile float32*)(0x280502)//周期性DAC数据传递
#define BaseAddr_OffsetCal   928
//=================系统故障索引结构体========================================
struct SysErrIndex_BITS {                                 // bits	description
                          Uint16  SysHFaultFlag:1;        //系统重故障标志

						  Uint16  rsvd:15;
                          };
union SysErrIndex_REG {
                       Uint16			      	 all;
                       struct SysErrIndex_BITS   bit;
                      };

//=================ARM故障标志========================================
struct ARMErr_BITS {                                 // bits	description
                          Uint16  ARMHFaultFlag:1;        //系统重故障标志
						  Uint16  rsvd:15; 
                          };
union ARMErr_REG   {
                       Uint16			     all;
                       struct  ARMErr_BITS   bit;
                    };
//=================DSP故障标志========================================
struct DSPErr_BITS {                                 // bits	description
                          Uint16  OCFaultFlag:1;        //系统重故障标志
						  Uint16  rsvd:15; 
                    };
union DSPFault_REG   {
                       Uint16			     all;
                       struct  DSPErr_BITS   bit;
                     };

struct SysCtl_BITS {		                   // bits	description
                     Uint16    StartInstr:1;   //启动指令
					 Uint16    StopInstr:1;    //停机指令
					 Uint16    EStopInstr:1;   //急停指令					 
					 Uint16    ResetInstr:1;   //复位指令
                     Uint16    OffSetInst:1;  //系统零漂指令
					 Uint16    LVDebugInst:1;  //低压调试指令
					 Uint16    MotorReverEn:1; //电机反转
					 Uint16    HVDebugInst:1;  //电机测参数指令
					 Uint16    SynSwitchInst:1;//同步投切指令
					 Uint16    ErrMaskInstr:1; //故障屏蔽
                     Uint16    rsvd:6;         // 7-15 reserved
                    };
union SysCtl_REG   {
                     Uint16	   all;
                     struct SysCtl_BITS   bit;
                    };

//===== 低压调试结构体 ====================================
typedef struct {
                //
				Uint16  uLVDebugEN;
                float32 fTheta_base;//相位计算
				float32 fUu_base;//U相调制波
				float32 fUv_base;//U相调制波
				float32 fUw_base;//U相调制波

				float32 fUuBoost;
				float32 fUvBoost;
				float32 fUwBoost;

				Uint16 uUu_Fib;
				Uint16 uUv_Fib;
				Uint16 uUw_Fib;
                }LVDebugTEST;

                //初始值
#define LVDebug_DEFAULTS {0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}
//===== 系统控制结构体 ====================================
typedef struct {
				//
				Uint16  uStartMode;

				}TypeSYSCTRL;

				//初始值
#define SYSCtrl_DEFAULTS {0}
//===== 保护参数结构体 ================================
typedef struct {
                //参数
				float32 fOCProtect;//过流保护值 
                float32 fOCProtect_Per;//过流保护标幺值  

                } TypeSysProParameter;
                 
                //初始值
#define SysProParameter_DEFAULTS {0.0,0.0}
//===== 波形上传结构体 ====================================
typedef struct {
                float32 VarScope[30];
				Uint16 ScopeCount;
                }SCOPEDATA;

                //初始值
#define ScopeData_DEFAULTS {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,\
                             0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},0}

//=================额定值参数=========================================
typedef struct {
                float32 fMotorRatedVoltage;//电机额定电压
				float32 fMotorRatedCurrent;//电机额定电流
				float32 fMotorRatedFre;//电机额定频率
				float32 fMotorRatedPower;//电机额定功率
				float32 fMotorRateSpeed;//电机额定转速，转/分
				float32 fMotorPoleNum;//电机极对数
				float32 fMotorRatedSlip;//电机转差率
				float32 fVFDInputVolatge;//变频器额定输入电压
				float32 fVFDInputCurrent;//变频器额定输入电流
				float32 fVFDRatedPower;//变频器额定功率
				float32 fVFDInputFre;//变频器额定输入频率
				float32 fVFDOutputVoltage;//变频器额定输出电压
				float32 fVFDOutputCurrent;//变频器额定输出电流
                } TypeSysRatedParameter;
//================额定参数默认变量初始化===============================
#define SysRatedParameter_DEFAULTS {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}
//===== 系统基值结构体 ====================================
typedef struct {   
                //输出
				float32  fVoltBaseValueGrid;   //系统输出电压基值
				float32  fVoltBaseValue;   //系统输出电压基值
				float32  fCurrBaseValue;   //系统电流基值
				float32  fSpeedBaseValue;  //系统转速基值
				float32  fThetaBaseValue;  //系统电角度基值
				float32  fPowerBaseValue; //系统功率基值
				float32  fZBaseValue;//系统阻抗基值
				float32  fYBaseValue; //系统导纳基值  added by yp
				float32  fLBaseValue;//系统电感基值
				float32  fPhirBaseValue;//系统磁链基值
				float32  fOmegBaseValue;//系统机械角度基值
				float32  fTeBaseValue;//系统转矩基值
				float32  fJBaseValue;//转动惯量基值
				float32  fFBaseValue;//摩擦系数基值
				float32  fHBaseValue;//惯性时间常数基值

				//函数
				  void   (*pfnSysBaseValueCal)();//系统基值计算
			   } TypeSysBaseValue;

                //初始值
#define SysBaseValue_DEFAULTS {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0, \
                               0.0,0.0,0.0,0.0,0.0,0.0,0.0, \
                               (void (*)(Uint32))fnSysBaseValueCal, \
                               }
//=================环境参数设定=========================================

typedef enum {
				AsynMotor = 0,       //异步电机
				SynMotor = 1,        //同步电机
				Reactor = 2         //电抗器

			} TypeSysVFDLoad;   //负载类型

typedef enum {
				PGVVVF = 0,         //VVVF
				NPGVVVF = 1,      //VVVF
				VC = 2,             //VC
				SLVC = 3            //SLVC

			} TypeSysControlStrat;  //控制策略
typedef struct {
			     Uint16 uConRunType;//变频器类型
			     TypeSysVFDLoad uVFDLoadType;//负载类型
			     TypeSysControlStrat uConStrat;//电机控制策略

			   } TypeSysEnvironParameter;
//================环境参数默认变量初始化===============================
#define SysEnvironParameter_DEFAULTS {0,AsynMotor,NPGVVVF}

extern void fnSysBaseValueCal(TypeSysBaseValue *p);
extern TypeSysMoore SysMoore;
extern LVDebugTEST SysLVDebug;
extern union  SysErrIndex_REG SysErrIndexReg;
extern union SysCtl_REG SysCtlReg;
extern union ARMErr_REG ARMFaultReg;
extern union DSPFault_REG DSPFaultCodeReg;
extern TypeSysProParameter SysProParamReg;
extern SCOPEDATA *ScopeDATAUpLoad;
extern TypeSysRatedParameter SysRatedParameter;
extern TypeSysBaseValue SysBaseValue;
extern TypeSysEnvironParameter SysEnviConfg;
extern TypeSYSCTRL SysCtlParameter;
extern void fnSysHMICommInit(void);
extern void fnSysFreCalHMI(void);
extern void fnSystemInitParam(void);
extern void fnSysFreCalInit(void);
extern void fnVFBaseCalculusCal(LVDebugTEST *p);
extern void fnSysCtlLvDebug(void);
extern void fnVarScopeAssign(void);

//extern void InitAlgorithm(void);
//extern void Algorithm(void);


extern Uint32  uDMA_Addr;
extern volatile Uint16 DMABuf1[BUF_SIZE];
extern volatile Uint16 *DMADest1;
extern volatile Uint16 *DMASource1;
extern volatile Uint16 *RdDSPtoARM;
extern volatile Uint16 *pARMParamRdFlag;
extern volatile float32 *pOffsetRam;
extern volatile Uint16 *pWaveParamStart;

//extern INTERG Interg_Vector;
//extern VECTOR_ST SpeedTest;
//extern PIREG PhrPI;
extern Uint16 uDirCount;
extern Uint16 uDirCountMax;
extern Uint32 CNT_FR_VALUE;
extern float32 CutOff_Freq;
#endif  

