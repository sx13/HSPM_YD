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
#pragma CODE_SECTION(fnCalFilter1order, "ramfuncs")
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
		 	 	  void  (*pfnIniFilter1order)();      //初始化函数指针
				  void  (*pfnCalFilter1order)();      //计算函数指针
				  void  (*pfnResFilter1order)();      //复位函数指针
				 } SFILTER1OR;
				 
typedef SFILTER1OR *sFilter1order_handle;	
/*-----------------------------------------------------------------------------
初始化滤波器
-----------------------------------------------------------------------------*/                     
#define SFILTER1OR_DEFAULTS { 0.0, 0.0, 0.0, \
                                 0.0, \
                                 0.0, 0.0, 0.0, 0.0, 0.0, \
                                 (void (*)(Uint32))fnIniFilter1order,\
              			         (void (*)(Uint32))fnCalFilter1order,\
              			         (void (*)(Uint32))fnResFilter1order }
//#define PI 3.1415926
/*------------------------------------------------------------------------------
Prototypes for the functions in CLARKE.C
------------------------------------------------------------------------------*/
void fnIniFilter1order(sFilter1order_handle);
void fnCalFilter1order(sFilter1order_handle);
void fnResFilter1order(sFilter1order_handle);

