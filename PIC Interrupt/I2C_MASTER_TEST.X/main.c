
#include "HEADER.h"
#include "I2C_MASTER.h"

#define WRITE 0
#define READ  1

uint8_t I2C_TxReceive(uint8_t Address,uint8_t data) {
    
        I2C_SendStartBit((Address) + WRITE);
        _delay_ms(10);
        I2C_WriteData(data);
        _delay_ms(10);
        I2C_SendStartBit((Address)  + READ);
        _delay_ms(10);
        char d = I2C_ReadACK();
        _delay_ms(10);
        I2C_SendStopBit();
        _delay_ms(10);
        return d;
}

uint8_t I2C_SendString(uint8_t Address,const char *msg) {
    uint8_t R_Data = 0;
    while(*msg != '\0') {
        R_Data = I2C_TxReceive(Address,*msg++);
    }
    return R_Data;
}
int main() { 
    
    DDRB = 0xFF;
    I2C_MasterInitialize();
    while(1) {
        
        PORTB = I2C_SendString(0x20,"HELLO");
        _delay_ms(100);
    }
}
