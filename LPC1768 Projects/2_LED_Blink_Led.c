#include <LPC17xx.h>

void delay(int ms);
int main( void ) {
	
	LPC_GPIO2->FIODIR = 0x1;
	
	while(1){
		LPC_GPIO2->FIOSET = 0x1;
		delay(1000);
		LPC_GPIO2->FIOCLR = 0x1;
		delay(1000);
		
	}
	return 0;
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<1000;i++){
		for(j=0;j<ms;j++);
	}
}