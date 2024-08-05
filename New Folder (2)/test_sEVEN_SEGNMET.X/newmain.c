#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

const uint8_t SEGMENTPATTERNS[] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

//void SegmentUpdate(uint16_t count){
//    uint16_t ones = count % 1;
//    count /=1;
//    uint16_t tens = count % 10;
//    count /=10;
//    uint16_t hunderds = count % 10;
//    count /=10;
//    uint16_t thousands = count % 10;
//    count /=10;
//    
//    PORTB = SEGMENTPATTERNS[ones];
//    _delay_ms(1);
//    PORTD = 0x0e;
//    
//    PORTB = SEGMENTPATTERNS[tens];
//    _delay_ms(1);
//    PORTD = 0x0d;
//    
//    PORTB = SEGMENTPATTERNS[hunderds];
//    _delay_ms(1);
//    PORTD = 0x0b;
//    
//    PORTB = SEGMENTPATTERNS[thousands];
//    _delay_ms(1);
//    PORTD = 0x07;
//}

void ADC_init(){
    
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1);
}

uint16_t ADc_Read(uint16_t channel){
    ADMUX = (1<<REFS0)|(channel);
    ADCSRA |= (1<<ADSC);
    while((ADCSRA & (1<<ADIF))==0);
    return ADC;
}
int main(){
    
    DDRB = 0xff;
    DDRD = 0xff;
    ADC_init();
    while(1){
        uint16_t adc_value = ADc_Read(0);
        uint8_t thousands = adc_value/1000;
        uint8_t hunderds  = (adc_value/100) % 10;
        uint8_t tens = (adc_value/10) % 10;
        uint8_t ones = adc_value % 10;
        
        for(uint8_t i = 0 ;i < 20 ; i++) {
            
            PORTB = SEGMENTPATTERNS[thousands];
            _delay_ms(5);
            PORTD = 0x0d;
            
            PORTB = SEGMENTPATTERNS[hunderds];
            _delay_ms(5);
            PORTD = 0x07;
            
            PORTB = SEGMENTPATTERNS[tens];
            _delay_ms(5);
            PORTD = 0x0b;
            
            PORTB = SEGMENTPATTERNS[ones];
            _delay_ms(5);
            PORTD = 0x0e;
        } 
   
    }
}