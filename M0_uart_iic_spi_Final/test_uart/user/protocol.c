#include <string.h>
#include "uart_driver.h"
#include "protocol.h"
#include "dsp_cfg.h"
#include "cfg.h"
#include "hs_dsp.h"
#include "sys.h"
#include "gpio.h"
#include "gpio_driver.h"
#include "spi0_driver.h"
#include "i2c0_driver.h"
#include "i2c1_driver.h"

extern uint8_t gRxFlag;
extern uint32_t RX_NUM;
extern uint8_t RxBuff[2000];

uint8_t ret;
uint8_t Ack[2000]={0};
uint16_t CmdType;

extern uint8_t gMode;
void hs_data_send(uint8_t *pStr, uint32_t ulStrLength)
{

		//hs_uart_send_str(pStr,ulStrLength);

}
uint32_t i=0;
void hs_protocol()
{
	uint8_t GPIO_Pin,PinVal,eye,level,mode,delLevel;
	uint16_t index,packLengh,packNum;
	uint8_t buff[1200];
	uint16_t RegAddr,SetVal,RdVal,REG_NUM;
	uint32_t REG_Addr,REG_Val;
	uint8_t retry=5;
	
	while(1)
	{
		
		if(DSP_CUR_STA == 0x84)
		{
			if(((DSP_TMPL_ENCODE_CTRL&(1<<4))==(1<<4))&&((DSP_TMPL_ENCODE_CTRL&(1<<5))==0x00))
			{
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_20)))
				{
					rGPIO5DATA &=~(1<<5);
					rGPIO6DATA |=(1<<6);
				}else{
					rGPIO5DATA |=(1<<5);
					rGPIO6DATA &=~(1<<6);
				}	
			}else if(((DSP_TMPL_ENCODE_CTRL&(1<<4))==0x00)&&((DSP_TMPL_ENCODE_CTRL&(1<<5))==(1<<5))){
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_20>>16)))
				{
					rGPIO5DATA &=~(1<<5);
					rGPIO6DATA |=(1<<6);
				}else{
					rGPIO5DATA |=(1<<5);
					rGPIO6DATA &=~(1<<6);
				}	
			}else{
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_21)))
				{
					rGPIO5DATA &=~(1<<5);
					rGPIO6DATA |=(1<<6);
				}else{
					rGPIO5DATA |=(1<<5);
					rGPIO6DATA &=~(1<<6);
				}	
			}	
		}else{
			rGPIO5DATA &=~(1<<5);
			rGPIO6DATA &=~(1<<6);
		}
		
		if (gRxFlag)
		{
			//if(RxBuff[RX_NUM]==CalCRC8(RxBuff,RX_NUM))
			if(1)
			{	
				
				CmdType = RxBuff[4]<<8|RxBuff[5];
				switch(CmdType)
				{
					
					case DOWNLOAD_TEMPLATE:						
							//packLengh = RxBuff[7]<<8|RxBuff[8]-2;
							packNum = RxBuff[9];
							memcpy(buff,RxBuff+11,1024);
							IrisDownloadTemp(buff,1024,packNum,RxBuff[10]);
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0b;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x01;
							Ack[9]=packNum;
							Ack[10]=CalCRC8(Ack,10);
							hs_data_send(Ack,11);
					
						break;
					case UPLOAD_TEMPLATE:						
							//packLengh = RxBuff[7]<<8|RxBuff[8];
							packNum = RxBuff[9];
							IrisUploadTemp(buff,1024,packNum,RxBuff[10]);
							memcpy(Ack+11,buff,1024);
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x04;
							Ack[3]=0x0b;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x04;
							Ack[8]=0x01;
							Ack[9]=packNum;
							Ack[1034]=CalCRC8(Ack,1034);
							hs_data_send(Ack,1035);
						break;			
					case DOWNLOAD_IMAG_PIC:						
							//packLengh = RxBuff[7]<<8|RxBuff[8];
							packNum = RxBuff[9]<<8|RxBuff[10];
							memcpy(buff,RxBuff+11,1024);
							IrisDownloadImag(buff,1024,packNum);
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0c;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x00;
							Ack[9]=(uint8_t)(packNum>>8);
							Ack[10]=(uint8_t)packNum;
							Ack[11]=0x66;//CalCRC8(Ack,11);

							hs_data_send(Ack,12);
						
						break;	
					case UPLOAD_IMAG_PIC:						
							//packLengh = RxBuff[7]<<8|RxBuff[8];
							packNum = RxBuff[9]<<8|RxBuff[10];
							IrisUploadImag(buff,1024,packNum);
							memcpy(Ack+11,buff,1024);
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x04;
							Ack[3]=0x0c;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x04;
							Ack[8]=0x02;
							Ack[9]=(uint8_t)(packNum>>8);
							Ack[10]=(uint8_t)packNum;
							Ack[1035]=CalCRC8(Ack,1035);
							hs_data_send(Ack,1036);
						break;
					
					case GPIO_OUTPUT:						
							GPIO_Pin = RxBuff[9];
							PinVal= RxBuff[10];
							GPIO_Init(Output,GPIO_Pin);
							if(PinVal)
							{
								GPIO_SetBit(GPIO_Pin);
							}else{
								GPIO_ResetBit(GPIO_Pin);
							}						
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0a;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x00;
							Ack[9]=CalCRC8(Ack,9);
							hs_data_send(Ack,10);		
						break;	
					case GPIO_INPUT:						
							GPIO_Pin = RxBuff[9];
							GPIO_Init(Input,GPIO_Pin);
							ret = GPIO_ReadOutputDataBit(GPIO_Pin);
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0a;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=ret;
							Ack[7]=0x00;
							Ack[8]=0x00;
							Ack[9]=CalCRC8(Ack,9);
							hs_data_send(Ack,10);			
						break;	
					case WRITE_REG:						
							REG_Addr = RxBuff[9]<<24|RxBuff[10]<<16|RxBuff[11]<<8|RxBuff[12];
							REG_Val = RxBuff[13]<<24|RxBuff[14]<<16|RxBuff[15]<<8|RxBuff[16];
							*((volatile uint32_t*)REG_Addr)= REG_Val;
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0a;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x00;
							Ack[9]=CalCRC8(Ack,9);
							hs_data_send(Ack,10);				
						break;	
					case WRITE_BULK_REG:						
							REG_Addr = RxBuff[9]<<24|RxBuff[10]<<16|RxBuff[11]<<8|RxBuff[12];
							REG_NUM = RxBuff[13]<<8|RxBuff[14];
							for(i=0;i<REG_NUM;i++)
							{
								*((volatile uint32_t*)(REG_Addr+4*i))= RxBuff[15+4*i]<<24|RxBuff[16+4*i]<<16|RxBuff[17+4*i]<<8|RxBuff[18+4*i];
							}
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0a;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x00;
							Ack[9]=CalCRC8(Ack,9);
							hs_data_send(Ack,10);				
						break;	
				  case MODIFY_SENSOR:						
							RegAddr = RxBuff[9]<<8|RxBuff[10];
							SetVal = RxBuff[11]<<8|RxBuff[12];
							i2c1_wr_data(RegAddr,SetVal);
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0a;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x00;
							Ack[9]=CalCRC8(Ack,9);
							hs_data_send(Ack,10);				
						break;	
				   case READ_SENSOR:						
							RegAddr = RxBuff[9]<<8|RxBuff[10];
							RdVal = i2c1_rd_8data(RegAddr);
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0c;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x02;
							Ack[9]=0x00;//(uint8_t)(RdVal>>8);
							Ack[10]=(uint8_t)RdVal;
							Ack[11]=CalCRC8(Ack,11);
				   
							hs_data_send(Ack,12);
						break;	
				   case READ_REG:						
							REG_Addr = RxBuff[9]<<24|RxBuff[10]<<16|RxBuff[11]<<8|RxBuff[12];
							REG_Val = *((volatile uint32_t*)REG_Addr);
				   
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0e;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x04;
							Ack[9]=(uint8_t)(REG_Val>>24);
							Ack[10]=(uint8_t)(REG_Val>>16);
							Ack[11]=(uint8_t)(REG_Val>>8);
							Ack[12]=(uint8_t)REG_Val;
							Ack[13]=CalCRC8(Ack,13);

							hs_data_send(Ack,14);
			
						break;	
				    case READ_BULK_REG:						
							REG_Addr = RxBuff[9]<<24|RxBuff[10]<<16|RxBuff[11]<<8|RxBuff[12];
							REG_NUM = RxBuff[13]<<8|RxBuff[14];
							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=(uint8_t)((REG_NUM*4+10)>>8);
							Ack[3]=(uint8_t)(REG_NUM*4+10);
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=(uint8_t)((REG_NUM*4)>>8);
							Ack[8]=(uint8_t)(REG_NUM*4);
							for(i=0;i<REG_NUM;i++){
								Ack[9+4*i]=(uint8_t)((*((volatile uint32_t*)(REG_Addr+4*i)))>>24);
								Ack[10+4*i]=(uint8_t)((*((volatile uint32_t*)(REG_Addr+4*i)))>>16);
								Ack[11+4*i]=(uint8_t)((*((volatile uint32_t*)(REG_Addr+4*i)))>>8);
								Ack[12+4*i]=(uint8_t)(*((volatile uint32_t*)(REG_Addr+4*i)));
							}
							Ack[13+4*(REG_NUM-1)]=CalCRC8(Ack,13+4*(REG_NUM-1));
							hs_data_send(Ack,14+4*(REG_NUM-1));
						break;	
					case CRC8_ERROR:						

							Ack[0]=0xe0;
							Ack[1]=0x0e;
							Ack[2]=0x00;
							Ack[3]=0x0a;
							Ack[4]=(uint8_t)(CmdType>>8);
							Ack[5]=(uint8_t)CmdType;
							Ack[6]=0x00;
							Ack[7]=0x00;
							Ack[8]=0x00;
							Ack[9]=CalCRC8(Ack,9);
							hs_data_send(Ack,10);
						break;	
					default:					
						break;	
				}
			
			}else{						
				Ack[0]=0xe0;
				Ack[1]=0x0e;
				Ack[2]=0x00;
				Ack[3]=0x0a;
				Ack[4]=0xff;
				Ack[5]=0xff;
				Ack[6]=0x00;
				Ack[7]=0x00;
				Ack[8]=0x00;
				Ack[9]=CalCRC8(Ack,9);
				hs_data_send(Ack,10);
			}
			gRxFlag = 0;
			RX_NUM = 0;
			memset(RxBuff,0,1200);
		}	
				
	}
}

