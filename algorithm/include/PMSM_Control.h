#include <math.h>
//====================================================================================================//
typedef struct
{
	float Ts;

	float Ia;
	float Ib;
	float Ic;
	float Vdc;

	float Ke; //Flux
	float Ls;
	float Ls_inv; //1/Ls
	float Ld; //Ld
	float Lq; //Lq
	float p; //Pole Pairs
	float J; //Inertia
	float R;
	float Vol_base;
	float Cur_base;

	float Ialpha;
	float Ibeta;
	float Id;
	float Iq;
	float SpeedRef;
	float Speed;  //转速 rpm
	float fre;		//电角频率Hz
	int   SpeedLoop;

	float Id_ref;
	float Iq_ref;

	float Ualpha;
	float Ubeta;
	float Theta;
	float cos_theta;
	float sin_theta;
	float Ud;
	float Uq;

	//observer variables
	float back_EMF_alpha;
	float back_EMF_beta;
	float observer_gain;
	float Ialpha_est;
	float Ibeta_est;
	float Speed_est;  //rpm
	float Theta_est;  //rad
	float Theta_PLL;
	float we;		//电角速度 rad/s

	float  Ta;				/* Output: reference phase-a switching function  */
	float  Tb;				/* Output: reference phase-b switching function   */
	float  Tc;				/* Output: reference phase-c switching function   */

	Uint16 Uu;
	Uint16 Uv;
	Uint16 Uw;

	PI_REG PI_Speed;
	PI_REG PI_id;
	PI_REG PI_iq;
	PI_REG PI_PLL;

	void  (*Init_Ready)();
	void  (*Init_Run)();
	void  (*I_f_Calc)();
	void  (*SLVC_Calc)();
	void  (*Observer)();
	void  (*Swit)();

} PMSM_Control;

#define PMSM_Control_DEFAULTS {0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
                          0, \
                          0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
                          0, \
                          0, \
						  0, \
						  0, \
						  0, \
                          0, \
                          0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  0, \
						  PI_REG_DEFAULTS, \
						  PI_REG_DEFAULTS, \
						  PI_REG_DEFAULTS, \
						  PI_REG_DEFAULTS, \
						  (void (*)(long))PMSM_Control_Init_Ready,\
						  (void (*)(long))PMSM_Control_Init_Run,\
						  (void (*)(long))PMSM_I_f_Control_Calc,\
						  (void (*)(long))PMSM_SLVC_Control_Calc,\
						  (void (*)(long))PMSM_Observer,\
						  (void (*)(long))PMSM_IF_SLVC_Switch}


//==================================================================================================//
void PMSM_Control_Init_Ready(PMSM_Control *p);
void PMSM_Control_Init_Run(PMSM_Control *p);
void PMSM_I_f_Control_Calc(PMSM_Control *p);
void PMSM_SLVC_Control_Calc(PMSM_Control *p);
void PMSM_Observer(PMSM_Control *p);
void PMSM_IF_SLVC_Switch(PMSM_Control *p);
extern PMSM_Control PMSM;
extern Uint16 SquareCount;
