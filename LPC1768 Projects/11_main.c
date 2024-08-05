#include <LPC17xx.h>
#include <stdio.h>

#define LcdDataBusPort      LPC_GPIO1->FIOPIN
#define LcdControlBusPort   LPC_GPIO2->FIOPIN

#define LcdDataBusDirnReg   LPC_GPIO1->FIODIR
#define LcdCtrlBusDirnReg   LPC_GPIO2->FIODIR


#define LCD_D0     20
#define LCD_D1     21
#define LCD_D2     22
#define LCD_D3     23
#define LCD_D4     24
#define LCD_D5     25
#define LCD_D6     26
#define LCD_D7     27

#define LCD_RS     0
#define LCD_RW     1
#define LCD_EN     2


#define PortDataBusConfig  ((1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))
#define PortCtrlBusConfig  ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))
#define LCD_dataBusMask    ((1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))


#define SBIT_CLKEN     0    /* RTC Clock Enable*/
#define SBIT_CTCRST    1    /* RTC Clock Reset */
#define SBIT_CCALEN    4    /* RTC Calibration counter enable */



void ADC_Initialize( void );
uint16_t ADC_ReadData( void );
void delay(int cnt);
void sendByte(char byte);
void Lcd_DataWrite(char dat);
void Lcd_CmdWrite(char cmd);
void Lcd_StrWrite(const char *ptr);
void Lcd_Location(uint8_t row, uint8_t col);
int main( void )
{
    SystemInit();  
		char arr[10];
		char arr1[10];
		uint16_t year;
    uint8_t hour, min, sec, date, month;
	
    LcdDataBusDirnReg = PortDataBusConfig;   
    LcdCtrlBusDirnReg = PortCtrlBusConfig;

    Lcd_CmdWrite(0x38);                  
    Lcd_CmdWrite(0x01);                     
    Lcd_CmdWrite(0x0E);  

    LPC_RTC->CCR = ((1 << SBIT_CTCRST ) | (1 << SBIT_CCALEN));
    LPC_RTC->CALIBRATION = 0x00;
    LPC_RTC->CCR = (1 << SBIT_CLKEN);    /* Enable the clock for RTC */

    /* Set Date and Time only once, comment these lines after setting the time and date */                                           
    // Set Date 14th Nov 2015 
    LPC_RTC->DOM    = 15;   // Update date value 
    LPC_RTC->MONTH  = 04;   // Update month value
    LPC_RTC->YEAR   = 2023; // Update year value

    // Set Time 10:40:25 AM 
    LPC_RTC->HOUR   = 01;   // Update hour value 
    LPC_RTC->MIN    = 10
		


\

;   // Update min value
    LPC_RTC->SEC    = 00;   // Update sec value 


    while (1)
    {
        /* Read Time */
        hour = LPC_RTC->HOUR;
        min  = LPC_RTC->MIN; 
        sec  = LPC_RTC->SEC; 

        /* Read Date */
        date  = LPC_RTC->DOM;   
        month = LPC_RTC->MONTH;  
        year  = LPC_RTC->YEAR;   
				
				sprintf(arr,"RTC TIME:%02d:%02d:%02d",hour,min,sec);
		  	
				Lcd_CmdWrite(0x80);
        Lcd_StrWrite(arr); 
		  	sprintf(arr1,"RTC DATE:%02d:%02d:%04d",date,month,year);
				Lcd_CmdWrite(0xc0);
        Lcd_StrWrite(arr1); 
    }   
}

void delay(int cnt)
{
    int i;
    for(i=0;i<cnt;i++);
}


void sendByte(char byte)
{
    LcdDataBusPort&= (unsigned int)~(LCD_dataBusMask);                 
    LcdDataBusPort|= (unsigned int)(((byte >>0x00) & 0x01) << LCD_D0);
    LcdDataBusPort|= (unsigned int)(((byte >>0x01) & 0x01) << LCD_D1);
    LcdDataBusPort|= (unsigned int)(((byte >>0x02) & 0x01) << LCD_D2);
    LcdDataBusPort|= (unsigned int)(((byte >>0x03) & 0x01) << LCD_D3);
    LcdDataBusPort|= (unsigned int)(((byte >>0x04) & 0x01) << LCD_D4);
    LcdDataBusPort|= (unsigned int)(((byte >>0x05) & 0x01) << LCD_D5);
    LcdDataBusPort|= (unsigned int)(((byte >>0x06) & 0x01) << LCD_D6);
    LcdDataBusPort|= (unsigned int)(((byte >>0x07) & 0x01) << LCD_D7);
}

void Lcd_CmdWrite(char cmd)
{
    sendByte(cmd);                    
    LcdControlBusPort &= (unsigned int)~(1<<LCD_RS);
    LcdControlBusPort &= (unsigned int)~(1<<LCD_RW);
    LcdControlBusPort |= (1<<LCD_EN); 
    delay(1000);
    LcdControlBusPort &= (unsigned int)~(1<<LCD_EN);

    delay(10000);
}


void Lcd_DataWrite(char dat)
{
    sendByte(dat);                    
    LcdControlBusPort |= (1<<LCD_RS); 
    LcdControlBusPort &= (unsigned int)~(1<<LCD_RW); 
    LcdControlBusPort |= (1<<LCD_EN); 
    delay(1000);
    LcdControlBusPort &= (unsigned int)~(1<<LCD_EN);

    delay(10000);
}



void Lcd_Location(uint8_t row, uint8_t col){
	
	if(row == 1){
		Lcd_CmdWrite(0x80 | col);
	}
	else if(row == 2){
		Lcd_CmdWrite(0xc0 | col);
	}
	else if(row == 3){
		Lcd_CmdWrite(0x94 | col);
	}
	else{
		Lcd_CmdWrite(0xd4 | col);
	}
}

void Lcd_StrWrite(const char *ptr){
	
	while(*ptr){
		
		Lcd_DataWrite(*ptr++);
	}
	
}