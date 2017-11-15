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
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();
	MotorDataInit();			//��ǰ,��ָ�����
	TIM7ConfigureTimerInterrupttion(1);		//��ʱ�жϿ�����1ms����һ��
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
