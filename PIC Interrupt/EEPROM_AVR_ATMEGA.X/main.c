
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

typedef struct
{
    uint8_t eepromaddress;
    uint16_t pageaddress;
    uint8_t data;
}Typedef_EEPROM_Config;

void I2C_init( void );
void I2C_Start( void );
void I2C_RepStart( void );
void I2C_WriteAddress(uint8_t Address);
void I2C_WriteData(uint8_t Data);
uint8_t I2C_ReadACK( void );
uint8_t I2C_ReadNACK( void );
void I2C_Stop( void );

int main()
{
    while(1) 
    {
        
    }
}

void I2C_init( void )
{
    TWBR = 2;
}
void I2C_Start( void )
{
    TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
    while((TWCR & (1<<TWINT)) == 0 );
}
void I2C_RepStart( void )
{
    
}
void I2C_WriteAddress(uint8_t Address);
void I2C_WriteData(uint8_t Data);
uint8_t I2C_ReadACK( void );
uint8_t I2C_ReadNACK( void );
void I2C_Stop( void );