#include "i2c1_driver.h"
#include "gpio.h"
#include "cfg.h"
#include "dsp_cfg.h"  
#include "sys.h"

	
#define TIME_MAX              0x400
#define TIME_MIN              0x40
#define CARSE_TIME            0x220

/**
  * @brief  initial sensor ar0237.
  * @param  none
  *         
  * @retval none
  */

void ar0237_init(void)
{
	ISP_GAIN_CTRL = 0x04;

	//ISP_RX_TOTAL_NUM = 0x01000010;

	//ISP_RX_TH_MIN = 0x030f03ff;
	
	//ISP_RX_TH_MID = 0x01000010;

	//ISP_RX_TH_MAX = 0x030f03ff;
	
	GPIO0_CTRL = 0x00000001;//enable gpio0 block clock
	
	rGPIODIR |= (1<<0)|(1<<1);//设置pin1和pin2为输出
	
	rGPIO1DATA &=~ (1<<1); //设置stanby为低；
	
	rGPIO0DATA |= (1<<0);
		
	rGPIO0DATA &=~ (1<<0);//reset

	delay(1000*1000);
	
	rGPIO0DATA |= (1<<0);
	
	delay(400000);
	
		
	i2c1_wr_data(0x301A,0x0001);
	
	delay(100*1000);
		
	i2c1_wr_data(0x301A,0x10D8);
				
	i2c1_wr_data(0x3088, 0x8000);		
	i2c1_wr_data(0x3086, 0x4558);			
	i2c1_wr_data(0x3086, 0x72a6);
	i2c1_wr_data(0x3086, 0x4A31);
	
	i2c1_wr_data(0x3086, 0x4342);
	i2c1_wr_data(0x3086, 0x8E03);
	i2c1_wr_data(0x3086, 0x2a14);
	i2c1_wr_data(0x3086, 0x4578);
	i2c1_wr_data(0x3086, 0x7B3D);
	i2c1_wr_data(0x3086, 0xFF3D);
	i2c1_wr_data(0x3086, 0xFF3D);
	i2c1_wr_data(0x3086, 0xEA2a);
	i2c1_wr_data(0x3086, 0x043D);
	i2c1_wr_data(0x3086, 0x102a);
	i2c1_wr_data(0x3086, 0x052a);
	i2c1_wr_data(0x3086, 0x1535);
	i2c1_wr_data(0x3086, 0x2a05);
	i2c1_wr_data(0x3086, 0x3D10);
	i2c1_wr_data(0x3086, 0x4558);
	i2c1_wr_data(0x3086, 0x2a04);
	i2c1_wr_data(0x3086, 0x2a14);
	i2c1_wr_data(0x3086, 0x3DFF);
	i2c1_wr_data(0x3086, 0x3DFF);
	i2c1_wr_data(0x3086, 0x3DEA);
	i2c1_wr_data(0x3086, 0x2a04);
	i2c1_wr_data(0x3086, 0x622a);
	i2c1_wr_data(0x3086, 0x288E);
	i2c1_wr_data(0x3086, 0x0036);
	i2c1_wr_data(0x3086, 0x2a08);
	i2c1_wr_data(0x3086, 0x3D64);
	i2c1_wr_data(0x3086, 0x7A3D);
	i2c1_wr_data(0x3086, 0x0444);
	i2c1_wr_data(0x3086, 0x2C4B);
	i2c1_wr_data(0x3086, 0xa403);
	i2c1_wr_data(0x3086, 0x430d);
	i2c1_wr_data(0x3086, 0x2d46);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x2a90);
	i2c1_wr_data(0x3086, 0x3e06);
	i2c1_wr_data(0x3086, 0x2a98);
	i2c1_wr_data(0x3086, 0x5f16);
	i2c1_wr_data(0x3086, 0x530d);
	i2c1_wr_data(0x3086, 0x1660);
	i2c1_wr_data(0x3086, 0x3e4c);
	i2c1_wr_data(0x3086, 0x2904);
	i2c1_wr_data(0x3086, 0x2984);
	i2c1_wr_data(0x3086, 0x8e03);
	i2c1_wr_data(0x3086, 0x2afc);
	i2c1_wr_data(0x3086, 0x5c1d);
	i2c1_wr_data(0x3086, 0x5754);
	i2c1_wr_data(0x3086, 0x495f);
	i2c1_wr_data(0x3086, 0x5305);
	i2c1_wr_data(0x3086, 0x5307);
	i2c1_wr_data(0x3086, 0x4d2b);
	i2c1_wr_data(0x3086, 0xf810);
	i2c1_wr_data(0x3086, 0x164c);
	i2c1_wr_data(0x3086, 0x0955);
	i2c1_wr_data(0x3086, 0x562b);
	i2c1_wr_data(0x3086, 0xb82b);
	i2c1_wr_data(0x3086, 0x984e);
	i2c1_wr_data(0x3086, 0x1129);
	i2c1_wr_data(0x3086, 0x9460);
	i2c1_wr_data(0x3086, 0x5c19);
	i2c1_wr_data(0x3086, 0x5c1b);
	i2c1_wr_data(0x3086, 0x4548);
	i2c1_wr_data(0x3086, 0x4508);
	i2c1_wr_data(0x3086, 0x4588);
	i2c1_wr_data(0x3086, 0x29b6);
	i2c1_wr_data(0x3086, 0x8e01);
	i2c1_wr_data(0x3086, 0x2af8);
	i2c1_wr_data(0x3086, 0x3e02);
	i2c1_wr_data(0x3086, 0x2afa);
	i2c1_wr_data(0x3086, 0x3f09);
	i2c1_wr_data(0x3086, 0x5c1b);
	i2c1_wr_data(0x3086, 0x29b2);
	i2c1_wr_data(0x3086, 0x3f0c);
	i2c1_wr_data(0x3086, 0x3e03);
	i2c1_wr_data(0x3086, 0x3e15);
	i2c1_wr_data(0x3086, 0x5c13);
	i2c1_wr_data(0x3086, 0x3f11);
	i2c1_wr_data(0x3086, 0x3e0f);
	i2c1_wr_data(0x3086, 0x5f2b);
	i2c1_wr_data(0x3086, 0x902b);
	i2c1_wr_data(0x3086, 0x803e);
	i2c1_wr_data(0x3086, 0x062a);
	i2c1_wr_data(0x3086, 0xf23f);
	i2c1_wr_data(0x3086, 0x103e);
	i2c1_wr_data(0x3086, 0x0160);
	i2c1_wr_data(0x3086, 0x29a2);
	i2c1_wr_data(0x3086, 0x29a3);
	i2c1_wr_data(0x3086, 0x5f4d);
	i2c1_wr_data(0x3086, 0x1c2a);
	i2c1_wr_data(0x3086, 0xfa29);
	i2c1_wr_data(0x3086, 0x8345);
	i2c1_wr_data(0x3086, 0xa83e);
	i2c1_wr_data(0x3086, 0x072a);
	i2c1_wr_data(0x3086, 0xfb3e);
	i2c1_wr_data(0x3086, 0x2945);
	i2c1_wr_data(0x3086, 0x8824);
	i2c1_wr_data(0x3086, 0x3e08);
	i2c1_wr_data(0x3086, 0x2afa);
	i2c1_wr_data(0x3086, 0x5d29);
	i2c1_wr_data(0x3086, 0x9288);
	i2c1_wr_data(0x3086, 0x102b);
	i2c1_wr_data(0x3086, 0x048b);
	i2c1_wr_data(0x3086, 0x1686);
	i2c1_wr_data(0x3086, 0x8d48);
	i2c1_wr_data(0x3086, 0x4d4e);
	i2c1_wr_data(0x3086, 0x2b80);
	i2c1_wr_data(0x3086, 0x4c0b);
	i2c1_wr_data(0x3086, 0x3f36);
	i2c1_wr_data(0x3086, 0x2af2);
	i2c1_wr_data(0x3086, 0x3f10);
	i2c1_wr_data(0x3086, 0x3e01);
	i2c1_wr_data(0x3086, 0x6029);
	i2c1_wr_data(0x3086, 0x8229);
	i2c1_wr_data(0x3086, 0x8329);
	i2c1_wr_data(0x3086, 0x435c);
	i2c1_wr_data(0x3086, 0x155f);
	i2c1_wr_data(0x3086, 0x4d1c);
	i2c1_wr_data(0x3086, 0x2afa);
	i2c1_wr_data(0x3086, 0x4558);
	i2c1_wr_data(0x3086, 0x8e00);
	i2c1_wr_data(0x3086, 0x2a98);
	i2c1_wr_data(0x3086, 0x3f0a);
	i2c1_wr_data(0x3086, 0x4a0a);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x0b43);
	i2c1_wr_data(0x3086, 0x168e);
	i2c1_wr_data(0x3086, 0x032a);
	i2c1_wr_data(0x3086, 0x9c45);
	i2c1_wr_data(0x3086, 0x783f);
	i2c1_wr_data(0x3086, 0x072a);
	i2c1_wr_data(0x3086, 0x9d3e);
	i2c1_wr_data(0x3086, 0x305d);
	i2c1_wr_data(0x3086, 0x2944);
	i2c1_wr_data(0x3086, 0x8810);
	i2c1_wr_data(0x3086, 0x2b04);
	i2c1_wr_data(0x3086, 0x530d);
	i2c1_wr_data(0x3086, 0x4558);
	i2c1_wr_data(0x3086, 0x3e08);
	i2c1_wr_data(0x3086, 0x8e01);
	i2c1_wr_data(0x3086, 0x2a98);
	i2c1_wr_data(0x3086, 0x8e00);
	i2c1_wr_data(0x3086, 0x76a7);
	i2c1_wr_data(0x3086, 0x77a7);
	i2c1_wr_data(0x3086, 0x4644);
	i2c1_wr_data(0x3086, 0x1616);
	i2c1_wr_data(0x3086, 0xa57a);
	i2c1_wr_data(0x3086, 0x1244);
	i2c1_wr_data(0x3086, 0x4b18);
	i2c1_wr_data(0x3086, 0x4a04);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x0643);
	i2c1_wr_data(0x3086, 0x1605);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x0743);
	i2c1_wr_data(0x3086, 0x1658);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x5a43);
	i2c1_wr_data(0x3086, 0x1645);
	i2c1_wr_data(0x3086, 0x588e);
	i2c1_wr_data(0x3086, 0x032a);
	i2c1_wr_data(0x3086, 0x9c45);
	i2c1_wr_data(0x3086, 0x787b);
	i2c1_wr_data(0x3086, 0x3f07);
	i2c1_wr_data(0x3086, 0x2a9d);
	i2c1_wr_data(0x3086, 0x630d);
	i2c1_wr_data(0x3086, 0x8b16);
	i2c1_wr_data(0x3086, 0x863e);
	i2c1_wr_data(0x3086, 0x2345);
	i2c1_wr_data(0x3086, 0x5825);
	i2c1_wr_data(0x3086, 0x3e10);
	i2c1_wr_data(0x3086, 0x8e01);
	i2c1_wr_data(0x3086, 0x2a98);
	i2c1_wr_data(0x3086, 0x8e00);
	i2c1_wr_data(0x3086, 0x3e10);
	i2c1_wr_data(0x3086, 0x8d60);
	i2c1_wr_data(0x3086, 0x1244);
	i2c1_wr_data(0x3086, 0x4bb9);
	i2c1_wr_data(0x3086, 0x2c2c);
	i2c1_wr_data(0x3086, 0x2c2c);
		
	i2c1_wr_data(0x30f0, 0x1283);
	i2c1_wr_data(0x3064, 0x1802);
	i2c1_wr_data(0x3eee, 0xa0aa);
	i2c1_wr_data(0x30ba, 0x762c);
	i2c1_wr_data(0x3fa4, 0x0f70);
	i2c1_wr_data(0x309e, 0x016a);
	i2c1_wr_data(0x3096, 0xf880);
	i2c1_wr_data(0x3f32, 0xf880);
	i2c1_wr_data(0x3092, 0x006f);
	i2c1_wr_data(0x301a, 0x10d8);
	i2c1_wr_data(0x30b0, 0x1118);
	i2c1_wr_data(0x31ac, 0x0c0c);
		
	i2c1_wr_data(0x302a, 0x0008);
	i2c1_wr_data(0x302c, 0x0001);
	i2c1_wr_data(0x302e, 0x0002);
	i2c1_wr_data(0x3030, 0x002c);
	i2c1_wr_data(0x3036, 0x000c);
	i2c1_wr_data(0x3038, 0x0001);
	i2c1_wr_data(0x3002, 0x0000);
	i2c1_wr_data(0x3004, 0x0000);
	i2c1_wr_data(0x3006, 0x0437);
	i2c1_wr_data(0x3008, 0x077f);
	i2c1_wr_data(0x300a, 0x0465);
	i2c1_wr_data(0x300c, 0x044c);
	i2c1_wr_data(0x3012, 0x0416);
	
	i2c1_wr_data(0x30a2, 0x0001);
	i2c1_wr_data(0x30a6, 0x0001);
	i2c1_wr_data(0x30ae, 0x0001);
	i2c1_wr_data(0x30a8, 0x0001);
	
//	i2c1_wr_data(0x3040, 0x0000);
i2c1_wr_data(0x3040, 0x4000);	//zxb fix: mirror
//i2c1_wr_data(0x3040, 0x8000);
	i2c1_wr_data(0x31ae, 0x0301);
	i2c1_wr_data(0x3082, 0x0009);
	i2c1_wr_data(0x30ba, 0x762c);
	i2c1_wr_data(0x3096, 0x0080);
	i2c1_wr_data(0x3098, 0x0080);
	i2c1_wr_data(0x3060, 0x0004);
	i2c1_wr_data(0x3100, 0x0004);
	i2c1_wr_data(0x31d0, 0x0000);
	i2c1_wr_data(0x3064, 0x1982);
	i2c1_wr_data(0x301a, 0x10dc);
	
	delay(33*1000);
		
}


