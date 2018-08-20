/*
 * SVPWM.h
 *
 *  Created on: 2018Äê1ÔÂ18ÈÕ
 *      Author: Administrator
 */

#ifndef ALGORITHM_INCLUDE_SVPWM_H_
#define ALGORITHM_INCLUDE_SVPWM_H_
#include "DSP2833x_Device.h"

typedef struct 	{ float  Ualfa; 			/* Input: reference alfa-axis phase voltage   */
				  float  Ubeta;			/* Input: reference beta-axis phase voltage   */
				  float  V_ba_inv;
				  int  sector;
				  float  Vdc;
				  float  T1;
				  float  T2;
				  float  T0;
				  float  T0_half;
				  float  Ta0;				/* Output: reference phase-a switching function  */
				  float  Tb0;				/* Output: reference phase-b switching function   */
				  float  Tc0;				/* Output: reference phase-c switching function   */
				  float  Ta;				/* Output: reference phase-a switching function  */
				  float  Tb;				/* Output: reference phase-b switching function   */
				  float  Tc;				/* Output: reference phase-c switching function   */
				  void   (*calc)();	    /* Pointer to calculation function */
				} SVPWM;

typedef SVPWM *SVPWM_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SVGENDQ object. section
-----------------------------------------------------------------------------*/
#define SVPWM_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
                       (void (*)(long))SVPWM_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in SVGEN_DQ.C
------------------------------------------------------------------------------*/
void SVPWM_calc(SVPWM_handle);

//extern Svm SVPWM1=Svm_DEFAULTS;

#endif /* ALGORITHM_INCLUDE_SVPWM_H_ */
