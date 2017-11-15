#include "main.h"
#include "math.h"

//----------------------------0电机控制函数-----------------
void StepMotorInit_0(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	Usart1Init();																				//开启传感器
	TIM2ConfigurePWM();
}

void StepMotorEnable_0(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	PBout(8)=Judge;
}

void StepMotorDirection_0(MotorRotationEnum Rotation)
{
	assert_param(IS_MOTOR_ROTATION(Rotation));
	PBout(9) = Rotation;
}

void StepMotorPWMEnable_0(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	if(Judge)
		TIM_SetCompare3(TIM2,42);	//修改比较值，修改占空比
	else
		TIM_SetCompare3(TIM2,0xffff);	//修改比较值，修改占空比
}

void StepMotorFrequencyConversion_0(int Frequency)
{
	int Prescaler;
		
	assert_param(IS_MOTOR_FREQUENCY(Frequency));
	
	Prescaler = 1000000/fabs(Frequency);
	
	if(Prescaler>65536)			//安全隐患
	{
		Prescaler = 0xffff;
	}
	StepMotorPWMEnable_0(ENABLE);

	if(Frequency>0)
	{
		StepMotorDirection_0(CLOCKWISE);
	}else
	{
		StepMotorDirection_0(ANTICLOCKWISE);
	}
	TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Immediate);
	TIM_Cmd(TIM2, ENABLE);  //使能TIM14
}
//*******************************************************************

//----------------------------1电机控制函数-----------------
void StepMotorInit_1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	Usart2Init();																				//开启传感器
	TIM3ConfigurePWM();
}

void StepMotorEnable_1(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	PAout(4)=Judge;
}

void StepMotorDirection_1(MotorRotationEnum Rotation)
{
	assert_param(IS_MOTOR_ROTATION(Rotation));
	PAout(5) = Rotation;
}
void StepMotorPWMEnable_1(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	if(Judge)
		TIM_SetCompare1(TIM3,42);	//修改比较值，修改占空比
	else
		TIM_SetCompare1(TIM3,0xffff);	//修改比较值，修改占空比
}

void StepMotorFrequencyConversion_1(int Frequency)
{
	u32 Prescaler;
		
	assert_param(IS_MOTOR_FREQUENCY(Frequency));
	
	Prescaler = 1000000/fabs(Frequency);
	
	if(Prescaler>65536)			//安全隐患
	{
		Prescaler = 0xffff;
	}
	StepMotorPWMEnable_1(ENABLE);
	if(Frequency>0)
	{
		StepMotorDirection_1(CLOCKWISE);
	}else
	{
		StepMotorDirection_1(ANTICLOCKWISE);
	}
	TIM_PrescalerConfig(TIM3,Prescaler,TIM_PSCReloadMode_Immediate);
	TIM_Cmd(TIM3, ENABLE);  //使能TIM14
}
//*******************************************************************

//----------------------------2电机控制函数-----------------
void StepMotorInit_2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTF时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_13;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	Usart3Init();																				//开启传感器
	TIM4ConfigurePWM();
}

void StepMotorEnable_2(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	PDout(11)=Judge;
}

void StepMotorDirection_2(MotorRotationEnum Rotation)
{
	assert_param(IS_MOTOR_ROTATION(Rotation));
	PDout(13) = Rotation;
}
void StepMotorPWMEnable_2(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	if(Judge)
		TIM_SetCompare1(TIM4,42);	//修改比较值，修改占空比
	else
		TIM_SetCompare1(TIM4,0xffff);	//修改比较值，修改占空比
}
void StepMotorFrequencyConversion_2(int Frequency)
{
	u32 Prescaler;
		
	assert_param(IS_MOTOR_FREQUENCY(Frequency));
	
	Prescaler = 1000000/fabs(Frequency);
	
	if(Prescaler>65536)			//安全隐患
	{
		Prescaler = 0xffff;
	}
	StepMotorPWMEnable_2(ENABLE);
	if(Frequency>0)
	{
		StepMotorDirection_2(CLOCKWISE);
	}else
	{
		StepMotorDirection_2(ANTICLOCKWISE);
	}
	TIM_PrescalerConfig(TIM4,Prescaler,TIM_PSCReloadMode_Immediate);
	TIM_Cmd(TIM4, ENABLE);  //使能TIM14

}
//*******************************************************************

//----------------------------2电机控制函数-----------------
void StepMotorInit_3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	Uart4Init();																				//开启传感器
	TIM5ConfigurePWM();
}

void StepMotorEnable_3(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	PBout(12)=Judge;
}

void StepMotorDirection_3(MotorRotationEnum Rotation)
{
	assert_param(IS_MOTOR_ROTATION(Rotation));
	PBout(13) = Rotation;
}
void StepMotorPWMEnable_3(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	if(Judge)
		TIM_SetCompare3(TIM5,42);	//修改比较值，修改占空比
	else
		TIM_SetCompare3(TIM5,0xffff);	//修改比较值，修改占空比
}
void StepMotorFrequencyConversion_3(int Frequency)
{
	u32 Prescaler;
		
	assert_param(IS_MOTOR_FREQUENCY(Frequency));
	
	Prescaler = 1000000/fabs(Frequency);
	
	if(Prescaler>65536)			//安全隐患
	{
		Prescaler = 0xffff;
	}
	StepMotorPWMEnable_3(ENABLE);
	if(Frequency>0)
	{
		StepMotorDirection_3(CLOCKWISE);
	}else
	{
		StepMotorDirection_3(ANTICLOCKWISE);
	}
	TIM_PrescalerConfig(TIM5,Prescaler,TIM_PSCReloadMode_Immediate);
	TIM_Cmd(TIM5, ENABLE);  //使能TIM14
}
//*******************************************************************


void MotorDataInit()
{
	u8 i;
	
	MotorControlData[0].StepMotorInit = &StepMotorInit_0;
	MotorControlData[0].StepMotorEnable = &StepMotorEnable_0;
	MotorControlData[0].StepMotorDirection = &StepMotorDirection_0;
	MotorControlData[0].StepMotorPWMEnable = &StepMotorPWMEnable_0;
	MotorControlData[0].StepMotorFrequencyConversion = &StepMotorFrequencyConversion_0;
	MotorControlData[0].SetLocation =0;
	
	MotorControlData[1].StepMotorInit = &StepMotorInit_1;
	MotorControlData[1].StepMotorEnable = &StepMotorEnable_1;
	MotorControlData[1].StepMotorDirection = &StepMotorDirection_1;
	MotorControlData[1].StepMotorPWMEnable = &StepMotorPWMEnable_1;
	MotorControlData[1].StepMotorFrequencyConversion = &StepMotorFrequencyConversion_1;
	MotorControlData[1].SetLocation =0;
	
	MotorControlData[2].StepMotorInit = &StepMotorInit_2;
	MotorControlData[2].StepMotorEnable = &StepMotorEnable_2;
	MotorControlData[2].StepMotorDirection = &StepMotorDirection_2;
	MotorControlData[2].StepMotorPWMEnable = &StepMotorPWMEnable_2;
	MotorControlData[2].StepMotorFrequencyConversion = &StepMotorFrequencyConversion_2;
	MotorControlData[2].SetLocation =0;
	
	MotorControlData[3].StepMotorInit = &StepMotorInit_3;
	MotorControlData[3].StepMotorEnable = &StepMotorEnable_3;
	MotorControlData[3].StepMotorDirection = &StepMotorDirection_3;
	MotorControlData[3].StepMotorPWMEnable = &StepMotorPWMEnable_3;
	MotorControlData[3].StepMotorFrequencyConversion = &StepMotorFrequencyConversion_3;
	MotorControlData[3].SetLocation =0;
	
	for(i=0;i<TESTMOTORNUMBER;i++)
	{
		MotorControlData[i].LocationPID.OutMax 	= 1;
		MotorControlData[i].LocationPID.OutMin	=	-1;
		MotorControlData[i].LocationPID.calc=&PidCalc;
		MotorControlData[i].LocationPID.clear=&PidClear;
		MotorControlData[i].LocationPID.clear(&MotorControlData[i].LocationPID);
		//------------------PID赋值-------------------------
		MotorControlData[i].LocationPID.Kp = STEPMOTOR_KP;
		MotorControlData[i].LocationPID.Ki = STEPMOTOR_KI;
		MotorControlData[i].LocationPID.Kd = STEPMOTOR_KD;
		MotorControlData[i].LocationPID.Kc = STEPMOTOR_KC;
		
		MotorControlData[i].StepMotorInit();
		MotorControlData[i].StepMotorEnable(ENABLE);
		MotorControlData[i].FlagReceiveAngle=0;
	}
}


void MotorControlLogic(void)
{
	u8 i;
	
	MotorControlData[0].LocationPID.Fdb = MotorControlData[0].AngleDataProcessed[0]/180.0f ;		//归一化
	MotorControlData[1].LocationPID.Fdb = MotorControlData[1].AngleDataProcessed[1]/180.0f ;		//归一化
	MotorControlData[2].LocationPID.Fdb = MotorControlData[2].AngleDataProcessed[0]/180.0f ;		//归一化
	MotorControlData[3].LocationPID.Fdb = MotorControlData[3].AngleDataProcessed[1]/180.0f ;		//归一化
	for(i=0;i<TESTMOTORNUMBER;i++)
	{
		MotorControlData[i].LocationPID.Ref = MotorControlData[0].SetLocation/180.0f;			//参考量
		
		MotorControlData[i].LocationPID.calc(&MotorControlData[i].LocationPID);
		if(fabs(MotorControlData[i].LocationPID.Out)>DEADZONE_CONVERT)
			MotorControlData[i].StepMotorFrequencyConversion(MotorControlData[i].LocationPID.Out*30000);
		else
			MotorControlData[i].StepMotorPWMEnable(DISABLE);
	}
	
}
