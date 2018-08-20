
/* File name:        INTERG.h     */              
#pragma CODE_SECTION(fnInterg_Calc, "ramfuncs")                    

typedef struct {  
                 /*输入变量*/
				  float32  fIn;
				 /*设置参数*/
				  float32  fKp;				// 
				  float32  fTs;				//  
				  float32  fUpLmt;	    	// 上限值
				  float32  fLwLmt;   		// 下限值
				  float32  fFlag;
				  float32  fKs;  

				  /*中间变量*/
				  float32  fOutformer;		     	// 
				  float32  fInformer;

				  /*输出变量*/
				  float32  fOut;			    // 


		 	 	  void  (*pfnCalc)();	  	// Pointer to calculation function
				 } INTERG;	           


/*-----------------------------------------------------------------------------
Default initalizer for the VIMC_pid object.
-----------------------------------------------------------------------------*/                     
#define INTERG_DEFAULTS {  0, \
                           0,0,30000.0,-30000.0,0,1, \
						   0,0,\
						   0,\
              			  (void (*)(Uint32))fnInterg_Calc }

void fnInterg_Calc(INTERG *p);

