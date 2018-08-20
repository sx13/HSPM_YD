/*
// Version: V1.0 文件创建
// Date: 	Oct 25, 2012
// Author:	csc @YD
//==========================================================================
//
// 文件名:	DMC_PI.h
//
// 用途:   PI头文件
//
//==========================================================================
*/
/*初始化
sPi.fKp 		= 0;
sPi.fKi 		= 0;
sPi.fSampleFreq = 5000;
sPi.fOutMax		= 1;
sPi.fOutMin		= -1;
sPi.fIntgInit	= 0;
sPi.pfnInit(&//sPi);
*/
/*调用
sPi.fRef1 = 0;
sPi.fRef2 = 0;
sPi.fFdb1 = 0;
sPi.fFdb2 = 0;
sPi.pfnCalc(&//sPi);
*/
#pragma CODE_SECTION(fnPiCalc, "ramfuncs")

//==========================================================================
// PI状态字
struct PI_SW_BITS {		// bits	description
    Uint16  IntgULmt:1;     // 0	积分上限	
	Uint16  IntgLLmt:1;		// 1   	积分下限
	Uint16  OutULmt:1;		// 2	输出上限
	Uint16  OutLLmt:1;		// 3	输出下限
    Uint16  rsvd:12;      	// 4~15 reserved
};
union PI_SW_REG {
   Uint16				all;
   struct PI_SW_BITS   bit;
};

//==========================================================================
// PI结构体
typedef struct {  
				  //输入
				  float32  fRef1;   	// 输入: 参考输入1
				  float32  fRef2;		// 输入: 参考输入2
				  float32  fFdb1;   	// 输入: 反馈输入1
				  float32  fFdb2;		// 输入: 反馈输入2
				   
				  /*输入参数*/
				  float32  fKp;			// 参数: 比例系数
				  float32  fKi;			// 参数: 积分系数
				  float32  fSampleFreq;	// 参数：采样频率
				  float32  fOutMax;		// 参数: 上限值 
				  float32  fOutMin;		// 参数: 下限值
				  float32  fIntgInit;	// 参数: 积分初始值

				  /*状态变量*/
				  float32  fErr;		// 变量：误差，给定-反馈
				  float32  fKiTs;		// 变量：积分系数，Ki/SampleFreq
				  float32  f2Intg;		// 变量: 积分累加器

				  /*输出*/
				  float32  fOut;   			// 输出: PI输出
				  union    PI_SW_REG sPiSw; // 输出: PI状态字

				  /*函数*/
				  void     (*pfnCalc)();		// PI计算函数指针
				  void     (*pfnReset)();		// PI复位函数指针
				  Uint16   (*pfnInit)();		// PI初始化函数指针
				 } PIREG;	            

//===========================================================================
//PIREG的默认初始化变量

#define PIREG_DEFAULTS { 0,0,0,0,\
						  0,0,0,0,0,0,\
						  0,0,0,\
						  0,0,\
						  (void (*)(Uint32))fnPiCalc,\
						  (void (*)(Uint32))fnPiReset,\
						  (Uint16 (*)(Uint32))fnPiInit }

//===========================================================================
//PIREG的操作函数申明
void fnPiCalc(PIREG *p);
void fnPiReset(PIREG *p);
Uint16 fnPiInit(PIREG *p);


//===========================================================================
// No more.
//===========================================================================
