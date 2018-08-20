/* =================================================================================
File name:       PARK.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the PARK.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                 
------------------------------------------------------------------------------*/

typedef struct {  /*输入变量*/
				  float32  fFref;       //输入：给定频率
				  float32  fPhrAct;     //输入：当前转子磁链

				  /*输入参数*/
				  float32  fFrLow;      //参数：励磁闭环作用的频率拐点
				  float32  fExccurSet;  //参数：励磁电流外部给定
				  float32  fPhrRef;     //参数：实际转子励磁
				  float32  fPhrKp;      //参数：转子励磁Kp
				  float32  fPhrKi;      //参数：转子励磁Ki
				  float32  fPhrUpLmt;   //参数：转子励磁环输出最大值
				  float32  fPhrLwLmt;   //参数：转子励磁环输出最小值
                  
				  /*输出变量*/
				  float32  fExccurOut;  //输出：励磁电流给定

		 	 	  void  (*pfnExcurcalc)();
		 	 	  void  (*pfnExcurreset)();	 
				 } EXCITCURRENT;	            

typedef EXCITCURRENT *EXCITCURRENT_handle;

/*-----------------------------------------------------------------------------
Default initalizer for the PARK object.
-----------------------------------------------------------------------------*/                     
#define EXCITCURRENT_DEFAULTS {  0,0.0,\
                                 0.06,0.3,0.95,0.0,0.0,0.3,-0.3,\
                                 0, \
              			         (void (*)(Uint32))fnExcur_calc,\
              			         (void (*)(Uint32))fnExcur_reset}
              			  
/*------------------------------------------------------------------------------
Prototypes for the functions in PARK.C
------------------------------------------------------------------------------*/
void fnExcur_calc(EXCITCURRENT_handle);
void fnExcur_reset(EXCITCURRENT_handle);


