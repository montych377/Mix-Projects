#define F_CPU 8000000UL
#include <avr/io.h>


void Timer_1_delay(int ms){
    
    for(int i=0;i<ms;i++){
        
        TCNT1 = 65528;
        TCCR1A = 0;
        TCCR1B = (1<<CS10)|(1<<CS12);
        while((TIFR &(1<<TOV1))==0);
        TCNT1 = 0;
        TIFR |= (1<<TOV1);
        
    }
    
}

int main() {
    DDRD = 0xff;
    unsigned int x= 5;
    DDRC &= ~(1<<1);
    PORTC = 0x02;
    while(1) {
        if((PINC & (1<<1))==0) {
            
            PORTD = 0x66;
            Timer_1_delay(x);
            PORTD = 0xcc;
            Timer_1_delay(x);
            PORTD = 0x99;
            Timer_1_delay(x);
            PORTD = 0x33;
            Timer_1_delay(x);
        }
        else
            PORTD = 0x66;
            Timer_1_delay(x);
            PORTD = 0x33;
            Timer_1_delay(x);
            PORTD = 0x99;
            Timer_1_delay(x);
            PORTD = 0xcc;
            Timer_1_delay(x);
        {
            
        }
    }
}
