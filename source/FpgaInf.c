#include "DSP2833x_Device.h"     // Headerfile Include File
#include "SysCtl_AllHeaders.h"

TypeChoppedWave SysChoppedWave;

float32 fDetatheta;

DSP_GPWMx_CARRIER *vDSP_GPWM_CARRIER[FPGA_PWM_MODULE_COUNT] = {
	(DSP_GPWMx_CARRIER *)DEP_DSP_GPWMx_CARRIER(0),
	(DSP_GPWMx_CARRIER *)DEP_DSP_GPWMx_CARRIER(1),
	(DSP_GPWMx_CARRIER *)DEP_DSP_GPWMx_CARRIER(2),
	(DSP_GPWMx_CARRIER *)DEP_DSP_GPWMx_CARRIER(3),
	(DSP_GPWMx_CARRIER *)DEP_DSP_GPWMx_CARRIER(4),
	(DSP_GPWMx_CARRIER *)DEP_DSP_GPWMx_CARRIER(5),
	(DSP_GPWMx_CARRIER *)DEP_DSP_GPWMx_CARRIER(6)
};

DSP_GPWMx_COMP	 *vDSP_GPWM_COMP[FPGA_PWM_MODULE_COUNT] = {
	(DSP_GPWMx_COMP *)DEP_DSP_GPWMx_COMP(0),
	(DSP_GPWMx_COMP *)DEP_DSP_GPWMx_COMP(1),
	(DSP_GPWMx_COMP *)DEP_DSP_GPWMx_COMP(2),
	(DSP_GPWMx_COMP *)DEP_DSP_GPWMx_COMP(3),
	(DSP_GPWMx_COMP *)DEP_DSP_GPWMx_COMP(4),
	(DSP_GPWMx_COMP *)DEP_DSP_GPWMx_COMP(5),
	(DSP_GPWMx_COMP *)DEP_DSP_GPWMx_COMP(6)
};

DSP_INT_MULTIPLE *vDSP_INT_MULTIPLE = (DSP_INT_MULTIPLE *)&(DEP_DSP_INT_MULTIPLE);

DSP_FIBER_CHOP *vDSP_FIBER_CHOP = (DSP_FIBER_CHOP *)&(DEP_DSP_FIBER_CHOP);


DSP_GPWM_INT *vDSP_GPWM_INT = (DSP_GPWM_INT *)&(DEP_DSP_GPWM_INT);
DSP_GPWM_ENABLE *vDSP_GPWM_ENABLE = (DSP_GPWM_ENABLE *)&(DEP_DSP_GPWM_ENABLE);
ARM_GPWM_IN_SET *vARM_GPWM_IN_SET = (ARM_GPWM_IN_SET *)&(DEP_ARM_GPWM_IN_SET);
ARM_GPWM_INT_SET *vARM_GPWM_INT_SET = (ARM_GPWM_INT_SET *)&(DEP_ARM_GPWM_INT_SET);
FPGA_GPWM_ENABLE *vFPGA_GPWM_ENABLE = (FPGA_GPWM_ENABLE *)&(DEP_FPGA_GPWM_ENABLE);
ARM_GPWM_ENABLE *vARM_GPWM_ENABLE = (ARM_GPWM_ENABLE *)&(DEP_ARM_GPWM_ENABLE);

/***********************************************************
//函数名称：InvModuWave
//函数功能：调制波传递接口函数
//函数参数： PhaseA A相调制波
 *        PhaseB B相调制波
 *        PhaseB B相调制波
************************************************************/
void InvModuWave(Uint16 PhaseA,Uint16 PhaseB,Uint16 PhaseC)
{	

	vDSP_GPWM_COMP[0]->all = PhaseA;

	vDSP_GPWM_COMP[2]->all = PhaseB;

	vDSP_GPWM_COMP[4]->all = PhaseC;
}

/***********************************************************
//函数名称：ChopWave
//函数功能：斩波函数
//函数参数：
 *
 *
************************************************************/

void ChopWave ( TypeChoppedWave  *p)
{
    Uint16 uChopwaveCarrier;
/*****************************界面可配置斩波频率*******************************/
    p->fchopdataDutyCycle = *pCsvChopDutyCycle;
    p->fchopwavedata = *pCsvChopwaveFre;

	if ((p->fchopwavedata > 0)&&(p->fchopwavedata <= 2))
	{
		uChopwaveCarrier = (Uint16)(5000 / p->fchopwavedata);
		vDSP_GPWM_CARRIER[6]->Reg.CARRIER = uChopwaveCarrier;
		SysVoltBase.uChopCount = uChopwaveCarrier;
	}


  /***************************获得比较值***********************************/

	vDSP_GPWM_COMP[6]->all = p->fchopdataDutyCycle * uChopwaveCarrier;

}
/**************************************************************/


//===========================================================================
// No more.
//===========================================================================
