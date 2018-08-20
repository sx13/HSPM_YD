
/*
// Version: V1.0
// Date: 	Oct 25, 2012
// Author:	csc @YD
//===========================================================================
//
// 文件名:	DmcLib.h
//
// 用途:	电机控制库对内头文件，包含常数的宏定义等。	
//
//===========================================================================
*/

//===========================================================================
// 定义28335的数据类型
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int                int16;
typedef long               int32;
typedef long long          int64;
typedef unsigned int       Uint16;
typedef unsigned long      Uint32;
typedef unsigned long long Uint64;
typedef float              float32;
typedef long double        float64;
#endif

#define MINIDATA	0.00000000001
#define NMINIDATA	-0.00000000001
#define TRUE		1
#define FALSE		0
#define PI			3.1415926
#define PI2			6.2831853
#define PI2D3       2.0943951
#define N_PI2		-6.2831853
#define ONE			1.0
#define N_ONE		-1.0
#define N_P5		-0.5
#define P5  		0.5
#define SQRT3_D2	0.8660254
#define N_SQRT3_D2	-0.8660254
#define ZERO		0.0
#define ONE_D_SQRT3 0.57735027
#define TWO_D_SQRT3 1.1547344
#define SQRT2       1.414214
#define SQRT_2D3    0.8164966  
#define SQRT3       1.732051
#define THREE_D_TWO 1.5
#define THIRD		0.33333333
#define THIRD2		0.66666667
#define SETERR		0x0001
#define	SETOK		0x0000
//===========================================================================
// NO MORE
//===========================================================================
