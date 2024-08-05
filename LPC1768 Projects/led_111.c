#include <LPC17xx.h>


void Delay(int ms);

int main( void ) {
	int arr[]={0,1,2,3,4,5,6,7};
	LPC_GPIO2->FIODIR = 0xff;
	int i=0;
	while(1) {
	
	 for(i=0;i<8;i++){
		 
		 LPC_GPIO2->FIOSET = (1<<arr[i]);
		 Delay(100);
	 }
	 
	 for(i=7;i>=0;i--){
		 
		 LPC_GPIO2->FIOCLR = (1<<arr[i]);
		 Delay(100);
	 }
	 
	 
	  for(i=7;i>=0;i--){
		 
		 LPC_GPIO2->FIOSET = (1<<arr[i]);
		 Delay(100);
	 }
	 
	 for(i=0;i<8;i++){
		 
		 LPC_GPIO2->FIOCLR = (1<<arr[i]);
		 Delay(100);
	 }
	}
	
}
/*

1<<LED1

1<<0

0b00000001<<0

0b00000001

0x01








*/
void Delay(int ms){
	
	uint16_t i,j;
	for(i=0;i<ms;i++){
		
		for(j=0;j<5000;j++);
	}	
}

