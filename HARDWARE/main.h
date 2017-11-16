/*
		@ChipType:	STM32F407ZET6		
		@Author: 		LD
		@Date:			2017.11.14
		@LED:							PF9				PF10
		@Number:					1					2					3					4						5			
		@Usart:						1					2					3					4						5
		@Usart_Rx:				PB7				PA3				PC11			PA1				PD2
		@Motor:						1					2					3					4					
		@Motor_Enable:		PB8				PA4				PD11			PB12			
		@Motor_Direction:	PB9				PA5				PD13			PB13			
		@Timer:						2					3					4					5					
		@Timer_Channal:		CH3				CH1				CH1				CH3				
		@Timer_Pin:				PB10			PA6				PD12			PA2
*/

#ifndef __MAIN_H
#define __MAIN_H
#include "sys.h"
#include "pid.h"
#include "bsp_usart.h"
#include "bsp_tim.h"
#include "delay.h"
#include "led.h"

#define USATRBUFFERSIZE (11)

#define NUMBEROFMOTOR (4)
#define TESTMOTORNUMBER (4)

#define STEPMOTOR_0_KP (3)				//5
#define STEPMOTOR_0_KI (0)
#define STEPMOTOR_0_KD (0)
#define STEPMOTOR_0_KC (0)
#define STEPMOTOR_0_INIT_ANGLE	(0)

#define STEPMOTOR_1_KP (3)
#define STEPMOTOR_1_KI (0)
#define STEPMOTOR_1_KD (0)
#define STEPMOTOR_1_KC (0)
#define STEPMOTOR_1_INIT_ANGLE	(-45)

#define STEPMOTOR_2_KP (3)
#define STEPMOTOR_2_KI (0)
#define STEPMOTOR_2_KD (0)
#define STEPMOTOR_2_KC (0)
#define STEPMOTOR_2_INIT_ANGLE	(0)

#define STEPMOTOR_3_KP (3)
#define STEPMOTOR_3_KI (0)
#define STEPMOTOR_3_KD (0)
#define STEPMOTOR_3_KC (0)
#define STEPMOTOR_3_INIT_ANGLE	(0)

#define DEADZONE (3.0f)			//��
#define DEADZONE_CONVERT (DEADZONE/180.0f)


typedef enum
{
	ANTICLOCKWISE =0,
	CLOCKWISE = 1,
}MotorRotationEnum;

typedef struct
{
	union
	{
		u8 Char[8];
		short Short[4];
	}CharToShort;																							//����ת��
	
	float AccelerateDataProcessed[3];													//�����Ǽ��ٶ�
	float GyroDataProcessed[3];																//�����ǽ��ٶ�
	float AngleDataProcessed[3];															//ŷ���Ƕ�
	float Temperature;																				//�¶���
	
	MotorRotationEnum MotorRotation;													//�����ת���򱣴�
	
	void (*StepMotorInit)();																	//���������ʼ�������������һ������
	void (*StepMotorEnable)(u8 Judge);												//���ʹ�� ENABLE  or  DISABLE
	void (*StepMotorDirection)(MotorRotationEnum Rotation);		//�趨��ת����CLOCKWISE����ANTICLOCKWISE
	void (*StepMotorPWMEnable)(u8 Judge);		//�趨��ת����CLOCKWISE����ANTICLOCKWISE
	void (*StepMotorFrequencyConversion)(int Frequency);			//�趨PWMƵ�ʣ���ʱ��Ч�����Ŵ�����  10kHz����
	
	float SetLocation;																				//�趨�Ƕ�
	
	PID LocationPID;																					//λ�û�PID����
	
	u8 FlagReceiveAngle;
	
	u8 UsartBuffer[USATRBUFFERSIZE];													//ͨ�Ż���
}MotorControlStruct;

typedef struct 
{
	union
	{
		u8 Char[8];
		short Short[4];
	}CharToShort;																							//����ת��
	
	float AccelerateDataProcessed[3];													//�����Ǽ��ٶ�
	float GyroDataProcessed[3];																//�����ǽ��ٶ�
	float AngleDataProcessed[3];															//ŷ���Ƕ�
	float Temperature;																				//�¶���
	u8 FlagReceiveAngle;
	
	u8 UsartBuffer[USATRBUFFERSIZE];													//ͨ�Ż���
}GyroDataStruct;


void MotorControlLogic(void);

extern GyroDataStruct GyroData;
extern MotorControlStruct MotorControlData[];
extern u8 FlagTim7Inturrupt;																//ȫ�ֱ�������

//����

#define IS_MOTOR_ROTATION(ROTATION) (((ROTATION) == ANTICLOCKWISE) || ((ROTATION) == CLOCKWISE))
#define IS_MOTOR_FREQUENCY(FREQUENCY) (FREQUENCY<100001 && FREQUENCY>-100001)

#endif
