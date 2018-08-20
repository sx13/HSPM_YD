
/*File name:       SLIP.H  */                   
                    





typedef struct { 
                  /*输入变量*/
                  float32  fIsmSet;  	// 输入：励磁电流给定  
				  float32  fIstSet;		// 输入：转矩电流给定

				  /*输入参数*/
				  float32  fSlipRate;   // 参数：额定滑差
				  float32  fSlipRr;     // 参数：转子电阻
				  float32  fSlipLlr;    // 参数：转子漏感
				  float32  fSlipLm;     // 参数：互感
                  
				  /*中间变量*/
				  float32  fTrdSlip;

				  /*输出变量*/
				  float32  fSlipSet;	// 输出：根据给定电流计算的转差 
                  /*函数指针*/
		 	 	  void  (*pfnSetcalc)();	// 指向计算函数指针
				  void  (*pfnSetinti)();	// 指向计算函数指针

				}SLIP;	            

                     
#define SLIP_DEFAULTS { 0,0,\
                        0,0,0,0,\
						0, \
                        0, \
              			(void (*)(Uint32))fnSlipset_Calc,\
              			(void (*)(Uint32))fnSlipset_Inti}


void fnSlipset_Calc(SLIP *p);
void fnSlipset_Inti(SLIP *p);



