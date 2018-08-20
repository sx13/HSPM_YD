
/*File name:       RATELIMIT.h*/                     
                    


typedef struct { 
                  float32  fNewData;
				  float32  fOldData;
                  float32  fErr;  	//
                  float32  fK;  
				  float32  fKUpLmt;	// 
				  float32  fKLwLmt;	//
				  float32  fOut; 
				  float32  fOutUpLmt;
				  float32  fOutLwLmt; 
		 	 	  void  (*pfnCalc)();//  
				 } RATELIMIT;	            


/*-----------------------------------------------------------------------------
Default initalizer for the RATELIMIT object.
-----------------------------------------------------------------------------*/                     
#define RATELIMIT_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          3.6, \
						  -3.6,\
						  0,\
						   1000, \
						  -1000,\
              			  (void (*)(Uint32))fnRatelimit_Calc }
              			  
/*------------------------------------------------------------------------------
Prototypes for the functions in PARK.C
------------------------------------------------------------------------------*/
void fnRatelimit_Calc(RATELIMIT *p);



