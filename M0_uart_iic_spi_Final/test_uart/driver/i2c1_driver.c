#include <stdint.h>
#include "i2c.h"
#include "sys.h"


/**
  * @brief  initial master iic1.
  * @param  none
  *         
  * @retval none
  */
void i2c1_init(void)
{
	rIC1_ENABLE &=~0x01;//禁能IIC
	rIC1_CON = 0x65;
	rIC1_TAR = 0x10;//设置从机地址
	rIC1_SS_SCL_LCNT = 35;//设置低电平clk
	rIC1_SS_SCL_HCNT = 21;//设置高电平clk

    rIC1_INTR_MASK = 0x04; //打开IIC RX_FULL中断

    rIC1_RX_TL = 1;//设置接收FIFO中断触发深度为1

    rIC1_TX_TL = 4;	//设置发送FIFO中断触发深度为4
	
	rIC1_ENABLE |= 0x01;//使能IIC
}

/**
  * @brief  config sensor register .
  * @param   sub_addr: address of sensor register.
  * @param   wr_dat: value of sensor register.
  * @retval none
  */
void i2c1_wr_data(uint16_t sub_addr,uint16_t wr_dat)
{
    int j;

    rIC1_DATA_CMD = 0x000 |(char)(sub_addr/256);   
	rIC1_DATA_CMD = 0x000 |(char)(sub_addr%256);
    rIC1_DATA_CMD = 0x000 |(char)(wr_dat/256);      
	rIC1_DATA_CMD = 0x200 |(char)(wr_dat%256);
    //wait 70us
    for(j=0;j<5000;j++); //wait

}

/**
  * @brief  config sensor register .
  * @param   sub_addr: address of sensor register.
  * @param   wr_dat: value of sensor register.
  * @retval none
  */
void i2c1_wr_8data(uint16_t sub_addr,uint8_t wr_dat)
{
    int j;

    rIC1_DATA_CMD = 0x000 |(char)(sub_addr/256);   
	rIC1_DATA_CMD = 0x000 |(char)(sub_addr%256);
	rIC1_DATA_CMD = 0x200 |wr_dat;
    //wait 70us
    for(j=0;j<5000;j++); //wait

}

uint8_t data1=0,data2=0;

/**
  * @brief  read value of sensor register .
  * @param   sub_addr: address of sensor register.
  * @retval sensor register value
  */
uint16_t i2c1_rd_data(uint16_t sub_addr)
{
    uint16_t rd_dat=0;
    int j;	
    rIC1_DATA_CMD = 0x000 |(char)(sub_addr>>8);
	//while(rIC1_RAW_INTR_STAT&(1<<4));	
	rIC1_DATA_CMD = 0x000 |(char)(sub_addr);
	//while(rIC1_RAW_INTR_STAT&(1<<4));
    rIC1_DATA_CMD |= 0x500; 
	
	rIC1_DATA_CMD |= 0x300;
	delay(1000);
	rd_dat =data1<<8|data2; 
		
    return   rd_dat;
}

#if 0


uint8_t i2c1_rd_8data(uint16_t sub_addr)
{
    uint8_t rd_dat=0;
    int j;	
    rIC1_DATA_CMD = 0x000 |(char)(sub_addr>>8);   
	rIC1_DATA_CMD = 0x000 |(char)(sub_addr);
    rIC1_DATA_CMD |= 0x500; 
	rd_dat        |=(char)(rIC1_DATA_CMD<<8);
	
	
	rIC1_DATA_CMD |= 0x300; 

	rd_dat = (char)rIC1_DATA_CMD;
    return   rd_dat;
}


void I2C1_IRQHandler(void)
{ 
	//uint16_t j=0;
	if(rIC1_RAW_INTR_STAT&(1<<2))
	{
		data1=rIC1_DATA_CMD;
		data2=rIC1_DATA_CMD;
		//j++;
	}
}	
#endif

/**
  * @brief  read value of sensor register .
  * @param   sub_addr: address of sensor register.
  * @retval sensor register value
  */
uint8_t i2c1_rd_8data(uint16_t sub_addr)
{
    uint8_t rd_dat=0;
    int j;	
    rIC1_DATA_CMD = 0x000 |(char)(sub_addr>>8);   
	rIC1_DATA_CMD = 0x000 |(char)(sub_addr);
    rIC1_DATA_CMD |= 0x700; 
	//rd_dat        |=(char)(rIC1_DATA_CMD<<8);
   // for(j=0;j<5000;j++); //wait	
	//rd_dat        |=((char)rIC1_DATA_CMD )<< 8;
    //for(j=0;j<5000;j++); //wait		
	
	//rIC1_DATA_CMD |= 0x300; 
	delay(1000);
	rd_dat = data1;
    return   rd_dat;
}

/**
  * @brief  This function handles I2C1 exception.
  * @param  None
  * @retval None
  */
void I2C1_IRQHandler(void)
{ 
	//uint16_t j=0;
	if(rIC1_RAW_INTR_STAT&(1<<2))
	{
		data1=rIC1_DATA_CMD;
		//data2=rIC1_DATA_CMD;
		//j++;
	}
}

