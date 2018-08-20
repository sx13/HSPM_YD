/*
// Version: V1.0 文件创建
// Date: 	DEC 21, 2012
// Author:	csc @YD
//==========================================================================
//
// 文件名:	DMC_CLARKE.h
//
// 用途:  CLARKE变换头文件
//
// 说明：
// sCw.Iuvw=1，输入为uvw三相；Alpha = 1/3*(2*fU - fV - fW), Beta = (fV - fW)/1.732
// sCw.Iuv=1，输入为uv三相；Alpha = fU, Beta = (fU + 2*fV)/1.732
//==========================================================================
*/
//控制字：输入电流方式选择

#pragma CODE_SECTION(fnClarkeCalc, "ramfuncs")

struct CLARKE_CW_BITS {    		// bits  description
    Uint16  Iuvw:1;      		// 0   
	Uint16  Iuv:1;				//
    Uint16  rsvd:14;      		// 14  reserved
};
union CLARKE_CW_REG {
   Uint16                	all;
   struct CLARKE_CW_BITS   	bit;
};
#define CLARKE_UVW    0x0001
#define CLARKE_UV     0x0002

typedef struct {
				  // 输入
				  float32  fU;  		// 输入: U相输入
				  float32  fV;			// 输入: V相输入
				  float32  fW;			// 输入: W相输入
				  union    CLARKE_CW_REG   sCw;

				  // 输出
				  float32  fAlpha;		// 输出：Alpha
				  float32  fBeta;		// 输出：Beta

				 /*函数*/
				 void     (*pfnCalc)();		// CLARKE计算函数指针
				 void     (*pfnReset)();	// CLARKE复位函数指针
				 void     (*pfnInit)();		// CLARKE初始化函数指针

				 } CLARKE;	            

#define CLARKE_DEFAULTS { 0.0,0.0,0.0,\
						  0,\
						  0.0,0.0,\
						  (void (*)(Uint32))fnClarkeCalc,\
						  (void (*)(Uint32))fnClarkeReset,\
						  (void (*)(Uint32))fnClarkeInit }
//===========================================================================
//CLARKE的操作函数申明
void fnClarkeCalc(CLARKE *p);
void fnClarkeReset(CLARKE *p);
void fnClarkeInit(CLARKE *p);


//===========================================================================
// No more.
//===========================================================================
