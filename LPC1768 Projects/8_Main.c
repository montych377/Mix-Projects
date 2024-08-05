#include <LPC17xx.h>

void Delay(int ms);
int main( void )
{
	int i=0 ,j=0;
	LPC_GPIO0->FIODIR = 0xff;
	LPC_GPIO1->FIODIR = (1<<0)|(1<<1);
	unsigned int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	
	while(1)
	{
		for(i=0;i<10;i++){
			for(j=0;j<10;j++){
				
				LPC_GPIO1->FIOSET = (1<<0);
				LPC_GPIO1->FIOCLR = (1<<1);
				LPC_GPIO0->FIOPIN = arr[j];
				Delay(250);
				
				LPC_GPIO1->FIOCLR = (1<<0);
				LPC_GPIO1->FIOSET = (1<<1);
				LPC_GPIO0->FIOPIN = arr[i];
				Delay(250);
				
			}
		}
			
	}	
}

void Delay(int ms){
	
	int i,j;
	for(i=0;i<1000;i++){
		for(j=0;j<ms;j++);
	}
}
