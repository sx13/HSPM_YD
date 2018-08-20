/*
// Version: V1.0
// Date: 	Mar 3, 2013
// Author:	csc @YD
//===========================================================================
//
// 文件名:    DMC_PARK.h
//
// 用途:   	  PARK变换
//
// 说明：
//===========================================================================
*/
#pragma CODE_SECTION(fnParkCalc, "ramfuncs")

typedef struct {  
				  // 输入
				  float32  fAlpha;  	// 输入: alpha输入  
				  float32  fBeta;		// 输入: beta输入 
				  float32  fCos;		// 输入: cos输入 
				  float32  fSin;        // 输入：sin输入
				  // 输出
				  float32  fDOut;		// 输出：D轴
				  float32  fQOut;		// 输出：Q轴

				 /*函数*/
				 void     (*pfnCalc)();		// CLARKE计算函数指针
				 void     (*pfnReset)();	// CLARKE复位函数指针
				 void     (*pfnInit)();		// CLARKE初始化函数指针
				 
				 } PARK;	            

#define PARK_DEFAULTS { 0,0,0,0,\
						  0,0,\
						  (void (*)(Uint32))fnParkCalc,\
						  (void (*)(Uint32))fnParkReset,\
						  (void (*)(Uint32))fnParkInit }   
//===========================================================================
//PARK的操作函数申明
void fnParkCalc(PARK *p);
void fnParkReset(PARK *p);
void fnParkInit(PARK *p);


//===========================================================================
// No more.
//===========================================================================
