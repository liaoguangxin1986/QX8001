#include <string.h>
#include <stdint.h>
#include "cfg.h"
#include "gpio.h"
#include "uart_driver.h"
#include "protocol.h"
#include "i2c1_driver.h"
#include "spi0_driver.h"
#include "i2c0_driver.h"
#include "ar0237_driver.h"
#include "dsp_cfg.h"
#include "sys.h"
#include "pll_driver.h"
#include "hs_dsp.h"
#include "mipi_csi0_driver.h"
#include "ov2281_driver.h"


#define ICPR                           *((volatile uint32_t*)0xE000E280)	
#define ICER                           *((volatile uint32_t*)0xE000E180)
#define ISER                           *((volatile uint32_t*)0xE000E100)
	

#define ISP_IMAGE_W_H                   *((volatile uint32_t*)0x4000912C)
#define ISP_IMAGE_OUT_W_H               *((volatile uint32_t*)0x40009130)
	
#define SENSOR_SEL                      *((volatile uint32_t*)0x40009154)	
	
#define ICPR                           *((volatile uint32_t*)0xE000E280)	

#define ISER                           *((volatile uint32_t*)0xE000E100)	
	
#define IPR0                           *((volatile uint32_t*)0xE000E400)
#define IPR1                           *((volatile uint32_t*)0xE000E404)	
#define IPR2                           *((volatile uint32_t*)0xE000E408)	
#define IPR3                           *((volatile uint32_t*)0xE000E40C)	
#define IPR4                           *((volatile uint32_t*)0xE000E410)	
#define IPR5                           *((volatile uint32_t*)0xE000E414)	
#define IPR6                           *((volatile uint32_t*)0xE000E418)	
#define IPR7                           *((volatile uint32_t*)0xE000E41C)

uint8_t gMode=0;
int main(void)
{

	ICER = 0xfff;//clear all interrupt
	ICPR = 0xfff;//remove pending state of all interrupt
	IPR0 |= (1<<14); //Set dsp2 interrupt priority 
	ISER = 0xfff;  //enable cm0 int
	TEST_KEY = 0x77686873;//enable write register	
	SW_BOOTLINK_EN |= 0x01;//enable bootlink

	pll_init();
	DSP_CTRL|=0x01;//enable dsp clk
			
	while(DSP_CUR_STA!=0x81);//wait DSP ready
	DSP_CMD |= 0x10000;//set INT pin HIGH level
	
	GPIO0_CTRL |= 0x01;//enable gpio clk
	I2C1_CTRL |= 0x01;//enable i2c1	clk

	
	
	DSP_WR_EN3 = 0x77686873;//enable write special register
	SET_ENCODE_TIMEOUT = 100000000*8;//设置注册超时时间	//8s
	DSP_WR_EN3 = 0x00;//disable write special register

	
	DSP_WR_EN3 = 0x77686873;//enable write special register
	WRITE_TEMP_TIMEOUT = 0xffffffff;//设置注册超时时间	
	DSP_WR_EN3 = 0x00;//disable write special register
	
	//ISP_IMAGE_W_H = 0x043c0780;
	ISP_IMAGE_W_H = 0x04380780;//设置图像区大小为1920*1080
	ISP_IMAGE_OUT_W_H = 0x00b40140; //设置输出图像大小为320*180
	
	MIPI_CSI_CTRL|=0x02; //打开MIPI采样时钟
	 
	EXT_CLK_CTRL = 0x01;//enable external clock output
	//SENSOR_SEL = 0x03;//sensor选择PARA
	SENSOR_SEL = 0x02;//sensor选择MIPI
   
	i2c1_init();
	mipi_csi0_init();
	ov2281_init();
		
	rGPIODIR|=(1<<5)|(1<<6);//set GPIO5&GPIO6 output
	rGPIO5DATA &=~(1<<5);//set GPIO5 low level
	rGPIO6DATA &=~(1<<6);//set GPIO6 low level
	
	UART0_CTRL |= 0x01;//enable uart0		
	SPI0_SEL&=~0x01;//select iic mode
	I2C0_CTRL |= 0x01;//enable i2c0
	//hs_uart_init(BAUD_115200);
	i2c0_init();
	
	hs_protocol();	
}


