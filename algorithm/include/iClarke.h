/*
File name:       CLARKE.H
                    
#pragma CODE_SECTION(fnIclarke_Calc, "ramfuncs")

typedef struct { 
                  输入变量
                  float32  fAs;  	// 输出：三相定子坐标系A相  
				  float32  fBs;		// 输出：三相定子坐标系B相
				  float32  fCs;		// 输出：三相定子坐标系C相  
				  输出变量
				  float32  fAlpha;	// 输入：两相静止坐标系A相 
				  float32  fBeta;	// 输入：两相静止坐标系B相 
                  函数指针
		 	 	  void  (*pfnIcalc)();	// 指向计算函数指针
				}ICLARKE;	            

                     
#define ICLARKE_DEFAULTS { 0, \
                          0, \
						  0,\
                          0, \
                          0, \
              			  (void (*)(Uint32))fnIclarke_Calc }


void fnIclarke_Calc(ICLARKE *p);*/




