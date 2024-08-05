#include<lpc17xx.h>
#include "lcd.h"       
#include "delay.h"      
        
/* Bit positions of ADCR and ADGR registers */ 
#define SBIT_BURST      16u
#define SBIT_START      24u
#define SBIT_PDN        21u
#define SBIT_EDGE       27u 
#define SBIT_DONE       31u
#define SBIT_RESULT     4u
#define SBIT_CLCKDIV    8u


int main()
{
    uint16_t adc_result;
    SystemInit();                              //Clock and PLL configuration

   /* Setup/Map the controller pins for LCD operation 
              RS   RW   EN   D0    D1    D2    D3    D4    D5    D6    D7   */
    LCD_SetUp(P2_0,P2_1,P2_2,P_NC,P_NC,P_NC,P_NC,P1_10,P1_9,P1_8,P1_4);

  /* Specify the LCD type(2x16) for initialization*/
    LCD_Init(2,16);    
    
      
    LPC_SC->PCONP |= (1 << 12);      /* Enable CLOCK for internal ADC controller */

    LPC_ADC->ADCR = ((1<<SBIT_PDN) | (10<<SBIT_CLCKDIV));  //Set the clock and Power ON ADC module

    LPC_PINCON->PINSEL3|= 0x01<<30;      	/* Select the P1_31 AD0[5] for ADC function */
	  LPC_PINCON->PINSEL3|= 0x01<<31;      	/* Select the P1_31 AD0[5] for ADC function */

    

    while(1)
    {
        
        LPC_ADC->ADCR  |= 0x01<<5;        /* Select Channel 5 by setting 5th bit of ADCR */
        DELAY_us(10);                  /* allow the channel voltage to stabilize*/
        
        util_BitSet(LPC_ADC->ADCR,SBIT_START);            /*Start ADC conversion*/
        
        while(util_GetBitStatus(LPC_ADC->ADGDR,SBIT_DONE)==0);  /* wait till conversion completes */
        
        adc_result = (LPC_ADC->ADGDR >> SBIT_RESULT) & 0xfff;   /*Read the 12bit adc result*/
        
        LCD_GoToLine(0);                      /* Go to First line of 2x16 LCD */
        LCD_Printf("ADC5:%4d",adc_result);   /* Display 4-digit adc result */  
    }
}