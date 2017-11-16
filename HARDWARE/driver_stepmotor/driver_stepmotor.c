#include "main.h"
#include "math.h"

//----------------------------0������ƺ���-----------------
void StepMotorInit_0(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	Usart1Init();																				//����������
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
		TIM_SetCompare3(TIM2,42);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	else
		TIM_SetCompare3(TIM2,0xffff);	//�޸ıȽ�ֵ���޸�ռ�ձ�
}

void StepMotorFrequencyConversion_0(int Frequency)
{
	int Prescaler;
		
	assert_param(IS_MOTOR_FREQUENCY(Frequency));
	
	Prescaler = 1000000/fabs(Frequency);
	
	if(Prescaler>65536)			//��ȫ����
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
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM14
}
//*******************************************************************

//----------------------------1������ƺ���-----------------
void StepMotorInit_1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	Usart2Init();																				//����������
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
		TIM_SetCompare1(TIM3,42);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	else
		TIM_SetCompare1(TIM3,0xffff);	//�޸ıȽ�ֵ���޸�ռ�ձ�
}

void StepMotorFrequencyConversion_1(int Frequency)
{
	u32 Prescaler;
		
	assert_param(IS_MOTOR_FREQUENCY(Frequency));
	
	Prescaler = 1000000/fabs(Frequency);
	
	if(Prescaler>65536)			//��ȫ����
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
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM14
}
//*******************************************************************

//----------------------------2������ƺ���-----------------
void StepMotorInit_2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_13;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	Usart3Init();																				//����������
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
	PDout(13) = !Rotation;
}
void StepMotorPWMEnable_2(u8 Judge)
{
	assert_param(IS_FUNCTIONAL_STATE(Judge));
	if(Judge)
		TIM_SetCompare1(TIM4,42);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	else
		TIM_SetCompare1(TIM4,0xffff);	//�޸ıȽ�ֵ���޸�ռ�ձ�
}
void StepMotorFrequencyConversion_2(int Frequency)
{
	u32 Prescaler;
		
	assert_param(IS_MOTOR_FREQUENCY(Frequency));
	
	Prescaler = 1000000/fabs(Frequency);
	
	if(Prescaler>65536)			//��ȫ����
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
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM14

}
//*******************************************************************

//----------------------------2������ƺ���-----------------
void StepMotorInit_3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	Uart4Init();																				//����������
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
		TIM_SetCompare3(TIM5,42);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	else
		TIM_SetCompare3(TIM5,0xffff);	//�޸ıȽ�ֵ���޸�ռ�ձ�
}
void StepMotorFrequencyConversion_3(int Frequency)
{
	u32 Prescaler;
		
	assert_param(IS_MOTOR_FREQUENCY(Frequency));
	
	Prescaler = 1000000/fabs(Frequency);
	
	if(Prescaler>65536)			//��ȫ����
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
	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM14
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
	MotorControlData[0].SetLocation =STEPMOTOR_0_INIT_ANGLE;
	MotorControlData[0].LocationPID.Kp = STEPMOTOR_0_KP;
	MotorControlData[0].LocationPID.Ki = STEPMOTOR_0_KI;
	MotorControlData[0].LocationPID.Kd = STEPMOTOR_0_KD;
	MotorControlData[0].LocationPID.Kc = STEPMOTOR_0_KC;
	
	MotorControlData[1].StepMotorInit = &StepMotorInit_1;
	MotorControlData[1].StepMotorEnable = &StepMotorEnable_1;
	MotorControlData[1].StepMotorDirection = &StepMotorDirection_1;
	MotorControlData[1].StepMotorPWMEnable = &StepMotorPWMEnable_1;
	MotorControlData[1].StepMotorFrequencyConversion = &StepMotorFrequencyConversion_1;
	MotorControlData[1].SetLocation =STEPMOTOR_1_INIT_ANGLE;
	MotorControlData[1].LocationPID.Kp = STEPMOTOR_1_KP;
	MotorControlData[1].LocationPID.Ki = STEPMOTOR_1_KI;
	MotorControlData[1].LocationPID.Kd = STEPMOTOR_1_KD;
	MotorControlData[1].LocationPID.Kc = STEPMOTOR_1_KC;
	
	MotorControlData[2].StepMotorInit = &StepMotorInit_2;
	MotorControlData[2].StepMotorEnable = &StepMotorEnable_2;
	MotorControlData[2].StepMotorDirection = &StepMotorDirection_2;
	MotorControlData[2].StepMotorPWMEnable = &StepMotorPWMEnable_2;
	MotorControlData[2].StepMotorFrequencyConversion = &StepMotorFrequencyConversion_2;
	MotorControlData[2].SetLocation =STEPMOTOR_2_INIT_ANGLE;
	MotorControlData[2].LocationPID.Kp = STEPMOTOR_2_KP;
	MotorControlData[2].LocationPID.Ki = STEPMOTOR_2_KI;
	MotorControlData[2].LocationPID.Kd = STEPMOTOR_2_KD;
	MotorControlData[2].LocationPID.Kc = STEPMOTOR_2_KC;
	
	MotorControlData[3].StepMotorInit = &StepMotorInit_3;
	MotorControlData[3].StepMotorEnable = &StepMotorEnable_3;
	MotorControlData[3].StepMotorDirection = &StepMotorDirection_3;
	MotorControlData[3].StepMotorPWMEnable = &StepMotorPWMEnable_3;
	MotorControlData[3].StepMotorFrequencyConversion = &StepMotorFrequencyConversion_3;
	MotorControlData[3].SetLocation =STEPMOTOR_3_INIT_ANGLE;
	MotorControlData[3].LocationPID.Kp = STEPMOTOR_3_KP;
	MotorControlData[3].LocationPID.Ki = STEPMOTOR_3_KI;
	MotorControlData[3].LocationPID.Kd = STEPMOTOR_3_KD;
	MotorControlData[3].LocationPID.Kc = STEPMOTOR_3_KC;
	
	for(i=0;i<TESTMOTORNUMBER;i++)
	{
		MotorControlData[i].LocationPID.OutMax 	= 1;
		MotorControlData[i].LocationPID.OutMin	=	-1;
		MotorControlData[i].LocationPID.calc=&PidCalc;
		MotorControlData[i].LocationPID.clear=&PidClear;
		MotorControlData[i].LocationPID.clear(&MotorControlData[i].LocationPID);
		//------------------PID��ֵ-------------------------

		
		MotorControlData[i].StepMotorInit();
		MotorControlData[i].StepMotorEnable(ENABLE);
		MotorControlData[i].FlagReceiveAngle=0;
	}
}


void MotorControlLogic(void)
{
	u8 i;
	
	MotorControlData[0].LocationPID.Fdb = MotorControlData[0].AngleDataProcessed[0]/180.0f ;		//��һ��
	MotorControlData[1].LocationPID.Fdb = MotorControlData[1].AngleDataProcessed[1]/180.0f ;		//��һ��
	MotorControlData[2].LocationPID.Fdb = MotorControlData[2].AngleDataProcessed[0]/180.0f ;		//��һ��
	MotorControlData[3].LocationPID.Fdb = MotorControlData[3].AngleDataProcessed[1]/180.0f ;		//��һ��
	for(i=0;i<TESTMOTORNUMBER;i++)
	{
		MotorControlData[i].LocationPID.Ref = MotorControlData[i].SetLocation/180.0f;			//�ο���
		
		MotorControlData[i].LocationPID.calc(&MotorControlData[i].LocationPID);
		if(fabs(MotorControlData[i].LocationPID.Out)>DEADZONE_CONVERT)
			MotorControlData[i].StepMotorFrequencyConversion(MotorControlData[i].LocationPID.Out*30000);
		else
			MotorControlData[i].StepMotorPWMEnable(DISABLE);
	}
	
}
