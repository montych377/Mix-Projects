#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void MAX7219_Write(uint8_t address,uint8_t data);

void Segment_Update(uint32_t n);
int main() {
    
    DDRB |= (1<<PB2)|(1<<PB3)|(1<<PB5);
    DDRB &= ~(1<<PB4);
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
    
    MAX7219_Write(0x09,0xFF);
    MAX7219_Write(0x0a,0x0F);
    MAX7219_Write(0x0b,0x07);
    MAX7219_Write(0x0c,0x01);
    while(1) {
        //for(uint32_t i=0;i<100000000;i++){
            Segment_Update(23678);
            _delay_ms(1000);
        //}
    }
}

void MAX7219_Write(uint8_t address,uint8_t data) {
    
    PORTB &= ~(1<<PB2);
    
    SPDR = address;
    while((SPSR & (1<<SPIF))==0);
    
    SPDR = data;
    while((SPSR & (1<<SPIF))==0);
    
    PORTB |= (1<<PB2);
    
    _delay_ms(1);
}

void Segment_Update(uint32_t n) {
    
    uint8_t n1 = n/10000000;
    uint8_t n2 = (n/1000000)%10;
    uint8_t n3 = (n/100000)%10;
    uint8_t n4 = (n/10000)%10;
    uint8_t n5 = (n/1000)%10;
    uint8_t n6 = (n/100)%10;
    uint8_t n7 = (n/10)%10;
    uint8_t n8 = n%10;
    
    MAX7219_Write(1,n1);
    MAX7219_Write(2,n2);
    MAX7219_Write(3,n3);
    MAX7219_Write(4,n4);
    MAX7219_Write(5,n5);
    MAX7219_Write(6,n6);
    MAX7219_Write(7,n7);
    MAX7219_Write(8,n8);
}
