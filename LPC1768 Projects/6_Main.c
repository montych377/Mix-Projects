#include <LPC17xx.h>

#define button 0

void delay(int ms);

int main( void ){
	uint8_t i = 0;
	SystemInit();
	LPC_PINCON->PINSEL0 = 0x00000000;
	LPC_PINCON->PINSEL3 = 0x00000000;
	LPC_GPIO0->FIODIR = 0xfff;
	LPC_GPIO1->FIODIR &= (unsigned char)~(1<<button);
	uint32_t arr[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x100,0x200,0x400,0x800};
	while(1){
		
		if((LPC_GPIO1->FIOPIN & (1<<button))==1){
			
			i++;
			delay(1000);
			while((LPC_GPIO1->FIOPIN & (1<<button))==1);
		}
		LPC_GPIO0->FIOSET = 0xff;
		if(i>10){
			i=0;
			LPC_GPIO0->FIOCLR = 0xfff;
		}
	}
	
}

void delay(int ms){
	int i,j;
	for(i=0;i<1000;i++){
		for(j=0;j<ms;j++);
	}
}

