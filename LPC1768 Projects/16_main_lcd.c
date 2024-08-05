#include<LPC17xx.h>

#define LCD_DATA_PORT        LPC_GPIO1->FIOPIN
#define LCD_DATA_PORT_DIR    LPC_GPIO1->FIODIR
#define LCD_CTRL_PORT        LPC_GPIO2->FIOPIN
#define LCD_CTRL_PORT_DIR    LPC_GPIO2->FIODIR

#define LCD_D0   20
#define LCD_D1   21
#define LCD_D2   22
#define LCD_D3   23
#define LCD_D4   24
#define LCD_D5   25
#define LCD_D6   26
#define LCD_D7   27

#define LCD_RS   0
#define LCD_RW   1
#define LCD_EN   2


#define LCD_DATA_PIN_CONFIG    ((1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))
#define LCD_DATA_PIN_MASK      ((1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))
#define LCD_CTRL_PIN_CONFIG    ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))

void WriteByte(char byte);
void LCD_Initialize( void );
void LCD_WriteCmd( char cmd );
void LCD_WriteData(char data);
void LCD_WriteString(char *ptr);
void Delay(int ms);
int main( void ){
		char arr[10] = " Hello ";
	int i=0;
		LCD_Initialize();
		while(1){
			LCD_WriteCmd(0x80);
			LCD_WriteString("Monty ");
			Delay(1000);
			LCD_WriteString(" Hello");
		}
}

void Delay(int ms){
	
	int i,j;
	for(i=0;i<ms;i++){
		for(j=0;j<1000;j++);
	}
}


void WriteByte(char byte){
	
	LCD_DATA_PORT &=~(LCD_DATA_PIN_MASK);
	
	LCD_DATA_PORT |= (((byte >> 0x00) & 0x01) << LCD_D0);
	LCD_DATA_PORT |= (((byte >> 0x01) & 0x01) << LCD_D1);
	LCD_DATA_PORT |= (((byte >> 0x02) & 0x01) << LCD_D2);
	LCD_DATA_PORT |= (((byte >> 0x03) & 0x01) << LCD_D3);
	LCD_DATA_PORT |= (((byte >> 0x04) & 0x01) << LCD_D4);
	LCD_DATA_PORT |= (((byte >> 0x05) & 0x01) << LCD_D5);
	LCD_DATA_PORT |= (((byte >> 0x06) & 0x01) << LCD_D6);
	LCD_DATA_PORT |= (((byte >> 0x07) & 0x01) << LCD_D7);
}
void LCD_Initialize( void ){
	
	LCD_DATA_PORT_DIR = LCD_DATA_PIN_CONFIG;
	LCD_CTRL_PORT_DIR = LCD_CTRL_PIN_CONFIG;
	
	LCD_WriteCmd(0x01);
	LCD_WriteCmd(0x80);
	LCD_WriteCmd(0x38);
	LCD_WriteCmd(0x0E);
}
void LCD_WriteCmd( char cmd ){
	
	WriteByte(cmd);
	LCD_CTRL_PORT &= ~(1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |= (1<<LCD_EN);
	Delay(1);
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	Delay(10);
}
void LCD_WriteData(char data){
	
	WriteByte(data);
	LCD_CTRL_PORT |= (1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |= (1<<LCD_EN);
	Delay(1);
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	Delay(10);
}
void LCD_WriteString(char *ptr){
	
	while(*ptr != '\0'){
		
		LCD_WriteData(*ptr++);
	}
}



