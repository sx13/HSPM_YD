/* =================================================================================
File name:       Vectors_ExciteCurr.H                     
                    
Originator:	justin_zh@yeah.net 

Description: 同步电机气息磁场控制头文件


=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-06-2014	Version 1.0                                                 
------------------------------------------------------------------------------*/
#ifndef VECTOR_EXCITECURR_H
#define VECTOR_EXCITECURR_H

typedef struct {  /*输入变量*/
				  float32  fFref;       //输入：给定频率
				  float32  fPhxAct;     //输入：当前转子磁链

				  /*输入参数*/
				  float32  fFrLow;      //参数：励磁闭环作用的频率拐点
				  float32  fExCurrSet;  //参数：励磁电流外部给定
				  float32  fPhxRef;     //参数：实际转子励磁
				  float32  fPhxKp;      //参数：转子励磁Kp
				  float32  fPhxKi;      //参数：转子励磁Ki
				  float32  fPhxUpLmt;   //参数：转子励磁环输出最大值
				  float32  fPhxLwLmt;   //参数：转子励磁环输出最小值
				  
				  //==中间变量=======
				  float32   fPhxUpTemp;
				  float32   fPhxLwTemp;
                  
				  /*输出变量*/
				  float32  fExCurrOut;  //输出：励磁电流给定

		 	 	  void  (*pfnCalc)();
		 	 	  void  (*pfnReset)();	 
				 } SYNEXCITECURRENT;	            

typedef SYNEXCITECURRENT *SYNEXCITECURRENT_handle;

/*-----------------------------------------------------------------------------
Default initalizer for the SYNEXCITECURRENT object.
-----------------------------------------------------------------------------*/                     
#define SYNEXCITECURRENT_DEFAULTS {  0,0.0,\
                                 0.2,0.0,0.98,0.0,0.0,0.3,-0.3,\
								 0.2,\
                                 0,0,\
              			         (void (*)(Uint32))fnExCurr_Calc,\
              			         (void (*)(Uint32))fnExCurr_Reset}
              			  
/*------------------------------------------------------------------------------
Prototypes for the functions in Vectors_ExciteCurr.C
------------------------------------------------------------------------------*/
void fnExCurr_Calc(SYNEXCITECURRENT_handle);
void fnExCurr_Reset(SYNEXCITECURRENT_handle);

#endif
//============end of the file ===========
//==========no more======================


