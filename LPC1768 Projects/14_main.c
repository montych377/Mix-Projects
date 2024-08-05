#include <LPC17xx.h>

void delay(int ms);
int main( void ){
	LPC_GPIO2->FIODIR = 0xff;
	LPC_GPIO0->FIODIR = 0xff;
	LPC_GPIO1->FIODIR &= ~0x01;
	uint32_t arr[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	uint32_t i=7;
	while(1){
		if((LPC_GPIO1->FIOPIN & 0x01)==0x01){
			i--;
			delay(1000);
			while((LPC_GPIO1->FIOPIN & 0x01)==0x01);
		}
	  LPC_GPIO0->FIOPIN = arr[i];
		if(i<=0){
			i=7;
		}
	  
	}
}

void delay(int ms){
	
	uint32_t i,j;
	for(i=0;i<1000;i++){
		for(j=0;j<ms;j++);
	}
}