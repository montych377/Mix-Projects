#include <LPC17xx.h>
#include <stdint.h>

#define uint8_t unsigned char
typedef union{
	
	struct{
		
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
		
	};
	
	struct{
		
		uint8_t Nib1:4;
		uint8_t Nib2:4;
	};
	
	uint8_t x;
	
}Typedef_LCD_Config;


typedef struct{
	
	uint32_t P2_0:1;
	uint32_t P2_1:1;
	uint32_t P2_2:1;
	uint32_t P2_3:1;
	uint32_t P2_4:1;
	uint32_t P2_5:1;
	uint32_t P2_6:1;
	uint32_t P2_7:1;
	uint32_t P2_8:1;
	uint32_t P2_9:1;

}Typedef_Pin_Config;

#define GPIO2_PIN  ((volatile Typedef_Pin_Config *) &LPC_GPIO2->FIOPIN)
#define GPIO2_SET  ((volatile Typedef_Pin_Config *) &LPC_GPIO2->FIOSET)
#define GPIO2_CLR  ((volatile Typedef_Pin_Config *) &LPC_GPIO2->FIOCLR)
	
void Send_byte(uint8_t d);
void lcd_cmd(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_init(void );

void delay(uint16_t ms);

int main( void ) {
	
	SystemInit();
	LPC_GPIO2->FIODIR = (1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9);
	lcd_init();

	while(1) {
		
			lcd_cmd(0x80);
			lcd_data('A');
	}
}

void Send_byte(uint8_t d){
	
	LPC_GPIO2->FIOCLR = 0xffff;
	Typedef_LCD_Config y = (Typedef_LCD_Config )d;
	GPIO2_PIN->P2_2 = y.b0;
	GPIO2_PIN->P2_3 = y.b1;
	GPIO2_PIN->P2_4 = y.b2;
	GPIO2_PIN->P2_5 = y.b3;
	GPIO2_PIN->P2_6 = y.b4;
	GPIO2_PIN->P2_7 = y.b5;
	GPIO2_PIN->P2_8 = y.b6;
	GPIO2_PIN->P2_9 = y.b7;
}
void lcd_cmd(uint8_t cmd){
	
	Send_byte(cmd);
	GPIO2_CLR->P2_0 = 1;
	GPIO2_SET->P2_1 = 1;
	delay(2);
	GPIO2_CLR->P2_1 = 1;
	delay(2);
}
void lcd_data(uint8_t data){
	
	Send_byte(data);
	GPIO2_SET->P2_0 = 1;
	GPIO2_SET->P2_1 = 1;
	delay(2);
	GPIO2_CLR->P2_1 = 1;
	delay(2);
}
void lcd_init(void ){
	
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x06);
	lcd_cmd(0x38);
	lcd_cmd(0x0c);
}

void delay(uint16_t ms){
	
	uint16_t i=0,j=0;
	
	for(i=0;i<ms;i++) {
		for(j=0;j<5000;j++){
			
		}
	}
}