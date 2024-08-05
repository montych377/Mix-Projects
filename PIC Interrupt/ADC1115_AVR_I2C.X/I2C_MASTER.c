
#include "I2C_MASTER.h"

void I2C_MasterInitialize(){
    
    TWSR = 0x00;
    TWBR = 2;
}
uint8_t I2C_SendStartBit(uint8_t Address) {
    
    uint8_t STATUS;
    
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
    while(!(TWCR & (1<<TWINT)));
    
    STATUS = TWSR & 0xF8;
    if((STATUS != TW_START) && (STATUS != TW_REP_START)) return 1;
    
    TWDR = Address;
    TWCR = (1<<TWEN) | (1<<TWINT);
    while(!(TWCR & (1<<TWINT)));
    
    STATUS = TWSR & 0xF8;
    if((STATUS != TW_MT_SLA_ACK) && (STATUS != TW_MR_SLA_ACK)) return 1;
    
    return 0;
}
uint8_t I2C_SendREPStartBit(uint8_t Address){
    
    return I2C_SendStartBit(Address);
}
void I2C_WaitStartBit(uint8_t Address) {
    
    uint8_t STATUS;
    
    while(1){
        TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
        while(!(TWCR & (1<<TWINT)));

        STATUS = TWSR & 0xF8;
        if((STATUS != TW_START) && (STATUS != TW_REP_START)) continue;

        TWDR = Address;
        TWCR = (1<<TWEN) | (1<<TWINT);
        while(!(TWCR & (1<<TWINT)));

        STATUS = TWSR & 0xF8;
        if((STATUS == TW_MT_SLA_NACK) && (STATUS == TW_MR_SLA_NACK)){

            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
            while((TWCR & (1<<TWSTO)));
            continue;
        }
        break;
    }
}
void I2C_SendStopBit( void ) {
    
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    while((TWCR & (1<<TWSTO)));
    
}
uint8_t I2C_WriteData(uint8_t data) {
    
    uint8_t STATUS ;
    
    TWDR = data;
    TWCR = (1<<TWEN) | (1<<TWINT) ;
    while(!(TWCR & (1<<TWINT)));
    
    STATUS = TWSR & 0xF8;
    if(STATUS != TW_MT_DATA_ACK) return 1;
    
    return 0;
}
uint8_t I2C_ReadACK( void ) {
    
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
    
}
uint8_t I2C_ReadNACK( void ) {
    
    TWCR = (1<<TWEN) | (1<<TWINT);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}