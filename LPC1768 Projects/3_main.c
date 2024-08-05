#include <LPC17xx.h>

void delay( int ms );
int main( void ){
	
	SystemInit();
	LPC_PINCON->PINSEL2 = 0x00000000;
	LPC_GPIO0->FIODIR = 0xff;
	
	while(1){
		
		LPC_GPIO0->FIOPIN = 0x1;
		delay(100);
		
		LPC_GPIO0->FIOPIN = 0x2;
		delay(100);
		
		LPC_GPIO0->FIOPIN = 0x4;
		delay(100);
		
		LPC_GPIO0->FIOPIN = 0x8;
		delay(100);
		
		LPC_GPIO0->FIOPIN = 0x10;
		delay(100);
		
		LPC_GPIO0->FIOPIN = 0x20;
		delay(100);
		
		LPC_GPIO0->FIOPIN = 0x40;
		delay(100);
		
		LPC_GPIO0->FIOPIN = 0x80;
		delay(100);
		
	}
	
}

void delay( int ms ){
	
	int i,j;
	for(i=0;i<10000;i++){
		for(j=0;j<ms;j++);
	}
}

