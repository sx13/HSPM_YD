/*
// Version: V1.0
// Date: 	Mar 3, 2013
// Author:	KEGY @YD
//===========================================================================
//
// 文件名:    SPEED_KPKI.h
//
// 用途:   	  转速环KpKi计算
//
// 说明：
//===========================================================================
*/
typedef struct {  
				  /*输入变量*/
				  float32  fFrRef;  	        // 输入: 给定频率
				  
				  /*输入参数*/  
				  Uint16   uMethod;		        // 参数: 矢量控制方法选择 
				  float32  fSpdKpmin_VC;		// 参数: VC速度环Kp最小值 
				  float32  fSpdKpmax_VC;        // 参数: VC速度环Kp最大值
				  float32  fSpdKpmin_SLVC;		// 参数: SLVC速度环Kp最小值 
				  float32  fSpdKpmax_SLVC;      // 参数: SLVC速度环Kp最大值
				  float32  fSpdKi_VC_SLVC;      // 参数: 速度环Ki

				  /* 输出 */
				  float32  fSpdKp;		        // 输出：速度环Kp
				  float32  fSpdKi;		        // 输出：速度环Ki

				  /*函数*/
				  void     (*pfnCalc)();		// 计算函数指针
				  void     (*pfnReset)();	    // 复位函数指针
				 
				 } SPEEDKPKI;	            

#define SPEEDKPKI_DEFAULTS {  0,\
	                          0,2.0,4.0,2.0,4.0,0.1,\
							  2.0,0.1,\
							  (void (*)(Uint32))fnSppiCalc,\
							  (void (*)(Uint32))fnSppiReset }   
//===========================================================================
//SPEEDKPKI的操作函数申明
void fnSppiCalc(SPEEDKPKI *p);
void fnSppiReset(SPEEDKPKI *p);



//===========================================================================
// No more.
//===========================================================================
