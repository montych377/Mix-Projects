#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void i2c_init_slave(char address){
    
    TWAR = address;
}

void i2c_addresss_match(){
    
    while((TWSR & 0xf8) != 0x60){
        TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
        while((TWCR & (1<<TWINT))==0);
    }
}

char i2c_receive(){
    TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
    while((TWCR & (1<<TWINT))==0);
    while((TWSR & 0xf8) != 0x80);
    return TWDR;
}

int main(){
    DDRD = 0xff;
    i2c_init_slave(0x20);
    while(1){
        i2c_addresss_match();
        _delay_ms(100);
        PORTD = i2c_receive();
    }
}