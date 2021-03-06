#include "i2c1_driver.h"
#include "gpio.h"
#include "cfg.h"
#include "dsp_cfg.h"  

	
#define TIME_MAX              0x400
#define TIME_MIN              0x40
#define CARSE_TIME            0x220



void af0140_init(void)
{
	ISP_GAIN_CTRL = 0x04;

	ISP_RX_TOTAL_NUM = 0x01000010;

	ISP_RX_TH_MIN = 0x030f03ff;
	
	ISP_RX_TH_MID = 0x01000010;

	ISP_RX_TH_MAX = 0x030f03ff;
	
	GPIO0_CTRL = 0x00000001;//enable gpio0 block clock
	
	//rGPIODIR |= (1<<1)|(1<<2);//设置pin1和pin2为输出
	
	rGPIO2DATA &=~ (1<<2); //设置stanby为低；
	
	rGPIO1DATA |= (1<<1);
		
	rGPIO1DATA &=~ (1<<1);//reset

	delay(1000*1000);
	
	rGPIO1DATA |= (1<<1);
	
	delay(400);
	
		
	i2c1_wr_data(0x301A,0x0001);
		
	i2c1_wr_data(0x301A,0x10D8);
				
	i2c1_wr_data(0x3088, 0x8000);		
	i2c1_wr_data(0x3086, 0x4558);			
	i2c1_wr_data(0x3086, 0x6E9B);
	i2c1_wr_data(0x3086, 0x4A31);
	i2c1_wr_data(0x3086, 0x4342);
	i2c1_wr_data(0x3086, 0x8E03);
	i2c1_wr_data(0x3086, 0x2714);
	i2c1_wr_data(0x3086, 0x4578);
	i2c1_wr_data(0x3086, 0x7B3D);
	i2c1_wr_data(0x3086, 0xFF3D);
	i2c1_wr_data(0x3086, 0xFF3D);
	i2c1_wr_data(0x3086, 0xEA27);
	i2c1_wr_data(0x3086, 0x043D);
	i2c1_wr_data(0x3086, 0x1027);
	i2c1_wr_data(0x3086, 0x0527);
	i2c1_wr_data(0x3086, 0x1535);
	i2c1_wr_data(0x3086, 0x2705);
	i2c1_wr_data(0x3086, 0x3D10);
	i2c1_wr_data(0x3086, 0x4558);
	i2c1_wr_data(0x3086, 0x2704);
	i2c1_wr_data(0x3086, 0x2714);
	i2c1_wr_data(0x3086, 0x3DFF);
	i2c1_wr_data(0x3086, 0x3DFF);
	i2c1_wr_data(0x3086, 0x3DEA);
	i2c1_wr_data(0x3086, 0x2704);
	i2c1_wr_data(0x3086, 0x6227);
	i2c1_wr_data(0x3086, 0x288E);
	i2c1_wr_data(0x3086, 0x0036);
	i2c1_wr_data(0x3086, 0x2708);
	i2c1_wr_data(0x3086, 0x3D64);
	i2c1_wr_data(0x3086, 0x7A3D);
	i2c1_wr_data(0x3086, 0x0444);
	i2c1_wr_data(0x3086, 0x2C4B);
	i2c1_wr_data(0x3086, 0x8F01);
	i2c1_wr_data(0x3086, 0x4372);
	i2c1_wr_data(0x3086, 0x719F);
	i2c1_wr_data(0x3086, 0x4643);
	i2c1_wr_data(0x3086, 0x166F);
	i2c1_wr_data(0x3086, 0x9F92);
	i2c1_wr_data(0x3086, 0x1244);
	i2c1_wr_data(0x3086, 0x1646);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x9326);
	i2c1_wr_data(0x3086, 0x0426);
	i2c1_wr_data(0x3086, 0x848E);
	i2c1_wr_data(0x3086, 0x0327);
	i2c1_wr_data(0x3086, 0xFC5C);
	i2c1_wr_data(0x3086, 0x0D57);
	i2c1_wr_data(0x3086, 0x5417);
	i2c1_wr_data(0x3086, 0x0955);
	i2c1_wr_data(0x3086, 0x5649);
	i2c1_wr_data(0x3086, 0x5F53);
	i2c1_wr_data(0x3086, 0x0553);
	i2c1_wr_data(0x3086, 0x0728);
	i2c1_wr_data(0x3086, 0x6C4C);
	i2c1_wr_data(0x3086, 0x0928);
	i2c1_wr_data(0x3086, 0x2C72);
	i2c1_wr_data(0x3086, 0xA37C);
	i2c1_wr_data(0x3086, 0x9728);
	i2c1_wr_data(0x3086, 0xA879);
	i2c1_wr_data(0x3086, 0x6026);
	i2c1_wr_data(0x3086, 0x9C5C);
	i2c1_wr_data(0x3086, 0x1B45);
	i2c1_wr_data(0x3086, 0x4845);
	i2c1_wr_data(0x3086, 0x0845);
	i2c1_wr_data(0x3086, 0x8826);
	i2c1_wr_data(0x3086, 0xBE8E);
	i2c1_wr_data(0x3086, 0x0127);
	i2c1_wr_data(0x3086, 0xF817);
	i2c1_wr_data(0x3086, 0x0227);
	i2c1_wr_data(0x3086, 0xFA17);
	i2c1_wr_data(0x3086, 0x095C);
	i2c1_wr_data(0x3086, 0x0B17);
	i2c1_wr_data(0x3086, 0x1026);
	i2c1_wr_data(0x3086, 0xBA5C);
	i2c1_wr_data(0x3086, 0x0317);
	i2c1_wr_data(0x3086, 0x1026);
	i2c1_wr_data(0x3086, 0xB217);
	i2c1_wr_data(0x3086, 0x065F);
	i2c1_wr_data(0x3086, 0x2888);
	i2c1_wr_data(0x3086, 0x9060);
	i2c1_wr_data(0x3086, 0x27F2);
	i2c1_wr_data(0x3086, 0x1710);
	i2c1_wr_data(0x3086, 0x26A2);
	i2c1_wr_data(0x3086, 0x26A3);
	i2c1_wr_data(0x3086, 0x5F4D);
	i2c1_wr_data(0x3086, 0x2808);
	i2c1_wr_data(0x3086, 0x1A27);
	i2c1_wr_data(0x3086, 0xFA84);
	i2c1_wr_data(0x3086, 0x69A0);
	i2c1_wr_data(0x3086, 0x785D);
	i2c1_wr_data(0x3086, 0x2888);
	i2c1_wr_data(0x3086, 0x8710);
	i2c1_wr_data(0x3086, 0x8C82);
	i2c1_wr_data(0x3086, 0x8926);
	i2c1_wr_data(0x3086, 0xB217);
	i2c1_wr_data(0x3086, 0x036B);
	i2c1_wr_data(0x3086, 0x9C60);
	i2c1_wr_data(0x3086, 0x9417);
	i2c1_wr_data(0x3086, 0x2926);
	i2c1_wr_data(0x3086, 0x8345);
	i2c1_wr_data(0x3086, 0xA817);
	i2c1_wr_data(0x3086, 0x0727);
	i2c1_wr_data(0x3086, 0xFB17);
	i2c1_wr_data(0x3086, 0x2945);
	i2c1_wr_data(0x3086, 0x8820);
	i2c1_wr_data(0x3086, 0x1708);
	i2c1_wr_data(0x3086, 0x27FA);
	i2c1_wr_data(0x3086, 0x5D87);
	i2c1_wr_data(0x3086, 0x108C);
	i2c1_wr_data(0x3086, 0x8289);
	i2c1_wr_data(0x3086, 0x170E);
	i2c1_wr_data(0x3086, 0x4826);
	i2c1_wr_data(0x3086, 0x9A28);
	i2c1_wr_data(0x3086, 0x884C);
	i2c1_wr_data(0x3086, 0x0B79);
	i2c1_wr_data(0x3086, 0x1730);
	i2c1_wr_data(0x3086, 0x2692);
	i2c1_wr_data(0x3086, 0x1709);
	i2c1_wr_data(0x3086, 0x9160);
	i2c1_wr_data(0x3086, 0x27F2);
	i2c1_wr_data(0x3086, 0x1710);
	i2c1_wr_data(0x3086, 0x2682);
	i2c1_wr_data(0x3086, 0x2683);
	i2c1_wr_data(0x3086, 0x5F4D);
	i2c1_wr_data(0x3086, 0x2808);
	i2c1_wr_data(0x3086, 0x1A27);
	i2c1_wr_data(0x3086, 0xFA84);
	i2c1_wr_data(0x3086, 0x69A1);
	i2c1_wr_data(0x3086, 0x785D);
	i2c1_wr_data(0x3086, 0x2888);
	i2c1_wr_data(0x3086, 0x8710);
	i2c1_wr_data(0x3086, 0x8C80);
	i2c1_wr_data(0x3086, 0x8A26);
	i2c1_wr_data(0x3086, 0x9217);
	i2c1_wr_data(0x3086, 0x036B);
	i2c1_wr_data(0x3086, 0x9D95);
	i2c1_wr_data(0x3086, 0x2603);
	i2c1_wr_data(0x3086, 0x5C01);
	i2c1_wr_data(0x3086, 0x4558);
	i2c1_wr_data(0x3086, 0x8E00);
	i2c1_wr_data(0x3086, 0x2798);
	i2c1_wr_data(0x3086, 0x170A);
	i2c1_wr_data(0x3086, 0x4A0A);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x0B43);
	i2c1_wr_data(0x3086, 0x5B43);
	i2c1_wr_data(0x3086, 0x1659);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x8E03);
	i2c1_wr_data(0x3086, 0x279C);
	i2c1_wr_data(0x3086, 0x4578);
	i2c1_wr_data(0x3086, 0x1707);
	i2c1_wr_data(0x3086, 0x279D);
	i2c1_wr_data(0x3086, 0x1722);
	i2c1_wr_data(0x3086, 0x5D87);
	i2c1_wr_data(0x3086, 0x1028);
	i2c1_wr_data(0x3086, 0x0853);
	i2c1_wr_data(0x3086, 0x0D8C);
	i2c1_wr_data(0x3086, 0x808A);
	i2c1_wr_data(0x3086, 0x4558);
	i2c1_wr_data(0x3086, 0x1708);
	i2c1_wr_data(0x3086, 0x8E01);
	i2c1_wr_data(0x3086, 0x2798);
	i2c1_wr_data(0x3086, 0x8E00);
	i2c1_wr_data(0x3086, 0x76A2);
	i2c1_wr_data(0x3086, 0x77A2);
	i2c1_wr_data(0x3086, 0x4644);
	i2c1_wr_data(0x3086, 0x1616);
	i2c1_wr_data(0x3086, 0x967A);
	i2c1_wr_data(0x3086, 0x2644);
	i2c1_wr_data(0x3086, 0x5C05);
	i2c1_wr_data(0x3086, 0x1244);
	i2c1_wr_data(0x3086, 0x4B71);
	i2c1_wr_data(0x3086, 0x759E);
	i2c1_wr_data(0x3086, 0x8B86);
	i2c1_wr_data(0x3086, 0x184A);
	i2c1_wr_data(0x3086, 0x0343);
	i2c1_wr_data(0x3086, 0x1606);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x0743);
	i2c1_wr_data(0x3086, 0x1604);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x5843);
	i2c1_wr_data(0x3086, 0x165A);
	i2c1_wr_data(0x3086, 0x4316);
	i2c1_wr_data(0x3086, 0x4558);
	i2c1_wr_data(0x3086, 0x8E03);
	i2c1_wr_data(0x3086, 0x279C);
	i2c1_wr_data(0x3086, 0x4578);
	i2c1_wr_data(0x3086, 0x7B17);
	i2c1_wr_data(0x3086, 0x0727);
	i2c1_wr_data(0x3086, 0x9D17);
	i2c1_wr_data(0x3086, 0x2245);
	i2c1_wr_data(0x3086, 0x5822);
	i2c1_wr_data(0x3086, 0x1710);
	i2c1_wr_data(0x3086, 0x8E01);
	i2c1_wr_data(0x3086, 0x2798);
	i2c1_wr_data(0x3086, 0x8E00);
	i2c1_wr_data(0x3086, 0x1710);
	i2c1_wr_data(0x3086, 0x1244);
	i2c1_wr_data(0x3086, 0x4B8D);
	i2c1_wr_data(0x3086, 0x602C);
	i2c1_wr_data(0x3086, 0x2C2C);
	i2c1_wr_data(0x3086, 0x2C00);
	i2c1_wr_data(0x302A, 0x0008);
	i2c1_wr_data(0x302C, 0x0001);
	i2c1_wr_data(0x302E, 0x0008);
	i2c1_wr_data(0x3030, 0x0042);
	i2c1_wr_data(0x3036, 0x000C);
	i2c1_wr_data(0x3038, 0x0001);
	i2c1_wr_data(0x3002, 0x001C);
	i2c1_wr_data(0x3004, 0x0016);
	i2c1_wr_data(0x3006, 0x033B);
	i2c1_wr_data(0x3008, 0x0515);
	i2c1_wr_data(0x300A, 0x0336);
	i2c1_wr_data(0x300C, 0x0672);
	i2c1_wr_data(0x3012, 0x002D);
	i2c1_wr_data(0x3060, 0x0010);
	i2c1_wr_data(0x30A2, 0x0001);
	i2c1_wr_data(0x30A6, 0x0001);
	i2c1_wr_data(0x3040, 0xC000);
	i2c1_wr_data(0x3044, 0x0400);
	i2c1_wr_data(0x3052, 0xA124);
	i2c1_wr_data(0x3092, 0x010F);
	i2c1_wr_data(0x30FE, 0x0080);
	i2c1_wr_data(0x3ECE, 0x40FF);
	i2c1_wr_data(0x3ED0, 0xFF40);
	i2c1_wr_data(0x3ED2, 0xA906);
	i2c1_wr_data(0x3ED4, 0x001F);
	i2c1_wr_data(0x3ED6, 0x638F);
	i2c1_wr_data(0x3ED8, 0xCC99);
	i2c1_wr_data(0x3EDA, 0x0888);
	i2c1_wr_data(0x3EDE, 0x8878);
	i2c1_wr_data(0x3EE0, 0x7744);
	i2c1_wr_data(0x3EE2, 0x4463);
	i2c1_wr_data(0x3EE4, 0xAAE0);
	i2c1_wr_data(0x3EE6, 0x1400);
	i2c1_wr_data(0x3EEA, 0xA4FF);
	i2c1_wr_data(0x3EEC, 0x80F0);
	i2c1_wr_data(0x3EEE, 0x0000);
	i2c1_wr_data(0x31E0, 0x1701);
	i2c1_wr_data(0x304C, 0x2000);
	i2c1_wr_data(0x304A, 0x0210);
	i2c1_wr_data(0x3082, 0x0001);
	i2c1_wr_data(0x3200, 0x0000);
	i2c1_wr_data(0x31D0, 0x0000);
	i2c1_wr_data(0x31AE, 0x0301);
	i2c1_wr_data(0x301A, 0x10DC);

	i2c1_wr_data(0x305A,0x008A);
	delay(20*1000);
	i2c1_wr_data(0x3056,0x0094);
	i2c1_wr_data(0x305C,0x0094);
	i2c1_wr_data(0x3058,0x008C);
		
}

#define TEST                           *((volatile uint32_t*)0x2001fe00)
#define TEST2                          *((volatile uint32_t*)0x2001fe04)
#define TEST3                          *((volatile uint32_t*)0x2001fe08)
#define TEST4                          *((volatile uint32_t*)0x2001fe0C)
#define TEST5                          *((volatile uint32_t*)0x2001fe10)
#define TEST6                          *((volatile uint32_t*)0x2001fe14)
#define TEST7                          *((volatile uint32_t*)0x2001fe18)
#define TEST8                          *((volatile uint32_t*)0x2001fe1c)					


