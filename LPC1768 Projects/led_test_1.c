#include <LPC17xx.h>

int main( void ) {
	uint32_t i=0;
	LPC_GPIO2->FIODIR = 0xff;
	
	while(1) {
		
			LPC_GPIO2->FIOSET = 0xff;
		  for(i=0;i<5000000;i++);
			LPC_GPIO2->FIOSET = 0xff;
		  for(i=0;i<5000000;i++);
	}
}

