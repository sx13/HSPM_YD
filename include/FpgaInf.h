
#ifndef FPGAINF_H
#define FPGAINF_H

typedef union{
  	Uint16 all;
	struct{
            Uint16 CARRIER;
	}Reg;
}DSP_GPWMx_CARRIER;

typedef union{
	Uint16 all;
	struct{
		Uint16 ARM_ENABLE : 1;
		Uint16 RES : 15;
	}Reg;
}ARM_GPWM_ENABLE;

typedef union{
	Uint16 all;
	struct{
		Uint16 FPGA_ENABLE : 1;
		Uint16 RES : 15;
	}Reg;
}FPGA_GPWM_ENABLE;

typedef union{
  	Uint16 all;
	struct{
            Uint16 COMPARE;
	}Reg;
}DSP_GPWMx_COMP;

typedef union{
  	Uint16 all;
	struct{
  		 	 Uint16 INT_N : 1;
  		 	 Uint16 INT_ENABLE : 1;
			 Uint16 RES : 14;
	}Reg;
}DSP_GPWM_INT;

typedef union{
  	Uint16 all;
	struct{
  		 	 Uint16 DSP_ENABLE : 1;
  		 	 Uint16 FIBER_CHOP_ENABLE : 1;
			 Uint16 RES : 14;
	}Reg;
}DSP_GPWM_ENABLE;

typedef union{
  	Uint16 all;
	struct{
		 	 Uint16 DSP_EV : 1;
		 	 Uint16 RES : 15;
	}Reg;
}ARM_GPWM_IN_SET;

typedef union{
  	Uint16 all;
	struct{
  		 	 Uint16 INT_ENABLE : 1;
			 Uint16 RES : 15;
	}Reg;
}ARM_GPWM_INT_SET;


typedef union{
  	Uint16 all;
	struct{
  		 	 Uint16 DSP_MULTIPLE : 3;
			 Uint16 RES : 13;
	}Reg;
}DSP_INT_MULTIPLE;

typedef union{
  	Uint16 all;
	struct{
  		 	 Uint16 DSP_FIBER_CHOP_ENABLE : 1;
			 Uint16 RES : 15;
	}Reg;
}DSP_FIBER_CHOP;





//================FPGA地址宏定义=========================================
//========通讯===========================================
#define DSP_APDE_DATA 	 		(Uint16*) 0x280000 	//通讯数据 0-2007
#define DSP_APDE_HANDSHAKE_DSP  *((Uint16*)0x2803FE)	//握手字1
#define DSP_APDE_HANDSHAKE_ARM  *((Uint16*)0x2803FF)	//握手字2
//=======================================================
#define arm_to_dsp_fault     	*((Uint16*)0x280F02)  //特殊功能区
#define dsp_to_arm_fault     	*((Uint16*)0x280F03)  //特殊功能区
#define dsp_to_arm_state	 	*((Uint16*)0x200070)  //特殊功能区

//==========通用PWM======================================
//全局寄存器
#define DEP_DSP_GPWM_INT				*((Uint16*)0x2806E0)     //写中断寄存器,在EV模块使能后给ARM提供中断
#define DEP_ARM_GPWM_ENABLE				*((Uint16*)0x2806E1)
#define DEP_DSP_GPWM_ENABLE				*((Uint16*)0x2806E2)		//ARM侧不使用
#define DEP_FPGA_GPWM_ENABLE			*((Uint16*)0x2806E3)
#define DEP_ARM_GPWM_IN_SET 			*((Uint16*)0x2806E4)		//GPWM生成选项0：比较值 1：EV模块    //这个需要全局
#define DEP_ARM_GPWM_INT_SET  			*((Uint16*)0x2806E5)		//中断产生方式

#define DEP_DSP_INT_MULTIPLE  			*((Uint16*)0x2806E6)		//DSP的主中断倍数
#define DEP_DSP_FIBER_CHOP  			*((Uint16*)0x2806E7)		//光纤斩波使能

#define FPGA_PWM_MODULE_COUNT	7
#define PWMx_REG_HMI_COUNT  	6
//x:0~6 模块配置寄存器
#define DE_DSP_GPWMx_GPIO(x)			*((Uint16*)0x280601 + x * 0x20)	//输出DSP的GPIO值
#define DEP_DSP_GPWMx_CARRIER(x)		((Uint16*)0x280605 + x * 0x20)
#define DEP_DSP_GPWMx_COMP(x)			((Uint16*)0x28060B + x * 0x20)	//比较值

extern DSP_GPWMx_CARRIER *vDSP_GPWM_CARRIER[FPGA_PWM_MODULE_COUNT];
extern DSP_GPWMx_COMP	 *vDSP_GPWM_COMP[FPGA_PWM_MODULE_COUNT];

extern DSP_GPWM_INT *vDSP_GPWM_INT;
extern ARM_GPWM_ENABLE *vARM_GPWM_ENABLE;
extern DSP_GPWM_ENABLE *vDSP_GPWM_ENABLE;
extern FPGA_GPWM_ENABLE *vFPGA_GPWM_ENABLE;
extern ARM_GPWM_IN_SET *vARM_GPWM_IN_SET;
extern ARM_GPWM_INT_SET *vARM_GPWM_INT_SET;
extern DSP_INT_MULTIPLE *vDSP_INT_MULTIPLE;
extern DSP_FIBER_CHOP *vDSP_FIBER_CHOP;

extern void InvModuWave(Uint16 PhaseA,Uint16 PhaseB,Uint16 PhaseC);

//extern void FPGA_SetCarrier(Uint16 uAddr,Uint16 uLen);

extern float32 fDetatheta;

//extern Uint16 C_Max[6];

//#define HMI_GIVEFRE 	*((float*)&HMIBuffer[1000])
//#define HMI_INVGIVEUA   *((float*)&HMIBuffer[1002])
//#define HMI_CARRIER1	*((Uint32*)&HMIBuffer[1256])
//#define HMI_CARRIER2	*((Uint32*)&HMIBuffer[1268])
//#define HMI_CARRIER3	*((Uint32*)&HMIBuffer[1280])
//#define HMI_CARRIER4	*((Uint32*)&HMIBuffer[1292])
//#define HMI_CARRIER5	*((Uint32*)&HMIBuffer[1304])
//#define HMI_CARRIER6	*((Uint32*)&HMIBuffer[1316])
//#define HMI_MODTYPE		*((Uint32*)&HMIBuffer[1202])

typedef struct{
	float32    fchopwavedata;
	float32    fchopdataDutyCycle;
	//float32    fchopEnable;
}TypeChoppedWave;

extern TypeChoppedWave SysChoppedWave;
extern void ChopWave(TypeChoppedWave  *p);

#endif




