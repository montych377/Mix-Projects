#define F_CPU 8000000UL
#include <avr/io.h>


void Timer_0_delay(int ms){
    
    int i=0;
    
    for(i=0;i<ms;i++){
        
        TCNT0 = 225;
        TCCR0 = (1<<CS02);
        while((TIFR & (1<<TOV0))==0);
        TCCR0 = 0;
        TIFR |= (1<<TOV0);
    }
}

int main() {
    
    DDRD = 0xff;
    
    while(1){
        
        PORTD = 0xff;
        Timer_0_delay(1000);
        PORTD = 0x00;
        Timer_0_delay(100);
    }
}
