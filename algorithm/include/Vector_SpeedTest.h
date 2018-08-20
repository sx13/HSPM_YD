
/* File name:       Vector_SpeedTest.H  */ 


typedef struct {  
                  /*输入变量*/
				  float32  fVola;	 // 输入：A相电压
				  float32  fVolb;	 // 输入：B相电压
				  float32  fCura;    // 输入：A相电流
				  float32  fCurb;    // 输入：B相电流
				  float32  fwr;      // 输入：电机滑差
				  float32  fSetSpd;  // 输入：给定转速

				  /*输入参数*/
				  Uint16   uMethod;  //参数：矢量控制方法标志位
				  Uint16   uParatest;//参数：参数辨识标志位
				  float32  fRs;      //参数：电机定子电阻
				  float32  fRr;      //参数：电机转子电阻
				  float32  fLls;     //参数：电机定子漏感
				  float32  fLlr;     //参数：电机转子漏感
				  float32  fLm;      //参数：电机互感
                  float32  fKp;      //参数：转速识别比例系数
				  float32  fKimin;   //参数：转速识别积分系数最小值
				  float32  fKimid;   //参数：转速识别积分系数中间值
                  float32  fKimax;   //参数：转速识别积分系数最大值
				  float32  fmin;     //参数：转速识别最小值
				  float32  fmax;     //参数：转速识别最大值				  
				  float32  fPwmTime; //参数：pwm中断时间
				  float32  fFrmin;   //参数：转速估计Ki中间值频率
   
                  /*中间计算变量*/
				  float32  fPhrAlpha;  //中间变量：转子Alpha磁链
				  float32  fPhrBeta;   //中间变量：转子Beta磁链
				  float32  fPhsAlpha;  //中间变量：定子Alpha磁链
				  float32  fPhsBeta;   //中间变量：定子Beta磁链
				  float32  fPhsq;      //中间变量：定子q轴磁链
				  float32  fPhsd;      //中间变量：定子d轴磁链
				  float32  fKiTemp;    //中间变量：Ki计算中间值

				  Uint32   uFlyStart;
				  Uint32   uFlyCount;
				  float32  fFrRefstop;


                  /*输出变量*/
				  float32  fPhrq;
				  float32  fPhrd;
				  float32  fSpd;	// 	
				  float32  fAng;
				  float32  fPhr;

		 	 	  void  (*pfnCalc)();	  	// Pointer to calculation function
				  void  (*pfnInit)();
				 } VECTOR_ST;	           

                   
#define VECTOR_ST_DEFAULTS {0,0,0,0,0,0,\
                           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
						   0,0,0,0,0,0,0,\
						   0,0,0.0,\
						   0,0,0,0,0,\
              			  (void (*)(Uint32))fnVector_st_Calc,\
              			  (void (*)(Uint32))fnVector_st_Init}

void fnVector_st_Calc(VECTOR_ST *p);
void fnVector_st_Init(VECTOR_ST *p);
 
