#ifndef _UART_DRIVER_H_
#define _UART_DRIVER_H_
#include <stdint.h>
	 
	 
typedef enum 
{
	BAUD_9600=1,
	BAUD_14400,
	BAUD_19200,
	BAUD_38400,
	BAUD_43000,
	BAUD_57600,
	BAUD_76800,
	BAUD_115200
}enumUartDef;	
	 
extern void hs_uart_init(enumUartDef baud);
extern void hs_uart_send(uint8_t ch);
extern void hs_uart_send_str(uint8_t *pStr, uint32_t ulStrLength);
	 

#endif
