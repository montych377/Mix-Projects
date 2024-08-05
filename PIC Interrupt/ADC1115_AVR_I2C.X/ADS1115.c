#include "ADS1115.h"
#include "I2C_MASTER.h"

uint8_t ADS1115_Write(uint8_t Address, uint8_t REG,uint16_t data){
    
    I2C_SendStartBit((Address<<1) + WRITE);
    I2C_WriteData((uint8_t )REG);
    I2C_WriteData((uint8_t )(data >> 8));
    I2C_WriteData((uint8_t )(data & 0xFF));
    I2C_SendStopBit();
    return 0;
}

uint16_t ADS1115_Read(uint8_t Address,uint8_t REG) {
    
    I2C_WaitStartBit((Address<<1)+WRITE);
    I2C_WriteData(REG);
    I2C_SendStopBit();
    
    I2C_SendREPStartBit((Address<<1)+READ);
    uint8_t MSB = I2C_ReadACK();
    uint8_t LSB = I2C_ReadNACK();
    I2C_SendStopBit();
    
    uint16_t data = (MSB << 8 | LSB);
    
    return data;
}
uint16_t ADS1115_ReadMultiChannel(uint8_t Address,uint8_t REG,uint8_t channel) {
    
        
    if(channel == 0){
        
        ADS1115_Write(ADS1115_ADDR_GND,0x01,ADS1115_MUX_AIN0_GND);
        _delay_ms(10);
        uint16_t data0 = ADS1115_Read(ADS1115_ADDR_GND,0x00);
        return data0;
    
    }  
    if(channel == 1){
        ADS1115_Write(ADS1115_ADDR_GND,0x01,ADS1115_MUX_AIN1_GND);
        _delay_ms(10);
        uint16_t data1 = ADS1115_Read(ADS1115_ADDR_GND,0x00);
        return data1;
      
    }  
    if(channel == 2){
        ADS1115_Write(ADS1115_ADDR_GND,0x01,ADS1115_MUX_AIN2_GND);
        _delay_ms(10);
        uint16_t data2 = ADS1115_Read(ADS1115_ADDR_GND,0x00);
        return data2;
    }
    if(channel == 3) {
        ADS1115_Write(ADS1115_ADDR_GND,0x01,ADS1115_MUX_AIN3_GND);
        _delay_ms(10);
        uint16_t data3 = ADS1115_Read(ADS1115_ADDR_GND,0x00);
        return data3;
    }
    return 0;
}