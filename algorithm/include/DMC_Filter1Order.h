/* =================================================================================
File name:       DMC_Filter.H                     
                    
Originator:	

Description: 一阶滤波器头文件
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 12-29-2012	Version 1.0                                                
------------------------------------------------------------------------------*/
//#define PI  3.1415926
#ifndef _DMC_Filter1Order_h_
#define _DMC_Filter1Order_h_
typedef struct {  //输入
                  float32  fInput;  	// 滤波输入变量  
				  float32  fSampFre;	// 采样频率  
				  float32  fCutFre;	    // 截止频率(Hz) 
                  
				  //输出
				  float32  fOutput;	    // 滤波输出变量

				  //中间变量
                  float32  fOutputOld;  //滤波器上一采样周期输出值
				  float32  fInputOld;   //滤波器上一采样周期输入值
				  float32  fA0;         //滤波器系数
				  float32  fA1;         //滤波器系数
				  float32  fB0;         //滤波器系数

			      //函数
		 	 	  void  (*pfnInit)();      //初始化函数指针
				  void  (*pfnCalc)();      //计算函数指针
				  void  (*pfnRest)();      //复位函数指针
				 } SFILTER1ORDER;
				 
typedef SFILTER1ORDER *SFILTER1ORDER_handle;	
/*-----------------------------------------------------------------------------
初始化滤波器
-----------------------------------------------------------------------------*/                     
#define SFILTER1ORDER_DEFAULTS { 0.0, 0.0, 0.0, \
                                 0.0, \
                                 0.0, 0.0, 0.0, 0.0, 0.0, \
                                 (void (*)(Uint32))fnFilter1OrderInit\
              			         (void (*)(Uint32))fnFilter1OrderCal\
              			         (void (*)(Uint32))fnFilter1OrderReset}
//#define PI 3.1415926
/*------------------------------------------------------------------------------
Prototypes for the functions in CLARKE.C
------------------------------------------------------------------------------*/
void fnFilter1OrderInit(SFILTER1ORDER_handle);
void fnFilter1OrderCal(SFILTER1ORDER_handle);
void fnFilter1OrderReset(SFILTER1ORDER_handle);

#endif

//=====nomore=====


