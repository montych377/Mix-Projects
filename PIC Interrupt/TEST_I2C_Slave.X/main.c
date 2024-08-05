#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SLAVE_ADDRESS 0x20
#define READ  1
#define WRITE  0

void I2C_Initialize( uint8_t Address) {
    
    TWAR = Address;
    TWCR = (1<<TWEN);
}

void I2C_READAck() {
    
    TWCR = (1<<TWINT)| (1<<TWEN) | (1<<TWEA);
    while(!(TWCR & (1<<TWINT)));
} 
void I2C_READNack() {
    
    TWCR = (1<<TWINT)| (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
} 

uint8_t  I2C_ReadData() {
    
    while((TWSR & 0xF8) != 0x60) {
        
        I2C_READAck();
        
    }
    while((TWSR & 0xF8) != 0x80){
        
        I2C_READAck();
    }
    uint8_t ReceiveData = TWDR;

    return ReceiveData;
}


void I2C_Write(uint8_t data) {
    
    TWDR = data;
    TWCR = (1<<TWEN) | (1<<TWINT) ;
    while(!(TWCR & (1<<TWINT)));
}
uint8_t  I2C_ReceiveTx(uint8_t data){
        char d = I2C_ReadData();
        while((TWSR & 0xF8) != 0xA8) {
            
            while(!(TWCR & (1<<TWINT)));
        }
        I2C_Write(data);
        return d;
}

void LCD_Command(char cmd) {
    
    PORTD = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    _delay_ms(2);
    PORTC &= ~0x04;
    _delay_ms(2);
}
void LCD_Data(char data) {
    
    PORTD = data;
    PORTC |=  0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    _delay_ms(2);
    PORTC &= ~0x04;
    _delay_ms(2);
}
void LCD_Initialize( void ) {
    
    DDRD = 0xFF;
    DDRC = 0x0F;
    LCD_Command(0x01);
    LCD_Command(0x02);
    LCD_Command(0x06);
    LCD_Command(0x38);
    LCD_Command(0x0C);
}
void LCD_String(const char *ptr) {
    
    while(*ptr != '\0') {
        
        LCD_Data(*ptr++);
    }
}


int main() { 
    //LCD_Initialize();
    I2C_Initialize(0x20);
    
    while(1) {
        
        char data = I2C_ReceiveTx(0x01); 
        _delay_ms(10);
//        LCD_Command(0x80);
//        LCD_Data(data);
  

    }
}