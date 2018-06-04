#ifndef __LED_H
#define __LED_H
#include "sys.h"



//LED端口定义
#define LED0 PDout(8)	// DS0
#define LED1 PDout(9)	// DS1	 

void LED_Init(void);//初始化		 		
void LedSpark(void);

#endif
