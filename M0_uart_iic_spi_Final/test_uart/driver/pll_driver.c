#include "cfg.h"
#include "sys.h"


/**
  * @brief  initial pll for dsp.
  * @param  none
  *         
  * @retval none
  */
void pll_init(void)
{
	DSP_CTRL &=~0x01;//disable dsp clk
	//pll setting
    PLL_CTRL2 = 0x11fc04;
    PLL_CTRL1 = 0x1418310c;//100M CLK
	
	//PLL_CTRL1 = 0x3230540c;//170M CLK
	//power on
    PLL_CTRL0 |= 0x1;
	delay(100);//wait
	PLL_CTRL0 = 0x03;//release rstz
	delay(1000);//wait for pll lock
	while(PLL_STA != 1); //check if pll lock
	//change pll clock and enable dsp
    DSP_CTRL = 0x3;
}
