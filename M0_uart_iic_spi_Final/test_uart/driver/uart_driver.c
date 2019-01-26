#include <stdint.h>
#include <string.h>
#include "uart.h"
#include "uart_driver.h"


uint8_t gRxFlag = 0;//command receive flag
uint32_t RX_NUM = 0;//receive data number
uint8_t RxBuff[2000]={0};//receive data buffer

#define ICER                           *((volatile uint32_t*)0xE000E180)
	
/**
  * @brief  initial uart0.
  * @param  baud rate,the range is 9600bps~115200bps
  *         
  * @retval none
  */	

void hs_uart_init(enumUartDef baud)
{
	//rUARTCR &=~0x01;//����UART
	//rUARTLCR_H &=~(1<<4);//���FIFO
	//��ʼ����������
	//���ò�����Ϊ115200����Ƶ26M��
	//Baud rate divisor BAUDDIV = (FUARTCLK/(16��Baud rate))
	switch ((uint8_t)baud)
	{
		case BAUD_9600:
			rUARTIBRD = 0xa9;//�����ʷ�Ƶ��������
			rUARTFBRD = 0x12;//�����ʷ�ƵС������
		break;
		case BAUD_14400:
			rUARTIBRD = 0x70;//�����ʷ�Ƶ��������
			rUARTFBRD = 0x36;//�����ʷ�ƵС������
		break;
		case BAUD_19200:
			rUARTIBRD = 0x54;//�����ʷ�Ƶ��������
			rUARTFBRD = 0x29;//�����ʷ�ƵС������
		break;
		case BAUD_38400:
			rUARTIBRD = 0x2a;//�����ʷ�Ƶ��������
			rUARTFBRD = 0x15;//�����ʷ�ƵС������
		break;
		case BAUD_43000://??
			rUARTIBRD = 0x25;//�����ʷ�Ƶ��������
			rUARTFBRD = 0x34;//�����ʷ�ƵС������
		break;
		case BAUD_57600:
			rUARTIBRD = 0x1c;//�����ʷ�Ƶ��������
			rUARTFBRD = 0x0e;//�����ʷ�ƵС������
		break;
		case BAUD_76800://??
			rUARTIBRD = 0x15;//�����ʷ�Ƶ��������
			rUARTFBRD = 0x0a;//�����ʷ�ƵС������
		break;
		case BAUD_115200:
			rUARTIBRD = 0x0e;//�����ʷ�Ƶ��������
			rUARTFBRD = 0x06;//�����ʷ�ƵС������
		break;
	}
	
	//rUARTLCR_H |= (1<<5);
	//rUARTLCR_H |= (1<<6);//8λ����λ
	//rUARTLCR_H &=~(1<<3);//1λֹͣλ
	//rUARTLCR_H &=~(1<<1);//��У��λ
	//rUARTLCR_H &=~0x01;
	//rUARTCR &=~(1<<14);
	//rUARTCR &=~(1<<15);//��Ӳ������
	//rUARTCR |= (1<<8);//ʹ��TX
	//rUARTCR |= (1<<9);//ʹ��RX
	
	rUARTCR = 0x300;
	rUARTIFLS = 0x24;
	rUARTLCR_H = 0x60;
	
	rUARTIMSC = (1<<4);//ʹ�ܽ����ж�
	
	rUARTCR |= 0x01; //ʹ��UART
}

/**
  * @brief  Write more than one byte with a single WRITE cycle.
  * @param  ch : single byte to be written.
  * @retval none
  */
void hs_uart_send(uint8_t ch)
{	
	rUARTDR = ch;
	while((rUARTFR&(1<<7))==0);
}

/**
  * @brief  Write more than one byte with a single WRITE cycle.
  * @param  pStr : pointer to the buffer containing the data to be written.
  * @param  ulStrLength : length to the variable holding number of bytes to 
  *         be written.
  * @retval none
  */
void hs_uart_send_str(uint8_t *pStr, uint32_t ulStrLength)
{
	while(ulStrLength--)
	{
		hs_uart_send(*pStr);
		pStr++;
	}
}


/**
  * @brief  This function handles UART0 exception.
  * @param  None
  * @retval None
  */
void UART0_IRQHandler(void)
{
	uint8_t res;
	
	res=(uint8_t)rUARTDR;//read data
    RxBuff[RX_NUM] = res;
	RX_NUM++;
	if(RX_NUM>=2000)
	{
		RX_NUM=0;
	}
	if((RxBuff[0]==0xe0)&&(RxBuff[1]==0x0e))
	{
		if(RX_NUM == ((RxBuff[2]<<8)|RxBuff[3]) )
		{

				gRxFlag =1;

		}						
	}
	rUARTICR|=(1<<4);//clear interrupt
}



