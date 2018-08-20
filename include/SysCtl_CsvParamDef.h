
#ifndef SYSCTL_CSVPARAMDEF_H
#define SYSCTL_CSVPARAMDEF_H
extern Uint16 HMIBuffer[2000];

//#define pCsvParamHead		    ((float32*)0x119000) // 必须定义为32位数指针，否则偏移量应乘以2。  是否应该 -
#define pCsvParamHead   (float32*)&HMIBuffer[0]
//===== 系统控制字 =====
#define pCsvParamSysCtlWord          ((Uint32*) (pCsvParamHead + 268));  //系统控制字

#define pCsvParamDebugMD             ((float32*) (pCsvParamHead + 58));  //控制电调试

#define pCsvParaSampleOffset       ((float32*) (pCsvParamHead + 463));  //零漂设定值起始地址
 
#define pCsvParamOCPRO              ((float32*) (pCsvParamHead + 140));  //瞬时过流 保护值
#define pCsvParaStartMod            ((float32*) (pCsvParamHead + 289));  //启动方式

//=====载波频率============
#define pCsvCarrierFre				((float32*) (pCsvParamHead + 383))  //开关频率，也称DSP主中断倍数
#define pCsvChopwaveFre				((float32*) (pCsvParamHead + 384))  //斩波频率
#define pCsvChopDutyCycle			((float32*) (pCsvParamHead + 385))  //载波占空比
#define pCsvARMInterMultiple		((float32*) (pCsvParamHead + 386))  //ARM主中断倍数
#define pCsvDspFiberChopEnable		((float32*) (pCsvParamHead + 387))  //光纤斩波使能


//=======VF曲线参数========
#define pCsvParamFreqStart            ((float32*) (pCsvParamHead + 394));  //始动频率
#define pCsvParamVF_VoltMin           ((float32*) (pCsvParamHead + 368));  //最低电压
#define pCsvParamVF_FreqPoint1        ((float32*) (pCsvParamHead + 369));  //频率点1
#define pCsvParamVF_VoltPoint1        ((float32*) (pCsvParamHead + 370));  //电压点1
#define pCsvParamVF_FreqPoint2        ((float32*) (pCsvParamHead + 371));  //频率点2
#define pCsvParamVF_VoltPoint2        ((float32*) (pCsvParamHead + 372));  //电压点2
#define pCsvParamVF_FreqMax           ((float32*) (pCsvParamHead + 373));  //最高频率
#define pCsvParamVF_VoltMax           ((float32*) (pCsvParamHead + 374));  //最高电压

//=====采样设置=======
//#define pCsvParamSamCurrentRatio      ((float32*) (pCsvParamHead + 187));  //电流传感器变比
//#define pCsvParamSamVoltageRatio      ((float32*) (pCsvParamHead + 188));  //电压传感器变比

//===== 额定参数 =====
#define pCsvParamMotorRatedVoltage   ((float32*) (pCsvParamHead + 450));  //电机额定电压                                 
#define pCsvParamMotorRatedCurrent   ((float32*) (pCsvParamHead + 451));  //电机额定电流                                 
#define pCsvParamMotorRatedFre       ((float32*) (pCsvParamHead + 452));  //电机额定频率                                 
#define pCsvParamMotorRatedPower     ((float32*) (pCsvParamHead + 453));  //电机额定功率                                 
#define pCsvParamMotorRateSpeed      ((float32*) (pCsvParamHead + 454));  //电机额定转速                                 
#define pCsvParamMotorPoleNum        ((float32*) (pCsvParamHead + 455));  //电机极对数                                  
#define pCsvParamMotorRatedSlip      ((float32*) (pCsvParamHead + 456));  //电机额定转差率        
#define pCsvParamVFDInputVolatge     ((float32*) (pCsvParamHead + 457));  //变频器额定输入电压                               
#define pCsvParamVFDInputCurrent     ((float32*) (pCsvParamHead + 458));  //变频器额定输入电流                           
#define pCsvParamVFDRatedPower       ((float32*) (pCsvParamHead + 459));  //变频器额定功率                               
#define pCsvParamVFDInputFre         ((float32*) (pCsvParamHead + 460));  //变频器额定输入频率                           
#define pCsvParamVFDOutputVoltage    ((float32*) (pCsvParamHead + 461));  //变频器额定输出电压                           
#define pCsvParamVFDOutputCurrent    ((float32*) (pCsvParamHead + 462));  //变频器额定输出电流 

#define pCsvParaConRunType           ((float32*) (pCsvParamHead + 273));  //变频器控制方式
#define pCsvParaVFDLoadType          ((float32*) (pCsvParamHead + 274));  //负载类型
#define pCsvParaConStrategy          ((float32*) (pCsvParamHead + 275));  //控制策略

#define pCsvParamDACH1 				 ((float32*) (pCsvParamHead + 741));
#define pCsvParamDACH2				 ((float32*) (pCsvParamHead + 746));

#define pCsvParamVol_ManualSet       ((float32*) (pCsvParamHead + 20))  //手动设置逆变侧电压上限值

#define pCsvParamSamDCVoltage        ((float32*) (pCsvParamHead + 473));  //直流电压采样DSP 3V对应最大母线电压多少V
#define pCsvParamSamOutCurrent       ((float32*) (pCsvParamHead + 474));  //交流电流DSP 3V对应电流多少A
#define pCsvParamSamOutVoltage       ((float32*) (pCsvParamHead + 475));  //交流电压DSP 3V对应电压多少V
#define pCsvParamSamNTC1             ((float32*) (pCsvParamHead + 476));  //NTC1 DSP 3V对应热敏电阻阻止多少欧姆
#define pCsvParamSamNTC2             ((float32*) (pCsvParamHead + 477));  //NTC2 DSP 3V对应热敏电阻阻止多少欧姆

#define pCsvParamOCPrtVal  		((float32*) (pCsvParamHead + 760)); //电流瞬时值保护
#define pStateNew				((Uint32*) (pCsvParamHead + 261));

//=========矢量控制算法=======
#define pCsvParamFreSet			((float32*) (pCsvParamHead + 393));//频率给定

#define pCsvParamAsynRs           ((float32*) (pCsvParamHead + 57));//定子电阻
#define pCsvParamAsynRr           ((float32*) (pCsvParamHead + 58));//转子电阻
#define pCsvParamAsynLs           ((float32*) (pCsvParamHead + 59));//定子漏感
#define pCsvParamAsynLr           ((float32*) (pCsvParamHead + 60));//转子漏感
#define pCsvParamAsynLm           ((float32*) (pCsvParamHead + 61));//互感

#define pCsvParamExcitCurrentST   ((float32*) (pCsvParamHead + 33));//励磁电流初始值
#define pCsvParamExcitationCurrent   ((float32*) (pCsvParamHead + 34));//激励电流
#define pCsvParamExcitationTime    ((float32*) (pCsvParamHead + 35));//激励时间


#define pCsvParamPhrKp             ((float32*) (pCsvParamHead + 39));//转子磁链闭环KP
#define pCsvParamPhrKi             ((float32*) (pCsvParamHead + 40));//转子磁链闭环Ki
#define pCsvParamPhrLoopStartFreq  ((float32*) (pCsvParamHead + 54));//转子磁链闭环起始频率

#define pCsvParamCNT_FR_VALUE      ((float32*) (pCsvParamHead + 53));//转矩计算周期
#define pCsvParamSLVCSpeedKpMAX      ((float32*) (pCsvParamHead + 29));//速度环KP最大值
#define pCsvParamSLVCSpeedKpMIN      ((float32*) (pCsvParamHead + 28));//速度环KP最小值
#define pCsvParamSpeedLoopKi       ((float32*) (pCsvParamHead + 30));//速度环Ki
#define pCsvParamSpeedLOutMin       ((float32*) (pCsvParamHead + 31));//速度环输出最小值
#define pCsvParamSpeedLOutMax       ((float32*) (pCsvParamHead + 32));//速度环输出最大值
#define pCsvParamCurrentKp          ((float32*) (pCsvParamHead + 36));//电流环Kp
#define pCsvParamCurrentKi          ((float32*) (pCsvParamHead + 37));//电流环Ki

#define pCsvParamRotorFluxGiven     ((float32*) (pCsvParamHead + 38));//磁链给定值
#define pCsvParamRotorFluxOutMin     ((float32*) (pCsvParamHead + 41));//磁链输出最小值
#define pCsvParamRotorFluxOutMax     ((float32*) (pCsvParamHead + 42));//磁链输出最大值

#define pCsvParamSpeedEstKp     ((float32*) (pCsvParamHead + 43));//估计环KP
#define pCsvParamSpeedEstKiMIN     ((float32*) (pCsvParamHead + 44));//估计环KI最小值
#define pCsvParamSpeedEstKiMID     ((float32*) (pCsvParamHead + 45));//估计环Ki中间值
#define pCsvParamSpeedEstKiMAX     ((float32*) (pCsvParamHead + 46));//估计环Ki最大值

#define pCsvParamSpeedEstFrRefFly  ((float32*) (pCsvParamHead + 47));//飞车启动初始频率
#define pCsvParamSpeedEstKpFly     ((float32*) (pCsvParamHead + 48));//飞车启动估计Kp
#define pCsvParamSpeedEstKiMINFly  ((float32*) (pCsvParamHead + 49));//飞车启动估计ki最小
#define pCsvParamSpeedEstKiMIDFly  ((float32*) (pCsvParamHead + 50));//飞车启动估计ki中间
#define pCsvParamSpeedEstKiMAXFly  ((float32*) (pCsvParamHead + 51));//飞车启动估计KI最大
#endif

//============================                                                                                                                                                                                                                                                                                                                       
// No more.
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
