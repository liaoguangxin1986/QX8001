#ifndef _GPIO_DRIVER_H_
#define _GPIO_DRIVER_H_

#include <stdint.h>

typedef enum{
	Input=0,
	Output	
}GPIO_Dir;

extern void GPIO_Init(GPIO_Dir dir,uint8_t pinNum);
extern void GPIO_SetBit(uint8_t GPIO_Pin);
extern void GPIO_ResetBit(uint8_t GPIO_Pin);
extern uint8_t GPIO_ReadOutputDataBit(uint8_t GPIO_Pin);

#endif
