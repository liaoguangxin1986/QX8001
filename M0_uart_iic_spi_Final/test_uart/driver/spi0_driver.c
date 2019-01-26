#include <stdint.h>
#include <string.h>
#include "spi.h"
#include "cfg.h"
#include "dsp_cfg.h"
#include "hs_dsp.h"

extern uint8_t gRxFlag;//command receive flag
extern uint32_t RX_NUM;//receive data number
extern uint8_t RxBuff[2000];//receive data buffer

/**
  * @brief  initial spi0 receive only mode.
  * @param  none
  *         
  * @retval none
  */
void spi0_init(void)
{
	rSSIENR &=~0x01;//禁止SPI
	rCTRLR0 = 0x247;//设置spi为receive only模式，设置SCPOL=0,SCPH=1,Wordlength=8bit
	//rMWCR = 0x00;
	rTXFTLR = 0;//设置接收FIFO中断触发深度为1
	rRXFTLR = 0;//设置发送FIFO中断触发深度为1
	rIMR = 0x14;
	rSSIENR |= 0x01;//开启SPI
}


/**
  * @brief  initial spi0 transfer only mode.
  * @param  none
  *         
  * @retval none
  */
void spi0_init_tx(void)
{
	rSSIENR &=~0x01;//禁止SPI
	rCTRLR0 = 0x147;//设置spi为transfer only模式，设置SCPOL=0,SCPH=1,Wordlength=8bit
	//rMWCR = 0x00;
	rTXFTLR = 0;//设置接收FIFO中断触发深度为1
	rRXFTLR = 0;//设置发送FIFO中断触发深度为1
	rIMR = 0x00;
	rSSIENR |= 0x01;//开启SPI
}



/**
  * @brief  Write more than one byte with a single WRITE cycle.
  * @param  pStr : pointer to the buffer containing the data to be written.
  * @param  ulStrLength : length to the variable holding number of bytes to 
  *         be written.
  * @retval none
  */
void hs_spi0_send_str(uint8_t *pStr, uint32_t ulStrLength)
{
	uint32_t i,j;
	//while((rSR&0x01)==0x00);
	while(ulStrLength)
	{
		if(rTXFLR<0x10){			
			ulStrLength--;
			rDR = *pStr;
			pStr++;	
		}				
	}
	while((rSR&0x04)!=0x04);
}


extern uint8_t RX_Flag;
extern uint16_t CmdType;
extern uint8_t ret;
extern uint8_t Ack[2000];

/**
  * @brief  This function handles SPI0 exception.
  * @param  None
  * @retval None
  */
void SPI0_IRQHandler(void)
{ 
	uint8_t res,status;
	uint32_t i;
	if((rISR&(1<<4))==0x10)
	{
		res=(uint8_t)rDR;//read value
		RxBuff[RX_NUM] = res;
		if(RxBuff[0]==0xff)
		{
			RX_NUM =0;
		}else{
			RX_NUM++;
		}
		
		if((RxBuff[0]==0xe0)&&(RxBuff[1]==0x0e))
		{
			if(RX_NUM == ((RxBuff[2]<<8)|RxBuff[3]))
			gRxFlag =1;			
		}
		status= rICR;//clear interrupt
	}

	if((rISR&0x01)==0x01)
	{
		status= rICR;//clear interrupt
	}
}
