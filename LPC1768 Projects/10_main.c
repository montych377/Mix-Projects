

#include<LPC17xx.h>
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
	  char data[15];
    LcdDataBusDirnReg = PortDataBusConfig;   
    LcdCtrlBusDirnReg = PortCtrlBusConfig;
		ADC_Initialize();
    Lcd_CmdWrite(0x38);                  
    Lcd_CmdWrite(0x01);                     
    Lcd_CmdWrite(0x0E);  

    while(1){
			
			uint16_t adc = ADC_ReadData();
			 
			sprintf(data,"ADC TEST = %d",adc);
			Lcd_CmdWrite(0x80);
			Lcd_StrWrite(data);
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

void ADC_Initialize( void ){
	
	LPC_SC->PCONP |= (1<<12);
	LPC_ADC->ADCR = ((1<<21) | (10<<8));
	LPC_PINCON->PINSEL1 |= 0x01<<14;
	
}
uint16_t ADC_ReadData( void ){
	
	uint16_t value;
	LPC_ADC->ADCR |= 0x01;
	LPC_ADC->ADCR |= (1<<24);
	delay(100);
	while((LPC_ADC->ADGDR & (1 << 31))==0);
	value = (LPC_ADC->ADGDR >> 4) &0xfff;
	return value;
	
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
/*
#include <LPC17xx.h>

#define LCD_DATA_PORT   LPC_GPIO1->FIOPIN
#define LCD_CTRL_PORT   LPC_GPIO2->FIOPIN

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

#define LCD_D0 20
#define LCD_D1 21
#define LCD_D2 22
#define LCD_D3 23
#define LCD_D4 24
#define LCD_D5 35
#define LCD_D6 26
#define LCD_D7 27

#define DATA_PIN_CONFIG  ((1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))
#define DATA_PIN_MASK    ((1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))

#define CTRL_PIN_CONFIG  ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))

void ADC_Initialize( void );
int ADC_ReadData( void );

void LCD_Mask_Bits(char byte);
void LCD_WriteCommand(char command);
void LCD_WriteData(char data);
void LCD_Initialize( void );
void LCD_WriteString(const char *ptr);
void LCD_Location(uint8_t row, uint8_t col);
void LCD_Delay(int ms);


int main( void ){
	
	LPC_GPIO1->FIODIR = DATA_PIN_CONFIG;
	LPC_GPIO2->FIODIR = CTRL_PIN_CONFIG;
	
	LCD_Initialize();
	
	//ADC_Initialize();
	LCD_WriteCommand(0x01);
	
	
	
	
	while(1){
		
		LCD_WriteString("udofhfh");
	
	}
	
}

void ADC_Initialize( void ){
	
	LPC_SC->PCONP |= (1<<12);
	LPC_PINCON->PINSEL1 |= (1<<18);
	LPC_ADC->ADCR = (1<<2) | (4<<8) | (1<<21);
}
int ADC_ReadData( void ){
	
	int value;
	LPC_ADC->ADCR |= (1<<24);
	while((LPC_ADC->ADGDR & (1<<31))==0);
	value = (LPC_ADC->ADGDR >> 4) &0xfff;
	return value;
	
}
void LCD_Mask_Bits(char byte){
	
	LCD_DATA_PORT &= ~(DATA_PIN_MASK);
	LCD_DATA_PORT |= (((byte >> 0x00)&0x01) << LCD_D0);
	LCD_DATA_PORT |= (((byte >> 0x01)&0x01) << LCD_D1);
	LCD_DATA_PORT |= (((byte >> 0x02)&0x01) << LCD_D2);
	LCD_DATA_PORT |= (((byte >> 0x03)&0x01) << LCD_D3);
	LCD_DATA_PORT |= (((byte >> 0x04)&0x01) << LCD_D4);
	LCD_DATA_PORT |= (((byte >> 0x05)&0x01) << LCD_D5);
	LCD_DATA_PORT |= (((byte >> 0x06)&0x01) << LCD_D6);
	LCD_DATA_PORT |= (((byte >> 0x07)&0x01) << LCD_D7);
	
}
void LCD_WriteCommand(char command){
	
	LCD_Mask_Bits(command);
	
	LCD_CTRL_PORT &= ~(1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |= (1<<LCD_EN);
	LCD_Delay(1000);
	
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	LCD_Delay(10000);
}
void LCD_WriteData(char data){
	
	LCD_Mask_Bits(data);
	
	LCD_CTRL_PORT |=  (1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |= (1<<LCD_EN);
	LCD_Delay(1000);
	
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	LCD_Delay(10000);
}
void LCD_Initialize( void ){
	
	LCD_WriteCommand(0x01);
	LCD_WriteCommand(0x02);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0c);
	LCD_WriteCommand(0x80);
}
void LCD_WriteString(const char *ptr){
	
	while(*ptr){
		LCD_WriteData(*ptr++);
	}
}
void LCD_Location(uint8_t row, uint8_t col){
	
	if(row == 1){
		LCD_WriteCommand(0xc0 | col);
	}
	else{
		
		LCD_WriteCommand(0x80 | col);
		
	}
}
void LCD_Delay(int ms){
	
	int i=0;
	for(i=0;i<ms;i++);
	
}
*/
