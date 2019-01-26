#ifndef _HS_DSP_H_
#define _HS_DSP_H_
#include <stdint.h>
#include "dsp_cfg.h"

#define DSP_READY              0x0001
#define ENCODE                 0x0101
#define MATCH                  0x0102
#define ERASER_ONE_TEMP        0x0103
#define ERASER_ALL_TEMP        0x0104
#define SAVE_TEMPLATE          0x0105
#define DOWNLOAD_TEMPLATE      0x0201
#define UPLOAD_TEMPLATE        0x0202
#define DOWNLOAD_IMAG_PIC      0x0301
#define UPLOAD_IMAG_PIC        0x0302
#define GPIO_OUTPUT            0x0401
#define GPIO_INPUT             0x0402
#define CHANGE_SPI_MODE        0x0501
#define CHANGE_NORMAL_MODE     0x0502
#define CRC8_ERROR             0xffff
#define WRITE_REG              0x0501
#define READ_REG               0x0502
#define WRITE_BULK_REG         0x0503
#define READ_BULK_REG          0x0504
#define MODIFY_SENSOR          0x0506
#define READ_SENSOR            0x0505
#define SET_UART               0x0601

void DspConfig(void);
extern uint8_t IrisEncoded(EyeType eye,EncodeQuaulityLevel level);
extern uint8_t IrisSaveTemplate(uint32_t index);
extern uint8_t IrisMatch(TempMatchMode mode);
extern uint8_t IrisEraseOneTemp(uint16_t index,HS_DELETE_LEVEL delLevel);
extern uint8_t IrisEraseAllTemp(HS_DELETE_LEVEL delLevel);
extern void IrisDownloadTemp(uint8_t *buff,uint16_t packLengh ,uint16_t packNum,RamType ram);
extern void IrisUploadTemp(uint8_t *buff,uint16_t packLengh ,uint16_t packNum,RamType ram);
extern void IrisDownloadImag(uint8_t *buff,uint16_t packLengh ,uint16_t packNum);
extern void IrisUploadImag(uint8_t *buff,uint16_t packLengh ,uint16_t packNum);


#endif
