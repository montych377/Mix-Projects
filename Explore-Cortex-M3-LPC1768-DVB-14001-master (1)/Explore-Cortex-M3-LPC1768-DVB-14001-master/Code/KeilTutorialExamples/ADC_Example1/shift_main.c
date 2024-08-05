#include <reg52.h>

sbit LATCH = P1^0;
sbit DATA = P1^1;
sbit CLOCK = P1^2;

void delay_ms(int ms) {
	
	unsigned int i,j;
	
	for(i=0;i<ms;i++){
		for(j=0;j<125;j++){
		}
	}
}

void latchdata(){
	
	LATCH = 0;
	delay_ms(1);
	LATCH = 1;;
	delay_ms(1);
}

void SendData(unsigned char xbyte) {
	unsigned char i=0;
	for(i=0;i<8;i++) {
		
		DATA = (xbyte>>i) & 0x01;
		CLOCK = 1;
		delay_ms(1);
		CLOCK = 0;
		delay_ms(1);
	}
	
	latchdata();
}


int main () {
	
	unsigned char datavalue = 0x55;
	
	while(1) {
		
		SendData(datavalue);
		
		datavalue = ~datavalue;
		
		delay_ms(1000);
	}
}