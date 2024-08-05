#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define MOSI  3
#define MISO  4
#define SCK   5
#define SS    2

void LCD_cmd(char cmd){
    
    PORTD = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    _delay_ms(3);
    PORTC &= ~0x04;
    _delay_ms(3);
}

void LCD_data(char data){
    
    PORTD = data;
    PORTC |=  0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    _delay_ms(3);
    PORTC &= ~0x04;
    _delay_ms(3);
}

void lcd_init(){
    
    LCD_cmd(0x01);
    LCD_cmd(0x02);
    LCD_cmd(0x06);
    LCD_cmd(0x38);
    LCD_cmd(0x0c);
}

void lcd_string(const char *ptr){
    
    while(*ptr != '\0'){
        LCD_data(*ptr++);
    }
}
void SPI_Initialize() {
    
    DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
    
}

void SPI_Transmit(char data) {
    
    SPDR = data;
    while((SPSR & (1<<SPIF))==0);
}

char SPI_Receive(void) {
    
    while((SPSR & (1<<SPIF))==0);
    char d = SPDR;
    return d;
}

void SPI_String(const char *ptr){
    
    while(*ptr != '\0'){
        
        SPI_Transmit(*ptr++);
    }
}
int main() {
    char arr[10] = {0};
    DDRD = 0xff;
    DDRC = 0x07;
    SPI_Initialize();
    lcd_init();
    LCD_cmd(0x80);
    lcd_string("Transmit->");
    LCD_cmd(0x8A);
    lcd_string("HELLO");
    while(1) {
        
        SPI_String("HELLO");
        _delay_ms(1000);
        for(int i=0;i<5;i++){
            arr[i] = SPI_Receive();
        }
        _delay_ms(1000);
        LCD_cmd(0xC0);
        lcd_string("Transmit->");
        LCD_cmd(0xCA);
        lcd_string(arr);
    }
}
