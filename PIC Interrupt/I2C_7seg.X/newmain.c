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
void PCF_SegmentUpdate(uint16_t n);

uint8_t arr[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x07,0x7d,0x7f,0x6f};

int main() {
    DDRD = 0xff;
    uint16_t counter = 0;
    uint16_t loop_counter = 0;
    I2C_Initialize();
    while(1) {
        PCF_SegmentUpdate(counter);
        loop_counter++;
        if(loop_counter == 10){
            
            counter++;
            if(counter == 1000){
                
                counter = 0;
            }
            
            loop_counter = 0;
        }
    }
}

void PCF_SegmentUpdate(uint16_t n) {
    uint16_t thou = (n/1000);
    uint16_t hund = (n/100)%10;
    uint16_t tens = (n/10)%10;
    uint16_t ones = n%10;
    
//    PCF8574_Write(arr[thou],SLAVE_ADDRESS_1);
//    PCF8574_Write(0x00,SLAVE_ADDRESS_1);
//    PCF8574_Write(0xfe,SLAVE_ADDRESS_2);
//    _delay_ms(1);
    
    PCF8574_Write(arr[hund],SLAVE_ADDRESS_1);
    PCF8574_Write(0x00,SLAVE_ADDRESS_1);
    PCF8574_Write(0xf7,SLAVE_ADDRESS_2);
    //PORTD = 0xFd;
    _delay_ms(1);
    
    PCF8574_Write(arr[tens],SLAVE_ADDRESS_1);
    PCF8574_Write(0x00,SLAVE_ADDRESS_1);
    PCF8574_Write(0xfd,SLAVE_ADDRESS_2);
    //PORTD = 0xfb;
    _delay_ms(1);
    
    PCF8574_Write(arr[ones],SLAVE_ADDRESS_1);
    PCF8574_Write(0x00,SLAVE_ADDRESS_1);
    PCF8574_Write(0xfb,SLAVE_ADDRESS_2);
    //PORTD = 0xf7;
    _delay_ms(1);
    
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
