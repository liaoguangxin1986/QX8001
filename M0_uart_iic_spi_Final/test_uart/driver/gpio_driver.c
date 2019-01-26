#include <stdint.h>
#include "gpio.h"
#include "gpio_driver.h"


/**
  * @brief  initial GPIO0.
  * @param  dir:gpio0 direction,the value can be one of below:
			-\Input
			-\Output
  * @param  GPIO_Pin:gpio0 pin number,the value range is 0~7:
  * @retval None
  */
void GPIO_Init(GPIO_Dir dir,uint8_t GPIO_Pin)
{	
	if(dir==Output)
	{
		rGPIODIR |= (1<<GPIO_Pin);
	}else{
		rGPIODIR &=~ (1<<GPIO_Pin);
	}
}


/**
  * @brief  set gpio0 output HIGH level.
  * @param  GPIO_Pin:gpio0 pin number,the value range is 0~7:
  * @retval None
  */
void GPIO_SetBit(uint8_t GPIO_Pin)
{
	*((volatile uint32_t*)(rGPIODATA_BASE+(1<<(GPIO_Pin+2))))|=(1<<GPIO_Pin);
}


/**
  * @brief  set gpio0 output LOW level.
  * @param  GPIO_Pin:gpio0 pin number,the value range is 0~7:
  * @retval None
  */
void GPIO_ResetBit(uint8_t GPIO_Pin)
{
	*((volatile uint32_t*)(rGPIODATA_BASE+(1<<(GPIO_Pin+2))))&=~(1<<GPIO_Pin);
}


/**
  * @brief  read gpio0 INPUT level.
  * @param  GPIO_Pin:gpio0 pin number,the value range is 0~7:
  * @retval GPIO0 input value
  */
uint8_t GPIO_ReadOutputDataBit(uint8_t GPIO_Pin)
{
	if((*((volatile uint32_t*)(rGPIODATA_BASE+(1<<(GPIO_Pin+2))))&(1<<GPIO_Pin))!=0x00)
	{
		return 1;
	}else{
		return 0;
	}
}


/**
  * @brief  This function handles GPIO0 exception.
  * @param  None
  * @retval None
  */
void GPIO0_IRQHandler(void)
{

}


