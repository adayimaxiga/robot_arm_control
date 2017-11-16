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

#define DEADZONE (3.0f)			//°
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
	}CharToShort;																							//类型转换
	
	float AccelerateDataProcessed[3];													//陀螺仪加速度
	float GyroDataProcessed[3];																//陀螺仪角速度
	float AngleDataProcessed[3];															//欧拉角度
	float Temperature;																				//温度量
	
	MotorRotationEnum MotorRotation;													//电机旋转方向保存
	
	void (*StepMotorInit)();																	//电机参数初始化函数，必须第一个调用
	void (*StepMotorEnable)(u8 Judge);												//电机使能 ENABLE  or  DISABLE
	void (*StepMotorDirection)(MotorRotationEnum Rotation);		//设定旋转方向，CLOCKWISE或者ANTICLOCKWISE
	void (*StepMotorPWMEnable)(u8 Judge);		//设定旋转方向，CLOCKWISE或者ANTICLOCKWISE
	void (*StepMotorFrequencyConversion)(int Frequency);			//设定PWM频率，即时生效，符号代表方向  10kHz以内
	
	float SetLocation;																				//设定角度
	
	PID LocationPID;																					//位置环PID计算
	
	u8 FlagReceiveAngle;
	
	u8 UsartBuffer[USATRBUFFERSIZE];													//通信缓存
}MotorControlStruct;

typedef struct 
{
	union
	{
		u8 Char[8];
		short Short[4];
	}CharToShort;																							//类型转换
	
	float AccelerateDataProcessed[3];													//陀螺仪加速度
	float GyroDataProcessed[3];																//陀螺仪角速度
	float AngleDataProcessed[3];															//欧拉角度
	float Temperature;																				//温度量
	u8 FlagReceiveAngle;
	
	u8 UsartBuffer[USATRBUFFERSIZE];													//通信缓存
}GyroDataStruct;


void MotorControlLogic(void);

extern GyroDataStruct GyroData;
extern MotorControlStruct MotorControlData[];
extern u8 FlagTim7Inturrupt;																//全局变量声明

//断言

#define IS_MOTOR_ROTATION(ROTATION) (((ROTATION) == ANTICLOCKWISE) || ((ROTATION) == CLOCKWISE))
#define IS_MOTOR_FREQUENCY(FREQUENCY) (FREQUENCY<100001 && FREQUENCY>-100001)

#endif
