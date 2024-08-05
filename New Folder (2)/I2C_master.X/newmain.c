#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

void I2C_Initialize(){
    
    TWBR = 2;
}

void i2c_start(){
    
    TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTA);
    while((TWCR & (1<<TWINT))==0);
}

void i2c_address(char address){
    TWDR = address;
    TWCR = (1<<TWEN)|(1<<TWINT);
    while((TWCR & (1<<TWINT))==0);
}
void i2c_data(char data){
    TWDR = data;
    TWCR = (1<<TWEN)|(1<<TWINT);
    while((TWCR & (1<<TWINT))==0);
}

void i2c_stop(){
    TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
    
}

int main(){
    
    I2C_Initialize();
    
    while(1) {
        
        i2c_start();
        _delay_ms(100);
        i2c_address(0x20);
        _delay_ms(100);
        i2c_data('A');
        _delay_ms(100);
        i2c_stop();
        _delay_ms(100);
    }
}

