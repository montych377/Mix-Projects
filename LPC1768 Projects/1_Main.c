#include <reg52.h>

//sbit LED0 = P1^0;
//sbit LED1 = P1^1;
//sbit LED2 = P1^2;
//sbit LED3 = P1^3;
//sbit LED4 = P1^4;
//sbit LED5 = P1^5;
//sbit LED6 = P1^6;
//sbit LED7 = P1^7;


void Delay(int ms){
	int i,j;
	for(i=0;i<ms;i++){
		for(j=0;j<1275;j++){
			
		}
	}
	
}
int main(){
	unsigned int i=0;
	while(1){
		for(i=0;i<8;i++){
			
			P1 &= ~(1<<i);
			Delay(100);
		}
	}
}