#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>


#define I2C_ADDRESS  0x20
void I2c_init(){
    
    TWBR = 2;
}

void i2c_start(){
    
    TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTA);
    while((TWCR & (1<<TWINT))==0);
    
}
void i2c_write(char data){
    
    TWDR = data;
    TWCR = (1<<TWEN)|(1<<TWINT);
    while((TWCR & (1<<TWINT))==0);
}
void i2c_stop(){
    
    TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);

}
void lcd_send_command(char cmd,char address){
    i2c_start();
    i2c_write((address << 1) | 0x00);
    i2c_write((cmd & 0xF0) | 0x08);
    _delay_us(10);
    i2c_write(((cmd<<4) & 0xF0) | 0x00);
    _delay_us(100);
    
    i2c_stop();
}
void lcd_send_data(char data,char address){
    i2c_start();
    i2c_write((address << 1) | 0x00);
    i2c_write((data & 0xF0) | 0x09);
    _delay_us(10);
    i2c_write(((data<<4) & 0xF0) | 0x01);
    _delay_us(100);
    i2c_stop();
}

void lcd_init(char address){
    
    lcd_send_data(0x30,address);
    _delay_ms(5);
    lcd_send_data(0x30,address);
    _delay_ms(5);
    lcd_send_data(0x30,address);
    _delay_ms(5);
    
    lcd_send_command(0x02,address);
    _delay_ms(1);
    lcd_send_command(0x28,address);
    _delay_ms(1);
    lcd_send_command(0x0c,address);
    _delay_ms(1);
    lcd_send_command(0x01,address);
    _delay_ms(1);
}

int main(){
    
    I2c_init();
    
    lcd_init(I2C_ADDRESS);
    while(1){
        
        lcd_send_data('A',I2C_ADDRESS);
    }
}