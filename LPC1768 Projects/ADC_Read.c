#include <LPC17xx.h>
#include <stdio.h>


#define LCD_RS     0
#define LCD_RW     1
#define LCD_EN     8

#define lcd_bit 0xff00000


 
#define VREF       3.3 //Reference Voltage at VREFP pin, given VREFN = 0V(GND)
#define ADC_CLK_EN (1<<12)
#define SEL_AD0_0  (1<<0) //Select Channel AD0.0 
#define CLKDIV     1 //ADC clock-divider (ADC_CLOCK=PCLK/CLKDIV+1) = 12.5Mhz @ 25Mhz PCLK
#define PWRUP      (1<<21) //setting it to 0 will power it down
#define START_CNV  (1<<24) //001 for starting the conversion immediately
#define ADC_DONE   (1U<<31) //define it as unsigned value or compiler will throw #61-D warning
#define ADCR_SETUP_SCM ((CLKDIV<<8) | PWRUP)
#define	Ref_Vtg		3.300
#define	Full_Scale	0xFFF				//12 bit ADC


void delay(int cnt);
void Lcd_CmdWrite(char cmd);
void Lcd_DataWrite(char dat);
void Lcd_Inintialize( void ) ;
void lcd_string(char *ptr);

void ADC_Init( void );
int ADC_Read( void );

int main( void ) {
	  char adc_str[20] = {0};
    SystemInit();
    Lcd_Inintialize();
		unsigned long adc_temp;
		unsigned int i;
		float in_vtg;
    LPC_SC->PCONP |= (1<<15); 				//Power for GPIO block
    LPC_PINCON->PINSEL3 |= 0xC0000000;		//P1.31 as AD0.5
		LPC_SC->PCONP |= (1<<12);	
	
		Lcd_CmdWrite(0x80);
		lcd_string("LPC1768 ADC READ");
	  
    while (1) {
			 LPC_ADC->ADCR = (1<<5)|(1<<21)|(1<<24);		//0x01200001;//ADC0.5, start conversion and operational	
			for(i=0;i<2000;i++);						//delay for conversion
			while((adc_temp = LPC_ADC->ADGDR) == 0x80000000);	//wait till 'done' bit is 1, indicates conversion complete
			adc_temp = LPC_ADC->ADGDR;
			adc_temp >>= 4;
			adc_temp &= 0x00000FFF;						//12 bit ADC
			//in_vtg = (((float)adc_temp * (float)Ref_Vtg))/((float)Full_Scale);	//calculating input analog voltage
			sprintf(adc_str,"adc:%04d",adc_temp);				//convert the readings into string to display on LCD
	
			Lcd_CmdWrite(0xc0);
			lcd_string(adc_str);
			
			delay(500); //Slowing down Updates to 2 Updates per second
    }

}
void delay(int cnt)
{
    int i;
    for(i=0;i<cnt;i++);
}

void Lcd_CmdWrite(char cmd)
{
    LPC_GPIO1->FIOPIN = ((cmd<<20)& lcd_bit);                  
    LPC_GPIO1->FIOCLR = (1<<LCD_RS); 
    LPC_GPIO1->FIOCLR = (1<<LCD_RW); 
    LPC_GPIO1->FIOSET = (1<<LCD_EN);  
    delay(1000);
    LPC_GPIO1->FIOCLR = (1<<LCD_EN);

    delay(10000);
}

void Lcd_DataWrite(char dat)
{
    LPC_GPIO1->FIOPIN = ((dat<<20)& lcd_bit);                
    LPC_GPIO1->FIOSET = (1<<LCD_RS); 
    LPC_GPIO1->FIOCLR = (1<<LCD_RW); 
    LPC_GPIO1->FIOSET = (1<<LCD_EN);  
    delay(1000);
    LPC_GPIO1->FIOCLR = (1<<LCD_EN);

    delay(10000);
}

void Lcd_Inintialize( void ) {
	
	LPC_GPIO1->FIODIR = 0xFF0010F; 
																					
	Lcd_CmdWrite(0x38);                     
	Lcd_CmdWrite(0x01);                     
	Lcd_CmdWrite(0x0c);                   
	Lcd_CmdWrite(0x80); 
}
void lcd_string(char *ptr){
	
	while(*ptr) {
		Lcd_DataWrite(*ptr++);
	}
}
//void ADC_Init( void ) {

////    LPC_SC->PCONP |= (1 << 12);

////    LPC_PINCON->PINSEL1 |= (1 << 14); 
////	
////		LPC_ADC->ADCR = (1<<16);
////	

////    LPC_ADC->ADCR = (1 << 0) | (1 << 21)|(1<<8)|(1<<24);
//	
//	
//		LPC_SC->PCONP |= ADC_CLK_EN; //Enable ADC clock
//		LPC_ADC->ADCR =  ADCR_SETUP_BURST | SEL_AD0_0 | SEL_AD0_1; 
//}

//int ADC_Read( void ) {

//    unsigned long ADGDR_Read = LPC_ADC->ADGDR;
//		int channel = (ADGDR_Read>>24) & 0x7; //Extract Channel Number
//		int currentResult = (ADGDR_Read>>4) & 0xFFF; //Extract Conversion Result
//		return currentResult;
//}



