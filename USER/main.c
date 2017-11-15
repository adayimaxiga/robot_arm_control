#include "main.h"

MotorControlStruct MotorControlData[NUMBEROFMOTOR];

void MotorDataInit(void);			

void UserDefinition()		//1ms
{
	static int Count;
	Count++;
	
	MotorControlData[0].SetLocation = Count;
	
}

int main(void)
{
	delay_init(168);		  //初始化延时函数
	LED_Init();
	MotorDataInit();			//靠前,有指针操作
	TIM7ConfigureTimerInterrupttion(1);		//定时中断开启，1ms调度一次
  while(1)
	{
		if(FlagTim7Inturrupt)
		{
			UserDefinition();
			MotorControlLogic();
			LedSpark();
			FlagTim7Inturrupt =0;
		}
	}
}
