#include <LPC17xx.h>

void delay(int ms);

int main( void ){
	
	LPC_PINCON->PINSEL0 &= (unsigned char)~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7));
	LPC_GPIO0->FIODIR |= (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9)|(1<<10);
	unsigned int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
	while(1){
		int i;
		for( i=0;i<11;i++){
			LPC_GPIO0->FIOPIN = 1<<i;
			delay(100);
		}
		
		for( i=10;i>=0;i--){
			LPC_GPIO0->FIOPIN = 1<<i;
			delay(100);
		}
		
			/*LPC_GPIO2->FIOSET = (1<<0);
			delay(1000);
		  LPC_GPIO2->FIOCLR = (1<<0);
			delay(1000);
		
			LPC_GPIO2->FIOSET = (1<<1);
			delay(1000);
		  LPC_GPIO2->FIOCLR = (1<<1);
			delay(1000);
		
	  	LPC_GPIO2->FIOSET = (1<<2);
			delay(1000);
		  LPC_GPIO2->FIOCLR = (1<<2);
			delay(1000);
		
			LPC_GPIO2->FIOSET = (1<<3);
			delay(1000);
		  LPC_GPIO2->FIOCLR = (1<<3);
			delay(1000);
		
			LPC_GPIO2->FIOSET = (1<<3);
			delay(1000);
		  LPC_GPIO2->FIOCLR = (1<<3);
			delay(1000);
		
			LPC_GPIO2->FIOSET = (1<<2);
			delay(1000);
		  LPC_GPIO2->FIOCLR = (1<<2);
			delay(1000);
		
	  	LPC_GPIO2->FIOSET = (1<<1);
			delay(1000);
		  LPC_GPIO2->FIOCLR = (1<<1);
			delay(1000);
		
			LPC_GPIO2->FIOSET = (1<<0);
			delay(1000);
		  LPC_GPIO2->FIOCLR = (1<<0);
			delay(1000);*/
	}
}

void delay(int ms){
	
	int i,j;
	for(i=0;i<1000;i++){
		for(j=0;j<ms;j++);
	}
}

