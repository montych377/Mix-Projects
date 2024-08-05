#include <LPC17xx.h>

void Delay(int ms);

#define button 0
#define BUTTON1 1
int main( void )
{
	int i=0;
	LPC_GPIO0->FIODIR = 0xff;
	LPC_GPIO1->FIODIR = (1<<button)|(1<<BUTTON1);
	unsigned int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	
	while(1)
	{
		
		if((LPC_GPIO1->FIOPIN & (1<<button)) == 0x01){
			i--;
			Delay(1000);
			while((LPC_GPIO1->FIOPIN & (1<<button)) == 0x011);
		 }		
			if(i<0){
				i=9;
			}
			
			if((LPC_GPIO1->FIOPIN & (1<<BUTTON1)) == 0x02){
				i++;
				Delay(1000);
				while((LPC_GPIO1->FIOPIN & (1<<BUTTON1)) == 0x02);
		  }		
			LPC_GPIO0->FIOSET = arr[i];
		  Delay(1000);
		  LPC_GPIO0->FIOCLR = arr[i];
			if(i>=10){
				i=0;
			}
	}	
}

void Delay(int ms){
	
	int i,j;
	for(i=0;i<1000;i++){
		for(j=0;j<ms;j++);
	}
}

