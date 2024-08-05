#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define WRITE 0
#define READ  1

#define EEPROM_WRITE_ADDR 0xA0
#define EEPROM_READ_ADDR 0xA1

#define TW_START                 0x08
#define TW_REP_START             0x10
#define TW_MT_SLA_ACK            0x18
#define TW_MR_SLA_ACK            0x40
#define TW_MT_SLA_NACK           0x20
#define TW_MR_SLA_NACK           0x48
#define TW_MT_DATA_ACK           0x28

void I2C_MasterInitialize(){
    
    TWSR = 0x00;
    TWBR = 2;
}
uint8_t I2C_SendStartBit(uint16_t Address)
{
    
    uint8_t STATUS;
    
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
    while(!(TWCR & (1<<TWINT)));
    _delay_ms(2);
    STATUS = TWSR & 0xF8;
    if((STATUS != TW_START) && (STATUS != TW_REP_START)) return 1;
    
    TWDR = Address;
    TWCR = (1<<TWEN) | (1<<TWINT);
    while(!(TWCR & (1<<TWINT)));
    _delay_ms(2);
    STATUS = TWSR & 0xF8;
    if((STATUS != TW_MT_SLA_ACK) && (STATUS != TW_MR_SLA_ACK)) return 1;
    _delay_ms(2);
    return 0;
}
uint8_t I2C_SendREPStartBit(uint16_t Address)
{
    
    return I2C_SendStartBit(Address);
}
void I2C_WaitStartBit(uint16_t Address) 
{
    
    uint8_t STATUS;
    
    while(1){
        TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
        while(!(TWCR & (1<<TWINT)));
        _delay_ms(2);
        STATUS = TWSR & 0xF8;
        if((STATUS != TW_START) && (STATUS != TW_REP_START)) continue;

        TWDR = Address;
        TWCR = (1<<TWEN) | (1<<TWINT);
        while(!(TWCR & (1<<TWINT)));
        _delay_ms(2);
        STATUS = TWSR & 0xF8;
        if((STATUS == TW_MT_SLA_NACK) && (STATUS == TW_MR_SLA_NACK)){

            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
            while((TWCR & (1<<TWSTO)));
            _delay_ms(2);
            continue;
        }
        break;
    }
}
void I2C_SendStopBit( void )
{
    
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    while((TWCR & (1<<TWSTO)));
    _delay_ms(2);
    
}
uint8_t I2C_WriteData(uint8_t data)
{
    
    uint8_t STATUS ;
    
    TWDR = data;
    TWCR = (1<<TWEN) | (1<<TWINT) ;
    while(!(TWCR & (1<<TWINT)));
    _delay_ms(2);
    STATUS = TWSR & 0xF8;
    if(STATUS != TW_MT_DATA_ACK) return 1;
    _delay_ms(2);
    return 0;
}
uint8_t I2C_ReadACK( void )
{
    
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
    _delay_ms(2);
    
}
uint8_t I2C_ReadNACK( void )
{
    
    TWCR = (1<<TWEN) | (1<<TWINT);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
    _delay_ms(2);
}




uint8_t EEPROM_WriteByte(uint16_t Address,uint8_t data)
{
    
    I2C_SendStartBit((EEPROM_WRITE_ADDR));
    _delay_ms(2);
    I2C_WriteData((uint8_t )(Address << 8));
    _delay_ms(2);
    I2C_WriteData((uint8_t )(Address & 0xFF));
    _delay_ms(2);
    I2C_WriteData(data);
    _delay_ms(2);
    I2C_SendStopBit();
    _delay_ms(2);
    return 0;
}

uint16_t EEPROM_ReadByte(uint16_t Address)
{
    
    I2C_WaitStartBit((EEPROM_WRITE_ADDR));
    _delay_ms(2);
    I2C_WriteData((uint8_t )(Address << 8));
    _delay_ms(2);
    I2C_WriteData((uint8_t )(Address & 0xFF));
    _delay_ms(2);
    I2C_SendStopBit();
    _delay_ms(2);
    I2C_SendREPStartBit((EEPROM_READ_ADDR));
    _delay_ms(2);

    uint8_t LSB = I2C_ReadACK();
    _delay_ms(2);
    I2C_SendStopBit();
    _delay_ms(2);
    
    return LSB;
}

void EEPROM_WriteString(uint16_t Address ,const char *ptr) {
    
    while(*ptr) {
        
        EEPROM_WriteByte(Address,*ptr++);
    }
}
int main() {
    char arr[10];
    DDRB = 0xFF; 
    I2C_MasterInitialize();

    
    while (1) {
  
        EEPROM_WriteByte(0x0000,0x01);
        _delay_ms(1000);
        PORTB = EEPROM_ReadByte(0x0000);
        _delay_ms(1000);
        
        EEPROM_WriteByte(0x0001,0x02);
        _delay_ms(1000);
        PORTB = EEPROM_ReadByte(0x0000);
        _delay_ms(1000);
        
        EEPROM_WriteByte(0x0003,0x04);
        _delay_ms(1000);
        PORTB = EEPROM_ReadByte(0x0000);
        _delay_ms(1000);
 
   
       
    }

}
