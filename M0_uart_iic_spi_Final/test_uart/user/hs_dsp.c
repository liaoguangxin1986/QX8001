#include <stdint.h>
#include "dsp_cfg.h"
#include "gpio.h"
#include "uart_driver.h"
#include "sys.h"

extern uint8_t SensorReady;

/**
  * @brief  Send encode command to the QX8001 and start encode.
  * @param  eye:indicate which eye to encode ,the value can be one of below:
            -\LeftEye
			-\RightEye
			-\DoubleEye
  * @param  level:indicate encode quality level ,the value can be one of below:
            -\LowQuaulity
			-\MidQuaulity
			-\HighQuaulity
  * @retval return value from QX8001,the value can be one of below:
			-\ENCODE_TIMEOUT
			-\ENCODE_OK
			-\HS_HAL_BUSY
  */
uint8_t IrisEncoded(EyeType eye,EncodeQuaulityLevel level)
{
	//while(!SensorReady);
	if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		if (eye==RightEye)
		{
			//设置左眼编码
			DSP_TMPL_ENCODE_CTRL |= (1<<1);
			DSP_TMPL_ENCODE_CTRL &=~ 0x01;
		}else if(eye==LeftEye){
			//设置右眼编码
			DSP_TMPL_ENCODE_CTRL &=~ (1<<1);
			DSP_TMPL_ENCODE_CTRL |= 0x01;
		}else{
			//设置双眼编码
			DSP_TMPL_ENCODE_CTRL |=(1<<1);
			DSP_TMPL_ENCODE_CTRL |= 0x01;
		}
		if(level == LowQuaulity)
		{
			//设置编码等级为低
			DSP_TMPL_ENCODE_CTRL |= (1<<4);
			DSP_TMPL_ENCODE_CTRL &=~ (1<<5);
		}else if(level==MidQuaulity)
		{
			//设置编码等级为中
			DSP_TMPL_ENCODE_CTRL &=~ (1<<4);
			DSP_TMPL_ENCODE_CTRL |= (1<<5);
		}else{
			//设置编码等级为高
			DSP_TMPL_ENCODE_CTRL |= (1<<4);
			DSP_TMPL_ENCODE_CTRL |= (1<<5);
		}

		DSP_TMPL_ENCODE_CTRL |= (1<<2);//设置编码模式为Location & Encode
		DSP_TMPL_ENCODE_CTRL |= (1<<3);//设置编码模式为LoadImag
		DSP_CMD |= 0x07;//开始编码

		
		while(!(DSP_CMD_STATUS&(1<<3)))//等待虹膜编码结束且模板有效
		{
			
			if(DSP_ERR_STATUS&(1<<3))//判断编码是否超时
			{

				return ENCODE_TIMEOUT;
			}
			
		}

		return ENCODE_OK;
		
	}else{	

		return HS_HAL_BUSY;
	}
}

/**
  * @brief  Send save template command to the QX8001 and start save.
  * @param  template index value(0~255).
  * @retval return value from QX8001,the value can be one of below:
			-\WRITE_READ_FLASH_TIMEOUT
			-\TEMPLATE_INDEX_OVER
			-\WRITE_READ_FLASH_OK
			-\WRITE_READ_FLASH_MATCH_ERROR
			-\HS_HAL_BUSY  
  */
uint8_t IrisSaveTemplate(uint32_t index)
{
	if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		DSP_RX_TMPL_INDEX = index;//设置编码索引
		DSP_RX_TMPL_INDEX &=~(1<<16);//select template BRAM A
		DSP_CMD |= 0x08;//将模板写入到FLASH
		if(DSP_ERR_STATUS&(1<<2))//判断索引是否溢出
		{
			return TEMPLATE_INDEX_OVER;	
		}
		while(!(DSP_CMD_STATUS&(1<<8)))//等待模板写入完成
		{
			if(DSP_ERR_STATUS&0x01)//判断读写FLASH是否超时
			{
				return WRITE_READ_FLASH_TIMEOUT;
			}
		}
		if(DSP_ERR_STATUS&(1<<1))//判断读写FLASH是否正确
		{
			return WRITE_READ_FLASH_MATCH_ERROR;
		}
		return WRITE_READ_FLASH_OK;
	}else{
		
		return HS_HAL_BUSY;		
	}		
}

/**
  * @brief  Send get template command to the QX8001 and start get.
  * @param  template index value(0~255).
  * @retval return value from QX8001,the value can be one of below:
			-\WRITE_READ_FLASH_TIMEOUT
			-\TEMPLATE_INDEX_OVER
			-\WRITE_READ_FLASH_OK
			-\HS_HAL_BUSY  
  */
uint8_t IrisGetTemplate(uint32_t index)
{
	if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		DSP_RX_TMPL_INDEX = index;//设置编码索引
		DSP_RX_TMPL_INDEX &=~(1<<16);//select template BRAM A
		DSP_CMD |= 0x19;//从FLASH取出模板
		if(DSP_ERR_STATUS&(1<<2))//判断索引是否溢出
		{
			return TEMPLATE_INDEX_OVER;	
		}
		while(!(DSP_CMD_STATUS&(1<<8)))//等待模板写入完成
		{
			if(DSP_ERR_STATUS&0x01)//判断读写FLASH是否超时
			{
				return WRITE_READ_FLASH_TIMEOUT;
			}
		}
		return WRITE_READ_FLASH_OK;
	}else{
		
		return HS_HAL_BUSY;		
	}		
}

/**
  * @brief  Send encode command to the QX8001 and start match.
  * @param  eye:indicate which mode to match ,the value can be one of below:
            -\NormalMode
			-\DownloadMode
  * @retval  return value from QX8001,the value can be one of below:
			-\MATCH_TIMEOUT
			-\MATCH_ERROR
			-\MATCH_OK
			-\HS_HAL_BUSY 	
  */
uint8_t IrisMatch(TempMatchMode mode)
{
	//while(!SensorReady);
	if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		if(mode==NormalMode)
		{
			DSP_TMPL_MATCH_CTRL |= 0x01;
			DSP_TMPL_MATCH_CTRL &=~ (1<<1);
		}else{
			DSP_TMPL_MATCH_CTRL &=~ 0x01;
			DSP_TMPL_MATCH_CTRL |= (1<<1);
		}	
		DSP_CMD |= 0x0D;//开始比对
		while(!(DSP_CMD_STATUS&(1<<5)))//等待比对成功
		{
			if(DSP_ERR_STATUS&(1<<4))//判断比对是否超时
			{

				return MATCH_TIMEOUT;
			}
			else if(DSP_CMD_STATUS&(1<<6))//判断是否比对错误
			{
				return MATCH_ERROR;
			}
		}

		return MATCH_OK;
		
	}else{
		
		return HS_HAL_BUSY;		
	}	
}

/**
  * @brief  Send eraser one template to the QX8001 and start eraser one template.
  * @param  template index value(0~255).
  * @param  template delete level,the value can be one of below:
			-\DeleteOnlyIndex
			-\DeleteIndexAndData
  * @retval return value from QX8001,the value can be one of below:
			-\WRITE_READ_FLASH_TIMEOUT
			-\TEMPLATE_INDEX_OVER
			-\WRITE_READ_FLASH_MATCH_ERROR
			-\ERASER_ONE_TEMP_OK
			-\HS_HAL_BUSY  
  */
uint8_t IrisEraseOneTemp(uint16_t index,HS_DELETE_LEVEL delLevel)
{
    if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		if(delLevel == DeleteOnlyIndex)
		{
			DSP_RX_CTRL &=~ 0x01;//仅擦除标志，保留数据
		}else{
			DSP_RX_CTRL |= 0x01;//删除/擦除模板时，同时擦除标志和数据
		}
		DSP_RX_TMPL_INDEX = index;//设置删除索引
		
		if(DSP_ERR_STATUS&(1<<2))//判断索引是否溢出
		{
			return TEMPLATE_INDEX_OVER;	
		}
		//DSP_CMD |= 0x08;//将模板写入到FLASH
		DSP_CMD |= 0x0E;//删除指定模板
		while(!(DSP_CMD_STATUS&(1<<7)))//等待模板删除完成
		{
			if(DSP_ERR_STATUS&0x01)//判断是否读写FLASH超时
			{
				return WRITE_READ_FLASH_TIMEOUT;
			}
		}
		if(DSP_ERR_STATUS&(1<<1))//判断是否读写FLASH错误
		{
			return WRITE_READ_FLASH_MATCH_ERROR;
		}
		return ERASER_ONE_TEMP_OK;
		
	}else{	
		
		return HS_HAL_BUSY;
	}
}

/**
  * @brief  Send eraser all template command to the QX8001 and start eraser all template.
  * @param  template delete level,the value can be one of below:
			-\DeleteOnlyIndex
			-\DeleteIndexAndData
  * @retval 0 if operation is correctly performed, else return value 
			-\WRITE_READ_FLASH_TIMEOUT
			-\TEMPLATE_INDEX_OVER
			-\WRITE_READ_FLASH_MATCH_ERROR
			-\ERASER_ALL_TEMP_OK
			-\HS_HAL_BUSY  
  */
uint8_t IrisEraseAllTemp(HS_DELETE_LEVEL delLevel)
{
    if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		if(delLevel == DeleteOnlyIndex)
		{
			DSP_RX_CTRL &=~ 0x01;//仅擦除标志，保留数据
		}else{
			DSP_RX_CTRL |= 0x01;//删除/擦除模板时，同时擦除标志和数据
		}

		DSP_CMD |= 0x0B;//删除全部模板

		while(!(DSP_CMD_STATUS&(1<<7)))//等待模板删除完成
		{
			if(DSP_ERR_STATUS&0x01)//判断是否读写FLASH超时
			{
				return WRITE_READ_FLASH_TIMEOUT;
			}
		}
		if(DSP_ERR_STATUS&(1<<1))//判断是否读写FLASH错误
		{
			return WRITE_READ_FLASH_MATCH_ERROR;
		}
		return ERASER_ALL_TEMP_OK;
		
	}else{	
		
		return HS_HAL_BUSY;
	}
}

/**
  * @brief  Write template data to the QX8001 template ram.
  * @param  buff : pointer to the buffer containing the template data to be written to 
  *         the QX8001.
  * @retval none
  */
void IrisDownloadTemp(uint8_t *buff,uint16_t packLengh ,uint16_t packNum,RamType ram)
{
	uint32_t i;
	if(ram== BRAM_A){
		for(i=0;i<packLengh/4;i++)
		{
			*((volatile uint32_t*)(0x30090000+4*i+packNum*packLengh))=(buff[4*i+3]<<24)|(buff[4*i+2]<<16)|(buff[4*i+1]<<8)|(buff[4*i+0]);
		}	
	}else{
		for(i=0;i<packLengh/4;i++)
		{
			*((volatile uint32_t*)(0x30092000+4*i+packNum*packLengh))=(buff[4*i+3]<<24)|(buff[4*i+2]<<16)|(buff[4*i+1]<<8)|(buff[4*i+0]);
		}	
	}		
}

/**
  * @brief  Get template data to the QX8001 template ram.
  * @param  buff : pointer to the buffer containing the image data to be written to 
  *         the QX8001.
  * @param  packLengh : data length of the buffer containing the template data to be read from 
  *         the QX8001.
  * @retval none
  */
void IrisUploadTemp(uint8_t *buff,uint16_t packLengh ,uint16_t packNum,RamType ram)
{
	uint32_t i,TempData;
	if(ram== BRAM_A){
		for(i=0;i<packLengh/4;i++)
		{
			TempData = *((volatile uint32_t*)(0x30090000+4*i+packNum*packLengh));							
			buff[0+4*i]=TempData;
			buff[1+4*i]=(uint8_t)(TempData>>8);
			buff[2+4*i]=(uint8_t)(TempData>>16);
			buff[3+4*i]=(uint8_t)(TempData>>24);
		}	
	}else{
		for(i=0;i<packLengh/4;i++)
		{
			TempData = *((volatile uint32_t*)(0x30092000+4*i+packNum*packLengh));							
			buff[0+4*i]=TempData;
			buff[1+4*i]=(uint8_t)(TempData>>8);
			buff[2+4*i]=(uint8_t)(TempData>>16);
			buff[3+4*i]=(uint8_t)(TempData>>24);
		}	
	}
}

/**
  * @brief  Write image data to the QX8001 image ram.
  * @param  buff : pointer to the buffer containing the image data to be written to 
  *         the QX8001.
  * @param  packLengh : data length of the buffer containing the image data to be written to 
  *         the QX8001.
  * @retval none
  */
void IrisDownloadImag(uint8_t *buff,uint16_t packLengh ,uint16_t packNum)
{
	uint32_t i;
	for(i=0;i<packLengh/4;i++)
	{
		*((volatile uint32_t*)(0x30000000+4*i+packNum*packLengh))=(buff[4*i+3]<<24)|(buff[4*i+2]<<16)|(buff[4*i+1]<<8)|(buff[4*i+0]);
	}		
}

/**
  * @brief  Get image data to the QX8001 image ram.
  * @param  buff : pointer to the buffer containing the image data to be written to 
  *         the QX8001.
  * @param  packLengh : data length of the buffer containing the image data to be read from 
  *         the QX8001.
  * @retval none
  */
void IrisUploadImag(uint8_t *buff,uint16_t packLengh ,uint16_t packNum)
{
	uint32_t i,TempData;
	for(i=0;i<packLengh/4;i++)
	{
		TempData = *((volatile uint32_t*)(0x30000000+4*i+packNum*packLengh));							
		buff[0+4*i]=TempData;
		buff[1+4*i]=(uint8_t)(TempData>>8);
		buff[2+4*i]=(uint8_t)(TempData>>16);
		buff[3+4*i]=(uint8_t)(TempData>>24);
	}	
}


/**
  * @brief  This function handles DSP1 exception.
  * @param  None
  * @retval None
  */
void DSP1_IRQHandler(void)
{

	delay(10000);
	DSP_CMD |= 0x10000;
}
