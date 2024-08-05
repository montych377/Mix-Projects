#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define WRITE 0
#define SLAVE_ADDRESS_1  0x40
#define SLAVE_ADDRESS_2  0x42

void I2C_Initialize( void );
void I2C_Start( void );
void I2C_WriteAddress(char address);
void I2C_WriteData(char data);
void I2C_Stop( void );

void PCF8574_Write(char x , char Address);


int main() {
    I2C_Initialize();
    while(1) {
        
    }
}

void I2C_Initialize( void ){
    
    TWBR = 2;
}
void I2C_Start( void ) {
    
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
    while((TWCR & (1<<TWINT)) == 0);
}
void I2C_WriteAddress(char address) {
    
    TWDR = address;
    TWCR = (1<<TWEN) | (1<<TWINT) ;
    while((TWCR & (1<<TWINT)) == 0);
}
void I2C_WriteData(char data) {
    
    TWDR = data;
    TWCR = (1<<TWEN) | (1<<TWINT) ;
    while((TWCR & (1<<TWINT)) == 0);
}

void I2C_Stop( void ) {
    
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTO);
}

void PCF8574_Write(char x,char Address){
    I2C_Start();
    _delay_ms(1);
    I2C_WriteAddress(Address | WRITE);
    _delay_ms(1);
    I2C_WriteData(x);
    _delay_ms(1);
    I2C_Stop();
    _delay_ms(1);

}
