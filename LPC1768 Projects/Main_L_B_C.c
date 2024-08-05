#include <LPC17xx.h>

#define button 0
void delay(int ms);

int main ( void ){
	
	uint8_t i = 0;

	LPC_GPIO1->FIODIR = (1<<button);
	
	LPC_GPIO2->FIODIR = 0xff;
	uint16_t arr[]={0x00,0x01,0x02,0x04,0x08};
	while(1){
		
		if((LPC_GPIO1->FIOPIN & (1<<button)) == 1){
			i++;
			delay(1000);
			while((LPC_GPIO1->FIOPIN & (1<<button)) == 1);
		}
		LPC_GPIO2->FIOSET = arr[i];
		if(i>5){
			i=0;
			LPC_GPIO2->FIOPIN = 0x00;
		}
	}
	
}

void delay(int ms){
	
	int i,j;
	for(i=0;i<1000;i++){
		for(j=0;j<ms;j++);
	}
}

