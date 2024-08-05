#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define PCF8574 0x20
#define WRITE   0
#define READ    1
#define SLAVE_ADDRESS_1  0x40
#define SLAVE_ADDRESS_2  0x42
char lcd = 0x00;


void I2C_Initialize( void );
void I2C_Start( void );
void I2C_WriteAddress(char address);
void I2C_WriteData(char data);
void I2C_Stop( void );

void PCF8574_Write(char x , char Address);
void PCF_Lcd_4Bit(char x,char Address);
void PCF_Lcd_Command(char cmd, char Address);
void PCF_Lcd_Data(char data, char Address);
void PCF_Lcd_Initialize( char Address);
void PCF_Write_String(const char *ptr, char Address);

int main() {
    
    I2C_Initialize();
    PCF_Lcd_Initialize(SLAVE_ADDRESS_1);
    PCF_Lcd_Initialize(SLAVE_ADDRESS_2);
    while(1) {
        
        PCF_Lcd_Command(0x80,SLAVE_ADDRESS_1);
        PCF_Write_String("Hello World!!",SLAVE_ADDRESS_1);
        _delay_ms(1000);
        
        PCF_Lcd_Command(0x80,SLAVE_ADDRESS_2);
        PCF_Write_String("How Are You!!",SLAVE_ADDRESS_2);
        _delay_ms(1000);
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

void PCF_Lcd_4Bit(char x,char Address) {
    
    char temp = 0x00;
    lcd &= 0x0f;
    temp = (x & 0xf0);
    lcd |= temp;
    lcd |= (0x04);
    PCF8574_Write(lcd,Address);
    _delay_ms(1);
    
    lcd &= ~(0x04);
    PCF8574_Write(lcd,Address);
    _delay_ms(1);
    
    temp = ((x << 4) & 0xf0);
    lcd &= 0x0f;
    lcd |= temp;
    lcd |= (0x04);
    PCF8574_Write(lcd,Address);
    _delay_ms(1);
    lcd &= ~(0x04);
    PCF8574_Write(lcd,Address);
    _delay_ms(1);
   
}

void PCF_Lcd_Command(char cmd,char Address) {
    
    lcd = 0x08;
    lcd &= ~0x01;
    PCF8574_Write(lcd,Address);
    PCF_Lcd_4Bit(cmd,Address);   
}

void PCF_Lcd_Data(char data, char address) {
 
    lcd |= 0x09;
    PCF8574_Write(lcd,address);
    PCF_Lcd_4Bit(data,address);
    
}

void PCF_Lcd_Initialize( char Address ) {

    switch(Address) {
        case SLAVE_ADDRESS_1:
            PCF_Lcd_Command(0x01,SLAVE_ADDRESS_1);
            PCF_Lcd_Command(0x02,SLAVE_ADDRESS_1);
            PCF_Lcd_Command(0x06,SLAVE_ADDRESS_1);
            PCF_Lcd_Command(0x28,SLAVE_ADDRESS_1);
            PCF_Lcd_Command(0x0c,SLAVE_ADDRESS_1);
        break;    
        case SLAVE_ADDRESS_2:
            PCF_Lcd_Command(0x01,SLAVE_ADDRESS_2);
            PCF_Lcd_Command(0x02,SLAVE_ADDRESS_2);
            PCF_Lcd_Command(0x06,SLAVE_ADDRESS_2);
            PCF_Lcd_Command(0x28,SLAVE_ADDRESS_2);
            PCF_Lcd_Command(0x0c,SLAVE_ADDRESS_2);
        break;    
    }
    

    
}

void PCF_Write_String(const char *ptr ,char Address) {
    
    while(*ptr) {
        
        PCF_Lcd_Data(*ptr++, Address);
    }
}