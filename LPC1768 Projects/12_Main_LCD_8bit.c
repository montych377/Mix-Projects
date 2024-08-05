/*
#include <LPC17xx.h>

#define LCD_DATA_PORT   LPC_GPIO1->FIOPIN
#define LCD_CTRL_PORT   LPC_GPIO2->FIOPIN

#define LCD_DATA_PORT_DIR  LPC_GPIO1->FIODIR
#define LCD_CTRL_PORT_DIR  LPC_GPIO2->FIODIR

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

#define LCD_D0 20
#define LCD_D1 21
#define LCD_D2 22
#define LCD_D3 23
#define LCD_D4 24
#define LCD_D5 25
#define LCD_D6 26
#define LCD_D7 27

#define LCD_DATA_CONFIG  ((1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))
#define LCD_DATA_MASK    ((1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))
#define LCD_CTRL_CONFIG    ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))


void LCD_WriteByte(char byte);
void LCD_WriteCommand(char command);
void LCD_WriteData(char data);
void LCD_WriteString(char *ptr);
void LCD_WriteLocation(uint8_t row, uint8_t col);
void Delay_lcd(int ms);

void LCD_Initialize( void ); 

int main( void ){
	
	LCD_DATA_PORT_DIR = LCD_DATA_CONFIG;
	LCD_CTRL_PORT_DIR = LCD_CTRL_CONFIG;
	
  LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x01);
	LCD_WriteCommand(0x0E);
	LCD_WriteCommand(0x80);
	while(1){
		LCD_WriteLocation(1,0);
		LCD_WriteString("How are you man!!");
		Delay_lcd(100000);
		
	}
}

void LCD_WriteByte(char byte){
	
	LCD_DATA_PORT &= (unsigned int)~(LCD_DATA_MASK);
	LCD_DATA_PORT |= (unsigned int)(((byte >> 0x00) & 0x01) << LCD_D0);
	LCD_DATA_PORT |= (unsigned int)(((byte >> 0x01) & 0x01) << LCD_D1);
	LCD_DATA_PORT |= (unsigned int)(((byte >> 0x02) & 0x01) << LCD_D2);
	LCD_DATA_PORT |= (unsigned int)(((byte >> 0x03) & 0x01) << LCD_D3);
	LCD_DATA_PORT |= (unsigned int)(((byte >> 0x04) & 0x01) << LCD_D4);
	LCD_DATA_PORT |= (unsigned int)(((byte >> 0x05) & 0x01) << LCD_D5);
	LCD_DATA_PORT |= (unsigned int)(((byte >> 0x06) & 0x01) << LCD_D6);
	LCD_DATA_PORT |= (unsigned int)(((byte >> 0x07) & 0x01) << LCD_D7);
}
void LCD_WriteCommand(char command){
	LCD_WriteByte(command);
	LCD_CTRL_PORT &= (unsigned int)~(1<<LCD_RS);
	LCD_CTRL_PORT &= (unsigned int)~(1<<LCD_RW);
	LCD_CTRL_PORT |= (1<<LCD_EN);
	Delay_lcd(100);
	LCD_CTRL_PORT &= (unsigned int)~(1<<LCD_EN);
	Delay_lcd(1000);
}
void LCD_WriteData(char data){
	
	LCD_WriteByte(data);
	LCD_CTRL_PORT |= (1<<LCD_RS);
	LCD_CTRL_PORT &= (unsigned int)~(1<<LCD_RW);
	LCD_CTRL_PORT |= (1<<LCD_EN);
	Delay_lcd(100);
	LCD_CTRL_PORT &= (unsigned int)~(1<<LCD_EN);
	Delay_lcd(1000);
}
void LCD_WriteString(char *ptr){
	
	while(*ptr){
		
		LCD_WriteData(*ptr++);
	}
}
void LCD_WriteLocation(uint8_t row, uint8_t col){
	
	if(row == 1){
		LCD_WriteCommand(0x80 | col);
	}
	
	else{
		LCD_WriteCommand(0xc0 | col);
	}
	
	
}
void Delay_lcd(int ms){
	
	int i;
	for(i=0;i<ms;i++);
}


*/



#include<lpc17xx.h>

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

void delay(int cnt)
{
    int i;
    for(i=0;i<cnt;i++);
}


void sendByte(char byte)
{
    LcdDataBusPort&=~(LCD_dataBusMask);                  // Clear previous data 
    LcdDataBusPort|= (((byte >>0x00) & 0x01) << LCD_D0);
    LcdDataBusPort|= (((byte >>0x01) & 0x01) << LCD_D1);
    LcdDataBusPort|= (((byte >>0x02) & 0x01) << LCD_D2);
    LcdDataBusPort|= (((byte >>0x03) & 0x01) << LCD_D3);
    LcdDataBusPort|= (((byte >>0x04) & 0x01) << LCD_D4);
    LcdDataBusPort|= (((byte >>0x05) & 0x01) << LCD_D5);
    LcdDataBusPort|= (((byte >>0x06) & 0x01) << LCD_D6);
    LcdDataBusPort|= (((byte >>0x07) & 0x01) << LCD_D7);
}

void Lcd_CmdWrite(char cmd)
{
    sendByte(cmd);                      //Send the Command
    LcdControlBusPort &= ~(1<<LCD_RS); // Send LOW pulse on RS pin for selecting Command register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN);

    delay(10000);
}

void Lcd_DataWrite(char dat)
{
    sendByte(dat);                     //Send the data
    LcdControlBusPort |= (1<<LCD_RS);  // Send HIGH pulse on RS pin for selecting data register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN);

    delay(10000);
}


int main( void )
{
    char i,a[]={"Good evening!"};
    SystemInit();                    //Clock and PLL configuration

    LcdDataBusDirnReg = PortDataBusConfig;    // Configure all the LCD pins as output
    LcdCtrlBusDirnReg = PortCtrlBusConfig;
                                            
    Lcd_CmdWrite(0x38);                      // enable 5x7 mode for chars 
    Lcd_CmdWrite(0x01);                      // Display OFF, Cursor ON
    Lcd_CmdWrite(0x0E);                     // Clear Display
    Lcd_CmdWrite(0x80);                      // Move the cursor to beginning of first line


    Lcd_DataWrite('H');
    Lcd_DataWrite('e');
    Lcd_DataWrite('l');
    Lcd_DataWrite('l');
    Lcd_DataWrite('o');
    Lcd_DataWrite(' ');
    Lcd_DataWrite('S');
    Lcd_DataWrite('h');
    Lcd_DataWrite('i');
    Lcd_DataWrite('p');
    Lcd_DataWrite('p');
		Lcd_DataWrite('i');

    Lcd_CmdWrite(0xc0);
    
    for(i=0;a[i]!=0;i++)
    {
        Lcd_DataWrite(a[i]);
    }

    while(1);
}




