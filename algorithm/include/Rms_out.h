
/* FILE:	rms_out.h */


typedef struct{ 
               /* 输入变量 */
				float32	fSampl_A;
				float32	fSampl_B;
				float32	fSampl_C;
				float32	fSamp_count;
				float32	fSet_Spd;

				int16   iN;
				int16   iN1;
				int16   iN2;
				float32 fSquare_A;
				float32 fSquare_B;
				float32 fSquare_C;
				float32 fSquare_A_former;
				float32 fSquare_B_former;
				float32 fSquare_C_former;


				/* 输出变量 */
				float32	fResult_A;
				float32	fResult_B;
				float32	fResult_C;

				  void(*pfnCalc)();	// Pointer to calculation function
				}RMS_OUT;
																																																																																																																																																																																																								
/*-----------------------------------------------------------------------------
Default initalizer for the RMS object.
-----------------------------------------------------------------------------*/                     
#define RMS_OUT_DEFAULTS { 0,0,0,2000,0,\
                           0,0,0,0,0,0,0,0,0,\
                           0,0,0, \
                       (void (*)(Uint32))fnRms_out_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in RMS.C
------------------------------------------------------------------------------*/
void fnRms_out_calc(RMS_OUT *p);


//===========================================================================
// No more.
//===========================================================================

