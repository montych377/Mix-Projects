#include <LPC17xx.h>

#define LED    0
#define BUTTON 0

int main( void ){
	
	LPC_GPIO2->FIODIR = (1<<LED);
	LPC_GPIO1->FIODIR &= ~(1<<BUTTON);
	while(1){
		
		if((LPC_GPIO1->FIOPIN & (1<<BUTTON))==1){
			
			LPC_GPIO2->FIOSET = (1<<LED);
		
		}
		else{
			
			LPC_GPIO2->FIOCLR = (1<<LED);
		}
	
	}
}
	
