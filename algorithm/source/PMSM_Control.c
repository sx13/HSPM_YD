#include "SysCtl_AllHeaders.h"

void PMSM_Control_Init_Ready(PMSM_Control *p)  //只初始化一次
{
	p->Ts = vDSP_GPWM_CARRIER[0]->Reg.CARRIER*0.02*fusToS * vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE;
	float Ls_tmp;
	Ls_tmp = *pCsvParamAsynLs;
	p->Ls = Ls_tmp * 0.001;
	p->Ld = p->Ls;
	p->Lq = p->Ls;
	p->Ls_inv = 1 / p->Ls;
	p->p = SysRatedParameter.fMotorPoleNum;
	p->Ke = *pCsvParamAsynLm;  //flux linkage
	p->R = *pCsvParamAsynRs;
	p->Cur_base = SysBaseValue.fCurrBaseValue;
	p->Vol_base = SysBaseValue.fVoltBaseValue;
//	p->PI_Speed.ui = 0.1;

//	p->Iq_ref = *pCsvParamExcitationCurrent;//i/f控制启动电流标幺值	Added by SX 20180427

}

void PMSM_Control_Init_Run(PMSM_Control *p)  //可以随时更新
{
	p->PI_Speed.kp = *pCsvParamSLVCSpeedKpMAX;//200*p->J/(4*4*0.4646);
	p->PI_Speed.ki = *pCsvParamSpeedLoopKi;//100*p->J/(4*4*0.4646)/10000;
	p->PI_Speed.max = *pCsvParamSpeedLOutMax;
	p->PI_Speed.ts = 10 * p->Ts;

	p->PI_id.kp = *pCsvParamCurrentKp;//2000*0.019;   2.3328
	p->PI_id.ki = *pCsvParamCurrentKi;//2000*0.1121/10000;  99.28
	p->PI_id.ts = p->Ts;

	p->PI_iq.kp = *pCsvParamCurrentKp;//2000*0.022;     2.21202
	p->PI_iq.ki = *pCsvParamCurrentKi;//2000*0.1121/10000;   99.28
	p->PI_iq.ts = p->Ts;

	p->PI_PLL.kp = *pCsvParamSpeedEstKp;
	p->PI_PLL.ki = *pCsvParamSpeedEstKiMIN;
	p->observer_gain = *pCsvParamPhrKp;

	float spd_tmp;
	spd_tmp = *pCsvParamFreSet;
	p->SpeedRef = spd_tmp * PI2;
	p->Iq_ref = *pCsvParamExcitationCurrent;//i/f控制启动电流标幺值

}

#pragma CODE_SECTION(PMSM_SLVC_Control_Calc, "ramfuncs")
void PMSM_SLVC_Control_Calc(PMSM_Control *p)
{

	IPARK VolIPark = IPARK_DEFAULTS;
	CLARKE  CurClarke = CLARKE_DEFAULTS;
	PARK CurPark = PARK_DEFAULTS;
	SVPWM Svpwm = SVPWM_DEFAULTS;


/////////////////////////////////////
	p->Theta = p->Theta_est;
/////////////////////////////////////
	p->cos_theta = cos(p->Theta);
	p->sin_theta = sin(p->Theta);


	CurClarke.as = p->Ia;
	CurClarke.bs = p->Ib;
	CurClarke.cs = p->Ic;
	CurClarke.calc(&CurClarke);
	CurPark.xalpha = CurClarke.xalpha;
	CurPark.xbeta = CurClarke.xbeta;
	p->Ialpha = CurClarke.xalpha;
	p->Ibeta = CurClarke.xbeta;
	CurPark.cos_ang = p->cos_theta;
	CurPark.sin_ang = p->sin_theta;
	CurPark.calc(&CurPark);
	p->Id = CurPark.xd;
	p->Iq = CurPark.xq;

	p->SpeedLoop++;
	if((p->SpeedLoop) > 9)
	{
		p->PI_Speed.ref = p->SpeedRef;
		p->PI_Speed.fb = p->Speed_est;
		p->PI_Speed.calc(&(p->PI_Speed));
		p->SpeedLoop = 0;
	}

	p->Iq_ref = p->PI_Speed.out;
	p->Id_ref = 0;

	p->PI_id.max = 0.57*p->Vdc;
	p->PI_iq.max = p->PI_id.max;

	p->PI_id.ref = p->Id_ref;
	p->PI_id.fb = p->Id;
	p->PI_id.calc(&(p->PI_id));

	p->PI_iq.ref = p->Iq_ref;
	p->PI_iq.fb = p->Iq;
	p->PI_iq.calc(&(p->PI_iq));

	p->Ud = p->PI_id.out - p->Iq * p->Lq * p->we * SysBaseValue.fYBaseValue;;
	p->Uq = p->PI_iq.out + p->Id * p->Ld * p->we * SysBaseValue.fYBaseValue;;
	float u_temp;
	u_temp = p->Ud * p->Ud + p->Uq * p->Uq;
	if(u_temp > (p->PI_id.max * p->PI_id.max))
	{
		p->Ud = p->PI_id.max / sqrt(u_temp) * p->Ud;
		p->Uq = p->PI_iq.max / sqrt(u_temp) * p->Uq;
	}

	VolIPark.xd = p->Ud;
	VolIPark.xq = p->Uq;
	VolIPark.cos_ang = cos(p->Theta + 1.5 * p->we * p->Ts);
	VolIPark.sin_ang = sin(p->Theta + 1.5 * p->we * p->Ts);
	VolIPark.calc(&VolIPark);

	Svpwm.Ualfa = VolIPark.xalpha;
	Svpwm.Ubeta = VolIPark.xbeta;
	Svpwm.Vdc = p->Vdc;
	p->Ualpha = Svpwm.Ualfa;
	p->Ubeta = Svpwm.Ubeta;
	Svpwm.calc(&Svpwm);
	p->Ta = Svpwm.Ta;
	p->Tb = Svpwm.Tb;
	p->Tc = Svpwm.Tc;
}

#pragma CODE_SECTION(PMSM_I_f_Control_Calc, "ramfuncs")
void PMSM_I_f_Control_Calc(PMSM_Control *p)
{
	IPARK VolIPark = IPARK_DEFAULTS;
	CLARKE  CurClarke = CLARKE_DEFAULTS;
	PARK CurPark = PARK_DEFAULTS;
	SVPWM Svpwm = SVPWM_DEFAULTS;

	float fre_acc = 0.0002;
//	float fre_max = 40;

	FreqEn_DSPtoARM = 0xc3;  // added by SX 20180417

/////////////////////////////////////
	if(p->SpeedRef == 0)
	{
//		p->Theta = -PI/2;
//		if(SquareCount <= 2000)
//		{
			p->Iq_ref = 0.25;
//		}
//		else
//		{
//			p->Iq_ref = -0.25;
//		}
//		SquareCount++;
//		if(SquareCount > 4000)
//		{
//			SquareCount = 0;
//		}
	}
	else
	{
	//		revised by SX 20180420

		if(p->fre < p->SpeedRef/PI2)
		{
			p->fre += fre_acc;
		}
		/*else
		{
			p->fre += fre_acc;
		}*/
		p->Theta += p->fre * PI2 * p->Ts;
		if(p->Theta >= PI2)
		{
			p->Theta -= PI2;
		}
	}
	/////////////////////////////////////
	p->cos_theta = cos(p->Theta);
	p->sin_theta = sin(p->Theta);

	CurClarke.as = p->Ia;
	CurClarke.bs = p->Ib;
	CurClarke.cs = p->Ic;
	CurClarke.calc(&CurClarke);

	CurPark.xalpha = CurClarke.xalpha;
	CurPark.xbeta = CurClarke.xbeta;
	p->Ialpha = CurClarke.xalpha;
	p->Ibeta = CurClarke.xbeta;

	CurPark.cos_ang = p->cos_theta;
	CurPark.sin_ang = p->sin_theta;
	CurPark.calc(&CurPark);

	p->Id = CurPark.xd;
	p->Iq = CurPark.xq;

	p->PI_id.max = 0.57*p->Vdc;
	p->PI_iq.max = p->PI_id.max;

	p->Id_ref = 0;
	p->PI_id.ref = p->Id_ref;
	p->PI_id.fb = p->Id;
	p->PI_id.calc(&(p->PI_id));

	//p->Iq_ref = 0.12;
	p->PI_iq.ref = p->Iq_ref;
	p->PI_iq.fb = p->Iq;
	p->PI_iq.calc(&(p->PI_iq));

	p->Ud = p->PI_id.out;
	p->Uq = p->PI_iq.out;
	float u_temp;
	u_temp = p->Ud * p->Ud + p->Uq * p->Uq;
	if(u_temp > (p->PI_id.max * p->PI_id.max))
	{
		p->Ud = p->PI_id.max / sqrt(u_temp) * p->Ud;
		p->Uq = p->PI_id.max / sqrt(u_temp) * p->Uq;
	}

	VolIPark.xd = p->Ud;
	VolIPark.xq = p->Uq;
	VolIPark.cos_ang = p->cos_theta;
	VolIPark.sin_ang = p->sin_theta;
	VolIPark.calc(&VolIPark);

	Svpwm.Ualfa = VolIPark.xalpha;
	Svpwm.Ubeta = VolIPark.xbeta;
	Svpwm.Vdc = p->Vdc;
	p->Ualpha = Svpwm.Ualfa;
	p->Ubeta = Svpwm.Ubeta;
	Svpwm.calc(&Svpwm);
	p->Ta = Svpwm.Ta;
	p->Tb = Svpwm.Tb;
	p->Tc = Svpwm.Tc;
}

#pragma CODE_SECTION(PMSM_Observer, "ramfuncs")
void PMSM_Observer(PMSM_Control *p)
{
//	p->SpeedLoop++;
//	if((p->SpeedLoop) > 9)
//	{
//		p->PI_Speed.ref = p->SpeedRef;
//		p->PI_Speed.fb = p->Speed_est;
//		p->PI_Speed.calc(&(p->PI_Speed));
//		p->SpeedLoop = 0;

//		if(((p->Theta_est - p->Theta) > 0.25)&&((p->Theta_est - p->Theta) < 3.14))
//		{
//			p->Iq_ref -= 0.0000001;
//		}
//		else if(((p->Theta - p->Theta_est) > 0.1)&&((p->Theta - p->Theta_est) < 3.14))
//		{
//			p->Iq_ref += 0.0000001;
//		}

//	}
	float Ialpha,Ibeta,Ualpha,Ubeta;
	Ialpha = p->Ialpha * p->Cur_base;
	Ibeta = p->Ibeta * p->Cur_base;
	Ualpha = p->Ualpha * p->Vol_base;
	Ubeta = p->Ubeta * p->Vol_base;
	p->back_EMF_alpha = p->observer_gain * (Ialpha - p->Ialpha_est);
	p->back_EMF_beta = -p->observer_gain * (Ibeta - p->Ibeta_est);
	p->PI_PLL.ref = p->back_EMF_alpha * cos(p->Theta_PLL);
	p->PI_PLL.fb = p->back_EMF_beta * sin(p->Theta_PLL);
	p->PI_PLL.calc(&p->PI_PLL);
	p->we = p->PI_PLL.out + 25 * PI2;
	p->Theta_PLL += p->we * p->Ts;
	if(p->Theta_PLL < 0)
	{
		p->Theta_PLL += PI2;
	}
	else if(p->Theta_PLL > PI2)
	{
		p->Theta_PLL -= PI2;
	}

	p->Speed_est = p->we;
//	p->Theta_est = p->Theta_PLL + atan(p->we * p->Ls / (p->observer_gain + p->R));
	p->Theta_est = p->Theta_PLL;

	if(p->Theta_est < 0)
	{
		p->Theta_est += PI2;
	}
	else if(p->Theta_est > PI2)
	{
		p->Theta_est -= PI2;
	}
	p->Ialpha_est = p->Ialpha_est * (1 - p->R * p->Ts * p->Ls_inv) + (Ualpha + p->back_EMF_alpha) * p->Ls_inv * p->Ts;
	p->Ibeta_est = p->Ibeta_est * (1 - p->R * p->Ts * p->Ls_inv) + (Ubeta - p->back_EMF_beta) * p->Ls_inv * p->Ts;


}

void PMSM_IF_SLVC_Switch(PMSM_Control *p)
{
	if (p->Iq_ref > iq_load)
	{
		p->Iq_ref -= 0.0000002;
	}

}
/*
 * PMSM_Control.c
 *
 *  Created on: 2018年1月23日
 *      Author: YP/SX
 */




