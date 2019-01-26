#include <stdint.h>
#include <string.h>
#include "i2c.h"
#include "dsp_cfg.h"
#include "hs_dsp.h"
#include "sys.h"

extern uint8_t gRxFlag;//command receive flag
extern uint32_t RX_NUM ;//receive data number
extern uint8_t RxBuff[2000];//receive data buffer


/**
  * @brief  initial iic0 slave mode,the slave address is 0x18.
  * @param  none
  *         
  * @retval none
  */
void i2c0_init(void)
{
	rIC0_ENABLE &=~0x01;//禁能IIC
	rIC0_SAR = 0x018;//设置从机地址0x18
//	rIC0_CON &=~(1<<3);//设置从机地址为7bit
//	rIC0_CON &=~(1<<2);
//	rIC0_CON |= (1<<1);//设置速度为standard mode（0~100k）
//	
//	rIC0_CON &=~ 0x01;//禁能master mode
//	rIC0_CON &=~(1<<6);//使能slave mode
	rIC0_CON = 0x02;
	rIC0_RX_TL = 0;//设置接收FIFO中断触发深度为1
	rIC0_TX_TL = 0;//设置发送FIFO中断触发深度为1
	rIC0_INTR_MASK = 0x024;//打开

	rIC0_ENABLE |= 0x01;//使能IIC
}

/**
  * @brief  Write more than one byte with a single WRITE cycle.
  * @param  ch : single byte to be written.
  * @retval none
  */
void hs_i2c0_send(uint8_t ch)
{
		rIC0_DATA_CMD = 0x000 |ch;
}

/**
  * @brief  Write more than one byte with a single WRITE cycle.
  * @param  pStr : pointer to the buffer containing the data to be written.
  * @param  ulStrLength : length to the variable holding number of bytes to 
  *         be written.
  * @retval none
  */
void hs_i2c0_send_str(uint8_t *pStr, uint32_t ulStrLength)
{

	while(ulStrLength--)
	{
		hs_i2c0_send(*pStr);
		pStr++;
	}
}
extern uint8_t RX_Flag;
extern uint16_t CmdType;
extern uint8_t ret;
extern uint8_t Ack[2000];

/**
  * @brief  This function handles I2C0 exception.
  * @param  None
  * @retval None
  */
void I2C0_IRQHandler(void)
{ 
	uint8_t status;
	uint32_t i;

	if(rIC0_RAW_INTR_STAT&(1<<5))
	{	
		for(i=0;i<14;i++)
		{		
			rIC0_DATA_CMD=Ack[i];//write data
			while((rIC0_RAW_INTR_STAT&(1<<4))==0);//wait write data finish
		}
		status=rIC0_CLR_RD_REQ;	//clear interrupt
	}

	if(rIC0_RAW_INTR_STAT&(1<<2))
	{
		uint8_t res;
		while((rIC0_RAW_INTR_STAT&(1<<2))==0);//wait read data finish
		res=(uint8_t)rIC0_DATA_CMD;//read data
		status =rIC0_CLR_RX_OVER;//clear interrupt
		RxBuff[RX_NUM] = res;
		RX_NUM++;
		if((RxBuff[0]==0xe0)&&(RxBuff[1]==0x0e))
		{
			if(RX_NUM == ((RxBuff[2]<<8)|RxBuff[3]) )
			gRxFlag =1;			
		}
		
	}
}

