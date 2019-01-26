#include <stdint.h>
#include "csi.h"
#include "cfg.h"

//mipi init

/**
  * @brief  initial mipi csi0.
  * @param  none
  *         
  * @retval none
  */
void mipi_csi0_init  (void)
{
//------------- MIPI CSI HOST setting @SYS_CTRL---------------------//
//enable MIPI pclk
    MIPI_CSI_CTRL                     = 0x1        ;

//----------start up mipi csi host------------//
//release mipi csi host from reset, set controller's internal logic to the default state
//----assert
    CSI2_RST                          = 0x0        ;
//----release
    CSI2_RST                          = 0x1        ;

//set or clear DPHY reset, set DPHY analog and digital logic to the default state
//----assert
    PHY_SHUTDOWNZ                     = 0x0        ; //offset 0x40
    DPHY_RSTZ                         = 0x0        ; //offset 0x44
//----release
    PHY_SHUTDOWNZ                     = 0x1        ; //offset 0x40
    DPHY_RSTZ                         = 0x1        ; //offset 0x44

//Release DPHY test code form reset,set DPHY internal config reg in default state
    PHY_TEST_CTRL0                    = 0x1        ; //offset 0x50
    PHY_TEST_CTRL0                    = 0x0        ; //offset 0x50
	
	
				//mipi ²î·ÖÐÅºÅ swap
	#if 1
	
	*((volatile uint32_t*)0x40008054)=0x00010055;
	*((volatile uint32_t*)0x40008050)=0x02;
	*((volatile uint32_t*)0x40008050)=0x00;
	*((volatile uint32_t*)0x40008054)=0x0000001;
	*((volatile uint32_t*)0x40008050)=0x02;
	*((volatile uint32_t*)0x40008050)=0x00;
	#endif

//----------initialize mipi csi host------------//
//***************A: Release DPHY test code form reset************************************************************//

//***************B: config DPHY frequency range, prepare the DPHY RX to operate with a given frequency***********//
//-write test code configration, execute a write opration
//---set clock lane (PHY_REG_0x34 = 0x14)---//
//--1.set test bus opration address
//-----set test code select(0x34:HS RX Control of clock lane)
    PHY_TEST_CTRL1                    = 0x00010034 ; //[  16]:1:write addr @negedge PHY_TESTCLK
                                                     //[15:8]:TESTOUT
                                                     //[7:0 ]:TESTIN,address = 0x34
//-----generate PHY_TESTCLK
    PHY_TEST_CTRL0                    = 0x2        ; //offset 0x50,generate phy_testclk high
    PHY_TEST_CTRL0                    = 0x0        ; //offset 0x50,generate phy_testclk low ,write addr will be sample @negedge PHY_TESTCLK

//--2.set test bus opration data
    PHY_TEST_CTRL1                    = 0x00000014 ;//[  16]:0:write data @posedge PHY_TESTCLK
                                                     //[15:8]:TESTOUT
                                                     //[7:0 ]:TESTIN,address = 0x14(8'b00 0 XXXX 0) XXXX = 1010 <800~1000MHz >    Y = 0 <enable HS RX settle filter>
                                                     //                                                  = 1001 <700~ 800MHz >      = 1 <bypass HS RX settle filter>
                                                     //                                                  = 1000 <600~ 700MHz >
                                                     //                                                  = 0111 <500~ 600MHz >
                                                     //                                                  = 0110 <400~ 500MHz >
                                                     //                                                  = 0101 <300~ 400MHz >
                                                     //                                                  = 0100 <250~ 300MHz >
                                                     //                                                  = 0011 <200~ 250MHz >
                                                     //                                                  = 0010 <150~ 200MHz >
                                                     //                                                  = 0001 <110~ 150MHz >
                                                     //                                                  = 0000 < 80~ 100MHz >

//-----generate PHY_TESTCLK
    PHY_TEST_CTRL0                    = 0x2        ; //offset 0x50,generate phy_testclk high,write addr will be sample @posedge PHY_TESTCLK
    PHY_TEST_CTRL0                    = 0x0        ; //offset 0x50,generate phy_testclk low 

//---set data lane0 (PHY_REG_0x44 = 0x14)---//
//--1.set test bus opration address
//-----set test code select(0x44:HS RX Control of lane0)
    PHY_TEST_CTRL1                    = 0x00010044 ; //[  16]:1:write addr @negedge PHY_TESTCLK
                                                     //[15:8]:TESTOUT
                                                     //[7:0 ]:TESTIN,address = 0x44
//-----generate PHY_TESTCLK
    PHY_TEST_CTRL0                    = 0x2        ; //offset 0x50,generate phy_testclk high
    PHY_TEST_CTRL0                    = 0x0        ; //offset 0x50,generate phy_testclk low ,write addr will be sample @negedge PHY_TESTCLK

//--2.set test bus opration data
    PHY_TEST_CTRL1                    = 0x00000014 ;//[  16]:0:write data @posedge PHY_TESTCLK
                                                     //[15:8]:TESTOUT
                                                     //[7:0 ]:TESTIN,address = 0x14(8'b00 0 XXXX Y) XXXX = 1010 <800~1000MHz >    Y = 0 <>
                                                     //                                                  = 1001 <700~ 800MHz >      = 1 <override HS frequency range>
                                                     //                                                  = 1000 <600~ 700MHz >
                                                     //                                                  = 0111 <500~ 600MHz >
                                                     //                                                  = 0110 <400~ 500MHz >
                                                     //                                                  = 0101 <300~ 400MHz >
                                                     //                                                  = 0100 <250~ 300MHz >
                                                     //                                                  = 0011 <200~ 250MHz >
                                                     //                                                  = 0010 <150~ 200MHz >
                                                     //                                                  = 0001 <110~ 150MHz >
    PHY_TEST_CTRL0                    = 0x2        ; //offset 0x50,generate phy_testclk pluse
    PHY_TEST_CTRL0                    = 0x0        ; //offset 0x50

//---set data lane1 (PHY_REG_0x54 = 0x14)---//
//--1.set test bus opration address
//-----set test code select(0x54:HS RX Control of lane1)
    PHY_TEST_CTRL1                    = 0x00010054 ; //[  16]:1:write addr @negedge PHY_TESTCLK
                                                     //[15:8]:TESTOUT
                                                     //[7:0 ]:TESTIN,address = 0x54
//-----generate PHY_TESTCLK
    PHY_TEST_CTRL0                    = 0x2        ; //offset 0x50,generate phy_testclk high
    PHY_TEST_CTRL0                    = 0x0        ; //offset 0x50,generate phy_testclk low ,write addr will be sample @negedge PHY_TESTCLK

//--2.set test bus opration data
    PHY_TEST_CTRL1                    = 0x00000014 ;//[  16]:0:write data @posedge PHY_TESTCLK
                                                     //[15:8]:TESTOUT
                                                     //[7:0 ]:TESTIN,address = 0x14(8'b00 0 XXXX Y) XXXX = 1010 <800~1000MHz >    Y = 0 <>
                                                     //                                                  = 1001 <700~ 800MHz >      = 1 <override HS frequency range>
                                                     //                                                  = 1000 <600~ 700MHz >
                                                     //                                                  = 0111 <500~ 600MHz >
                                                     //                                                  = 0110 <400~ 500MHz >
                                                     //                                                  = 0101 <300~ 400MHz >
                                                     //                                                  = 0100 <250~ 300MHz >
                                                     //                                                  = 0011 <200~ 250MHz >
                                                     //                                                  = 0010 <150~ 200MHz >
                                                     //                                                  = 0001 <110~ 150MHz >
    PHY_TEST_CTRL0                    = 0x2        ; //offset 0x50,generate phy_testclk pluse
    PHY_TEST_CTRL0                    = 0x0        ; //offset 0x50

//***************oprional: performs addtional PHY test code config  ***********//
//NA

//***************C: set or clear DPHY from  reset  ***********//
//set or clear DPHY reset, set DPHY analog and digital logic to the default state
//----assert
    PHY_SHUTDOWNZ                     = 0x0        ; //offset 0x40
    DPHY_RSTZ                         = 0x0        ; //offset 0x44
//----release
    PHY_SHUTDOWNZ                     = 0x1        ; //offset 0x40
    DPHY_RSTZ                         = 0x1        ; //offset 0x44


//***************D: config number of active lanes  ***********//
    N_LANES                           = 0x1        ; //offset 0x04
                                                     //000 1lane
                                                     //001 2lane
                                                     //010 3lane
                                                     //011 4lane
                                                     //100 5lane
                                                     //101 6lane
                                                     //110 7lane
                                                     //111 8lane

//***************oprional: config data id  ***********//
//config Data ID,if not used set 0
    DATA_IDS_1                        = 0x0        ; //offset 0x10
                                                     //[31:30]:VC of Data ID3   [29:24]:DT of Data ID3
                                                     //[23:22]:VC of Data ID2   [21:16]:DT of Data ID2
                                                     //[15:14]:VC of Data ID1   [13: 8]:DT of Data ID2
                                                     //[ 7: 6]:VC of Data ID0   [ 5: 0]:DT of Data ID0
    DATA_IDS_2                        = 0x0        ; //offset 0x14
                                                     //[31:30]:VC of Data ID7   [29:24]:DT of Data ID7
                                                     //[23:22]:VC of Data ID6   [21:16]:DT of Data ID6
                                                     //[15:14]:VC of Data ID5   [13: 8]:DT of Data ID5
                                                     //[ 7: 6]:VC of Data ID4   [ 5: 0]:DT of Data ID4

//***************E: define error mask  ***********//
    INT_MSK_PHY_FATAL                 =0xff  ; //offset 0xe4

    INT_MSK_PKT_FATAL                 =0xff  ; //offset 0xf4

    INT_MSK_FRAME_FATAL               =0xff  ; //offset 0x104

    INT_MSK_PHY                       =0xff  ; //offset 0x114

    INT_MSK_PKT                       =0xff  ; //offset 0x124

    INT_MSK_LINE                      =0xff  ; //offset 0x134



//***************F: release mipi-csi2 host  reset***********//
//release mipi csi host from reset, set controller's internal logic to the default state
//----assert
    CSI2_RST                          = 0x0        ;
//----release
    CSI2_RST                          = 0x1        ;


//***************G: check if data lanes are in stop state***********//
while((*(volatile uint32_t *)(0x4000804c) & 0x03) != 0x3);


 }

 
 /**
  * @brief  This function handles CSI0 exception.
  * @param  None
  * @retval None
  */
void CSI0_IRQHandler (void)
{


}
