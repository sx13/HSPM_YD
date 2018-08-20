#include "common_struct.h"

//====================================================================================//
#pragma CODE_SECTION(park_calc, "ramfuncs")
void park_calc(PARK *v)
{	
     v->xd = v->xalpha*v->cos_ang + v->xbeta*v->sin_ang;
     v->xq =v->xbeta*v->cos_ang - v->xalpha*v->sin_ang;
}

#pragma CODE_SECTION(ipark_calc, "ramfuncs")
void ipark_calc(IPARK *v)
{	
     v->xalpha = v->xd*v->cos_ang - v->xq*v->sin_ang;
     v->xbeta = v->xq*v->cos_ang + v->xd*v->sin_ang;  
}

#pragma CODE_SECTION(clarke_calc, "ramfuncs")
void clarke_calc(CLARKE *v)
{	
//    v->xalpha = v->as;
//	v->xbeta = (v->bs - v->cs)*0.57735; //
		v->xalpha = (v->as-0.5*v->bs-0.5*v->cs)*0.6667;
		v->xbeta = (v->bs - v->cs)*0.5773; //
}

#pragma CODE_SECTION(iclarke_calc, "ramfuncs")
void iclarke_calc(ICLARKE *v)
{	
//    v->as = v->xalpha*0.81649658;
//	v->bs = -0.40824829*v->xalpha + 0.70710678*v->xbeta;
//	v->as = v->xalpha;
//	v->bs = -0.5*v->xalpha + 0.866*v->xbeta;
//    v->cs = -(v->as + v->bs);
	v->as = v->xalpha;
	v->bs = -0.5*v->xalpha + 0.866*v->xbeta;
    v->cs = -0.5*v->xalpha - 0.866*v->xbeta;
}

#pragma CODE_SECTION(PI_calc, "ramfuncs")
void PI_calc(PI_REG *r)
{
	r->err = r->ref - r->fb;
/*	if (r->max > 0)
	{
		if (r->err > r->max)
		{
			r->err = r->max;
		}
		else if (r->err < -r->max)
		{
			r->err = -r->max;
		}
	}*/

	r->ui += r->ki * r->err;
	if (r->max > 0)
	{
		if (r->ui > r->max)
		{
			r->ui = r->max;
		}
		else if (r->ui < -r->max)
		{
			r->ui = -r->max;
		}
	}

	r->up = r->kp * r->err;
	r->out = r->up + r->ui;

	if (r->max > 0)
	{
		if (r->out > r->max)
		{
			r->out = r->max;
		}
		else if (r->out < -r->max)
		{
			r->out = -r->max;
		}
	}
}

#pragma CODE_SECTION(lpf_calc, "ramfuncs")
void lpf_calc(LPF *v)
{	// y += tc*wc*(x-y_1)
	v->y += v->Tc * v->wc* (v->x - v->y_old);
	v->y_old = v->y;

}

#pragma CODE_SECTION(lpfi_calc, "ramfuncs")
void lpfi_calc(LPFI *v)
{
	v->y += v->Tc * (v->x - v->wc * v->y_old);

	v->y_old = v->y;
}

