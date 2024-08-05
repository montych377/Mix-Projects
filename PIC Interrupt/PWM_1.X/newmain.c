#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

void PWM_Initialize(){
    
    TCCR2 |= (1<<WGM20)|(1<<COM21)|(1<<CS20)|(1<<CS21);
    OCR2 = 0;
}
int main() {
    
    DDRB |= (1<<PB3);
    PWM_Initialize();
    
    while(1) {
        
        for(int i=0;i<255;i++){
            OCR2 = i;
            _delay_ms(10);
        }
        
        for(int i=255;i>=0;i--){
            OCR2 = i;
            _delay_ms(10);
        }
    }
    
}
