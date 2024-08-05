#include <LPC17xx.h>

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
	
	uint8_t d;
	
}Typedef_PinConfig;

void Data_Write(char data) {
	
	Typedef_PinConfig y;
	
	y.b0= (0x01 & data) ? 1 : 0;
	y.b1= (0x02 & data) ? 1 : 0;
	y.b2= (0x04 & data) ? 1 : 0;
	y.b3= (0x08 & data) ? 1 : 0;
	y.b4= (0x10 & data) ? 1 : 0;
	y.b5= (0x20 & data) ? 1 : 0;
	y.b6= (0x40 & data) ? 1 : 0;
	y.b7= (0x80 & data) ? 1 : 0;
	
	LPC_GPIO0 -> FIOPIN = y.d;
}

void delay_ms(int ms) {
	
	uint16_t i,j;
	for(i=0;i<ms;i++) {
		
		for(j=0;j<1000;j++);
	}
}
int main( void ) {
	
	LPC_PINCON -> PINSEL0 = 0x00000000;
	LPC_GPIO0 -> FIODIR = 0xFFFF;
	
	while(1) {
		
		Data_Write(0x01);
		delay_ms(1000);
		Data_Write(0x02);
		delay_ms(1000);
		Data_Write(0x04);
		delay_ms(1000);
		Data_Write(0x08);
		delay_ms(1000);
		Data_Write(0x10);
		delay_ms(1000);
		Data_Write(0x20);
		delay_ms(1000);
		Data_Write(0x40);
		delay_ms(1000);
		Data_Write(0x80);
		delay_ms(1000);
		
		
	}
	
}

