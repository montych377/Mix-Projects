#include "ADC.h"

void ADC_Initialize( void ){
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1);
}
uint16_t ADC_Read(uint8_t channel){
    ADMUX = (1<<REFS0)|channel;
    ADCSRA |= (1<<ADSC);
    while((ADCSRA & (1<<ADIF))==0);
    return ADC;
}
