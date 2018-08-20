/*
// Version: V1.0 文件创建
//
// Date: 	Dec 18, 2017
//
// Author:	chenchangjiang @YD
//===================================================================
//
// 文件名:	SysCtl_AnalogProcess.h
//
// 用途:    模拟量控制结构体

//===================================================================
*/
#ifndef SYSCTRL_ANALOGPROCESS_H
#define SYSCTRL_ANALOGPROCESS_H

//============= 模拟输入控制结构体 ================================
typedef struct {
	            //输入
	            int    iSysADResult[8];
                //参数
				float32 fAnaInTs;        //模拟采样周期
				float32 fLVoltAB;
				float32 fLVoltBC;
				//输出

				float32 fFreGivenAna;    //模拟给定频率
				float32 fADResult_Offset[12];//系统模拟量（输入输出电流、电压）零漂前采样值
				float32 fADResult_Offseted[12];//系统模拟量（输入输出电流、电压）扣除零漂后的采样值
				float32 fADResult[9];		  //采样实际值
                int uADResultAnaIn[16];           //片上AD结果寄存器
				//计算函数
				void (*pfnAISample)();//模拟采样结果函数
              //  void (*pfnInit)();//初始化函数

                }TypeAnalogInput;

//============= 模拟输入默认变量初始化 =============================
#define AnalogInput_DEFAULTS {{0},0.0,0.0,0.0,0.0,{0},{0},{0},{0}, \
							  (void (*)(Uint32))fnAISample\
                              }
//============= 模拟输入处理函数声明 ==============================
void fnAISample(TypeAnalogInput *p);

typedef struct {
                //状态量
	            Uint16  uSampleOffsetEn;//零漂使能
	            Uint16  SampOffsetOnce;//读取零漂结果单次触发
				Uint16  uOffsetCount;//零漂计数
                Uint16  uOffsetCounter;//零漂计数
                float32 fOffsetValue[12];//DSP运算零漂值
				float32 fOffsetAdd[12];
				float32 fOffsetUpValue[12];//DSP运算零漂上传值

				//函数声明
                void (*pfnSysOffsetInit)();//零漂参数初始化函数
				void (*pfnSysOffsetParameterCal)();//零漂参数计算函数
               }TypeSysOffsetParameter;

#define SysOffsetParameter_DEFAULTS {0,0,0,0,\
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0},{0}, \
                                     (void (*)(Uint32))fnSysOffsetInit, \
                                     (void (*)(Uint32))fnSysOffsetParameterCal, \
                                     }

//=================采样整定参数=========================================
typedef struct {
                float32 fSysSamValue[12];
				float32 fSysSamOutCRatio;
				float32 fSysSamOutCSamR;
				float32 fSysSamOutVDividR;
				float32 fSysSamOutVDCR;
				float32 fSysSamDCVoltage;
				float32 fSysSamOutVoltage;
				float32 fSysSamOutCurrent;
				float32 fSysSamNTC1;
				float32 fSysSamNTC2;
                } TypeSysSamScaParameter;
//================采样整定参数默认变量初始化===============================
#define SysSamScaParameter_DEFAULTS {{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}

//=================DSP采样数据传递至ARM=========================================
typedef struct {
				float32 fSamDSPtoARMIu;
				float32 fSamDSPtoARMIv;
				float32 fSamDSPtoARMIw;

				float32 fSamDSPtoARMUu;
				float32 fSamDSPtoARMUv;
				float32 fSamDSPtoARMUw;

				float32 fSamDSPtoARMUdc;
				float32 fSamDSPtoARMNTC1;
				float32 fSamDSPtoARMNTC2;

				} TypeSamDSPtoARM;
//================采样数据变量传递至ARM===============================
#define TypeSamDSPtoARM_DEFAULTS {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}
//=================DA数据选择=========================================
typedef struct {
				Uint16 uDA_NumCh1;//通道1编号
				Uint16 uDA_NumCh2;//通道2编号

				float32 fDA_DataCh1;//通道1数据
				float32 fDA_DataCh2;//通道2数据
				} TypeDAChoose;
//================DA数据传递至ARM===============================
#define TypeDAChoose_DEFAULTS {0,0,0.0,0.0}
//============ 全局变量与全局函数声明 =============================

extern TypeAnalogInput AnalogInput;

extern TypeSysOffsetParameter SysSampOffset;

extern TypeSysSamScaParameter SysSamScaParameter;

extern TypeSamDSPtoARM  SysSamDSPtoARM;

extern TypeDAChoose DAOut;

void fnSysOffsetInit(TypeSysOffsetParameter *p);

void fnSysOffsetParameterCal(TypeSysOffsetParameter *p);

extern void fnParaUpdateSysSamScaParameter(void); 

//extern void fnWhileAISample(void);

#endif
//========================================================================
// No more.
//========================================================================


