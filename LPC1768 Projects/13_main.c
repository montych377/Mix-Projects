#include <LPC17xx.h>


#define LCD_DATA_PORT   LPC_GPIO1->FIOPIN
#define LCD_CTRL_PORT   LPC_GPIO2->FIOPIN

#define LCD_DATA_PORT_DIR   LPC_GPIO1->FIODIR
#define LCD_CTRL_PORT_DIR   LPC_GPIO2->FIODIR


#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

#define LCD_D4 24
#define LCD_D5 25
#define LCD_D6 26
#define LCD_D7 27

#define LCD_DATA_CONFIG  ((1<<LCD_D4|1<<LCD_D5|1<<LCD_D6|1<<LCD_D7))
#define LCD_DATA_MASK    ((1<<LCD_D4|1<<LCD_D5|1<<LCD_D6|1<<LCD_D7))

#define LCD_CTRL_CONFIG  ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))

void LCD_WriteByte(char byte);
void LCD_WriteCommand(char cmd);
void LCD_WriteData(char data);
void LCD_WriteString(const char *ptr);
void LCD_Initialize( void );
void LCD_WriteLocation(uint8_t row, uint8_t col);
void LCD_Delay(int ms);
int main( void ){
	
	LCD_CTRL_PORT_DIR |= LCD_CTRL_CONFIG;
	LCD_DATA_PORT_DIR |= LCD_DATA_CONFIG;
	LCD_Initialize();
	
	while(1){
		for(int i=0;i<15;i++){
			
			LCD_WriteLocation(1,i);
			LCD_WriteData('A');
			LCD_Delay(1000000);
		}
		
	}
	
	
}

void LCD_Delay(int ms){
	
	int i=0;
	for(i=0;i<ms;i++){
		
		
	}
}

void LCD_WriteByte(char byte){
	
	LCD_DATA_PORT &= ~(LCD_DATA_MASK);
	LCD_DATA_PORT |= (((byte >> 0x04) & 0x01) << LCD_D4);
	LCD_DATA_PORT |= (((byte >> 0x05) & 0x01) << LCD_D5);
	LCD_DATA_PORT |= (((byte >> 0x06) & 0x01) << LCD_D6);
	LCD_DATA_PORT |= (((byte >> 0x07) & 0x01) << LCD_D7);
}
void LCD_WriteCommand(char cmd){
	
	LCD_WriteByte(cmd & 0xf0);
	LCD_CTRL_PORT &= ~(1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |=  (1<<LCD_EN);
	LCD_Delay(100);
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	LCD_Delay(1000);
	
	LCD_WriteByte((cmd << 4)&0xf0);
	LCD_CTRL_PORT &= ~(1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |=  (1<<LCD_EN);
	LCD_Delay(100);
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	LCD_Delay(1000);
}
void LCD_WriteData(char data){
	
	LCD_WriteByte(data & 0xf0);
	LCD_CTRL_PORT |=  (1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |=  (1<<LCD_EN);
	LCD_Delay(100);
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	LCD_Delay(1000);
	
	LCD_WriteByte((data << 4)&0xf0);
	LCD_CTRL_PORT |=  (1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |=  (1<<LCD_EN);
	LCD_Delay(100);
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	LCD_Delay(1000);
}
void LCD_Initialize( void ){
	
	LCD_WriteCommand(0x01);
	LCD_WriteCommand(0x02);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x28);
	LCD_WriteCommand(0x0c);
}
void LCD_WriteLocation(uint8_t row, uint8_t col){
	
	if(row == 2){
		LCD_WriteCommand(0xc0 | col);
	}
	else{
		LCD_WriteCommand(0x80 | col);
	}
}

void LCD_WriteString(const char *ptr){
	
	while(*ptr != '\0'){
		LCD_WriteData(*ptr++);
	}
}

