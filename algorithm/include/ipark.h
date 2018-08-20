/* =================================================================================
File name:       IPARK.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the IPARK.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                
------------------------------------------------------------------------------*/
#pragma CODE_SECTION(fnIpark_calc, "ramfuncs")
typedef struct {  float32  fAlpha;  	// Output: stationary d-axis stator variable 
				  float32  fBeta;	// Output: stationary q-axis stator variable 
				  float32  fAngle;	// Input: rotating angle (rad) 
				  float32  fDs;		// Input: rotating d-axis stator variable 
				  float32  fQs;		// Input: rotating q-axis stator variable 
		 	 	  void  (*pfnIpcalc)();	// Pointer to calculation function 
				 } IPARK;	            

typedef IPARK *IPARK_handle;

/*-----------------------------------------------------------------------------
Default initalizer for the IPARK object.
-----------------------------------------------------------------------------*/                     
#define IPARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  (void (*)(Uint32))fnIpark_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in IPARK.C
------------------------------------------------------------------------------*/
void fnIpark_calc(IPARK_handle);

