/*#include <LPC17xx.h>
#define RS 8
#define RW 9
#define EN 10

#define LCD_DATA_BIT_MUSKING  0xFF

void _delay_ms(uint32_t ms);
void lcd_cmd(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_init( void );


int main( void ) {
	
	lcd_init();
	
	while(1) {
		
		lcd_cmd(0x80);
		lcd_data('A');
	}
}

void _delay_ms(uint32_t ms){
	uint32_t i=0,j=0;
	for(i=0;i<ms;i++){
		for(j=0;j<5000;j++){
			
		}
	}
}
void lcd_cmd(uint8_t cmd){
	
	LPC_GPIO0->FIOCLR = (1<<RS);
	LPC_GPIO0->FIOPIN = ( cmd & LCD_DATA_BIT_MUSKING);
	LPC_GPIO0->FIOCLR = (1<<RW);
	LPC_GPIO0->FIOSET = (1<<EN);
	_delay_ms(2);
	LPC_GPIO0->FIOCLR = (1<<EN);
	_delay_ms(2);
}
void lcd_data(uint8_t data){
	
	LPC_GPIO0->FIOSET = (1<<RS);
	LPC_GPIO0->FIOPIN = ( data & LCD_DATA_BIT_MUSKING);
	LPC_GPIO0->FIOCLR = (1<<RW);
	LPC_GPIO0->FIOSET = (1<<EN);
	_delay_ms(2);
	LPC_GPIO0->FIOCLR = (1<<EN);
	_delay_ms(2);
}
void lcd_init( void ){
	
	LPC_PINCON->PINSEL0 = 0x0000;
	LPC_GPIO0->FIODIR = 0xFFFF;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x06);
	lcd_cmd(0x38);
	lcd_cmd(0x0c);
}
*/


#include<lpc17xx.h>



#define LCD_RS     0
#define LCD_RW     1
#define LCD_EN     8

#define lcd_bit 0xff00000

void delay(int cnt);
void Lcd_CmdWrite(char cmd);
void Lcd_DataWrite(char dat);
void Lcd_Inintialize( void ) ;
void lcd_string(char *ptr);

int  main( void )
{
    SystemInit();                 

		Lcd_Inintialize();
		Lcd_CmdWrite(0x80);
	  lcd_string("Hello World!!");

    while(1){
			Lcd_CmdWrite(0xc0);
			lcd_string("monty hgjhj bhai");
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
	
	LPC_GPIO1->FIODIR = 0xFF0010F;  // Configure all the LCD pins as output
	//LPC_GPIO2->FIODIR = 0x0F;
																					
	Lcd_CmdWrite(0x38);                      // enable 5x7 mode for chars 
	Lcd_CmdWrite(0x01);                      // Display OFF, Cursor ON
	Lcd_CmdWrite(0x0E);                     // Clear Display
	Lcd_CmdWrite(0x80); 
}
void lcd_string(char *ptr){
	
	while(*ptr) {
		Lcd_DataWrite(*ptr++);
	}
}
