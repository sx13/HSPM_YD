/* LPF.h */

#define  DETECT_N   200
#define  DETECT_50   5
//***************************************************
//LPF_PLL(均值滤波)
//--------------50次滤波-------------------
typedef struct {  
                  float32   fIn;        
				  int16     iN;
				  float32   fIn_Buf[DETECT_N];                 
				  float32   fOut;  
				  float32   fSum;
		 	 	  void  (*pfnCalc)();	   // Pointer to calculation function
                  void  (*pfnInit)();	   // Pointer to init function
				 } LPF_PLL;	            



/*-----------------------------------------------------------------------------
Default initalizer for the LPF_PLL object.
-----------------------------------------------------------------------------*/                     
#define LPF_PLL_DEFAULTS { 0, \
							   0, \
                               {0}, \
							   0, \
							   0, \
              		    	   (void (*)(  unsigned long)) fnLpf_Pll_Calc,\
              		    	   (void (*)(  unsigned long)) fnLpf_Pll_Init }

/*------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
Default function
-----------------------------------------------------------------------------*/   
//CALC
void fnLpf_Pll_Calc(LPF_PLL *p);
//INIT
void fnLpf_Pll_Init(LPF_PLL *p);


//--------------50次滤波-------------------
typedef struct {  
                  float32   fIn;        
				  int16     iN;
				  float32   fIn_Buf[DETECT_50];                 
				  float32   fOut;  
				  float32   fSum;
		 	 	  void  (*pfnCalc)();	   // Pointer to calculation function
                  void  (*pfnInit)();	   // Pointer to init function
				 } LPF_PLL2;	            



/*-----------------------------------------------------------------------------
Default initalizer for the LPF_PLL object.
-----------------------------------------------------------------------------*/                     
#define LPF_PLL_DEFAULTS2 { 0, \
							   0, \
                               {0}, \
							   0, \
							   0, \
              		    	   (void (*)(  unsigned long)) fnLpf_Pll_Calc2,\
              		    	   (void (*)(  unsigned long)) fnLpf_Pll_Init2 }

/*------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
Default function
-----------------------------------------------------------------------------*/   
//CALC
void fnLpf_Pll_Calc2(LPF_PLL2 *p);
//INIT
void fnLpf_Pll_Init2(LPF_PLL2 *p);
//============================================================================
//--------------50次滤波-------------------
typedef struct {  
                 /*输入*/
                  float32   fIn;          // Input: Ifbk current
				  int16     iN;     //N次滤波

                  /*变量*/
				  float32   fSum;
	              int16     iSumcount;

                 /*输出*/
				  float32   fOut;  
				 
		 	 	  void  (*pfnCalc)();	   // Pointer to calculation function
                  void  (*pfnInit)();	   // Pointer to init function
				 } LPF_PLL3;	            


/*-----------------------------------------------------------------------------
Default initalizer for the LPF_PLL object.
-----------------------------------------------------------------------------*/                     
#define LPF_PLL_DEFAULTS3 { 0, \
							   0, \
							   0, \
							   0, \
							   0, \
              		    	   (void (*)(  unsigned long)) fnLpf_Pll_Calc3,\
              		    	   (void (*)(  unsigned long)) fnLpf_Pll_Init3 }

/*------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
Default function
-----------------------------------------------------------------------------*/   
//CALC
void fnLpf_Pll_Calc3(LPF_PLL3 *p);
//INIT
void fnLpf_Pll_Init3(LPF_PLL3 *p);


