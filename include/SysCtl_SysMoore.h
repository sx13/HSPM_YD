/*
//===================================================================
//
// 文件名:	SysCtl_Moore.h
//
// 用途:    系统状态机头文件
//
// 结构体：
//         TypeSysMooreState     //系统状态值定义
//         TypeSysMoore          //系统状态机
//
//===================================================================
*/

#ifndef SYSCTL_SYSMOORE_H
#define SYSCTL_SYSMOORE_H


//===== 系统状态定义 ===========================
typedef enum {
				SysErr = 1,         //系统故障
				SysInit = 2,        //系统初始化
				ControllerReady = 3,//控制器就绪
				SysPrecharge = 4,   //系统预充电
				SystemReady = 5,    //系统待机
				SystemRun = 6      //系统运行
             } TypeSysMooreState;

//===== 系统状态机结构体 ====================================
typedef struct {
                //状态值输出
                TypeSysMooreState SysStateNew;//系统新状态值
				TypeSysMooreState SysStateOld;//系统旧状态值

                //函数

				void (*pfnSysMooreCal)();//系统状态机计算

                } TypeSysMoore;

                //初始值
#define SysMoore_DEFAULTS {SystemReady,SystemReady, \
                          (void (*)(Uint32))fnSysMooreCal}

                //函数声明
void fnSysMooreCal(TypeSysMoore *p);

extern void fnVarCopyToRam(Uint16 *HeadAddr,float32 *pVarAddr,Uint16 AddrBias);

extern float fTimeCount;

extern float iq_load;

#endif

//========================================================================
// No more.
//========================================================================

