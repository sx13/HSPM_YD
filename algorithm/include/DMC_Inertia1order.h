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

typedef struct {  //输入
                  float32  fInput;  	// 输入变量  
				  float32  fSampFre;	// 采样频率  
				  float32  fCutFre;	    // 截止频率(Hz) 
				  float32  fKp;         // 放大系数
                  
				  //输出
				  float32  fOutput;	    // 滤波输出变量

				  //中间变量
                  float32  fOutputOld;  //上一采样周期输出值
				  float32  fInputOld;
				  float32  fA0;         //计算系数
				  float32  fA1;         //计算系数
				  float32  fB0;         //计算系数

			      //函数
		 	 	  void  (*pfnIniInertia1order)();      //初始化函数指针
				  void  (*pfnCalInertia1order)();      //计算函数指针
				  void  (*pfnResInertia1order)();      //复位函数指针
				 } INERTIA1OR;
				 
typedef INERTIA1OR *sInertia1order_handle;	
/*-----------------------------------------------------------------------------
初始化滤波器
-----------------------------------------------------------------------------*/                     
#define INERTIA1OR_DEFAULTS { 0, 0, 0, 1,\
                                 0, \
                                 0, 0, 0, 0, 0,\
                                 (void (*)(Uint32))fnIniInertia1order,\
              			         (void (*)(Uint32))fnCalInertia1order,\
              			         (void (*)(Uint32))fnResInertia1order }
//#define PI 3.1415926
/*------------------------------------------------------------------------------
Prototypes for the functions in CLARKE.C
------------------------------------------------------------------------------*/
void fnIniInertia1order(sInertia1order_handle);
void fnCalInertia1order(sInertia1order_handle);
void fnResInertia1order(sInertia1order_handle);

