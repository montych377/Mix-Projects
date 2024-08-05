#define _XTAL_FREQ 8000000

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

void UART_Initialize(long baud);
void UART_TransmitData(char data);
char UART_ReceiveData(void);
void UART_WriteString(const char *ptr);

void LCD_WriteCommand(char cmd);
void LCD_WriteData(char data);
void LCD_Initialize(void);
void LCD_WriteString(const char *ptr);

int main( void ) {
    char arr[15] = {0};
    TRISD = 0x00;
    PORTD = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;
    UART_Initialize(9600);
    LCD_Initialize();
//    LCD_WriteCommand(0x80);
//    LCD_WriteString("Receive->");
    while(1) {
        
        for(int i=0;i<6;i++){
            arr[i] = UART_ReceiveData();
        }
        
        UART_WriteString(arr);
        __delay_ms(500);
//        LCD_WriteCommand(0x8A);
//        LCD_WriteString(arr);
        
    }
}


void UART_Initialize(long baud){
    
    SPBRG = (((_XTAL_FREQ)/(16*baud))-1);
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;
}
void UART_TransmitData(char data){
    TXREG = data;
    while(!TXIF);
}
char UART_ReceiveData(void){
    
    if(OERR){
        CREN = 0;
        CREN = 1;
    }
    while(!RCIF);
    return RCREG;
}
void UART_WriteString(const char *ptr){
    
    while(*ptr){
        
        UART_TransmitData(*ptr++);
    }
}

void LCD_WriteCommand(char cmd){
    
    PORTD = cmd;
    PORTB &= ~0x01;
    PORTB &= ~0x02;
    PORTB |=  0x04;
    __delay_ms(2);
    PORTB &= ~0x04;
    __delay_ms(2);
}
void LCD_WriteData(char data){
    
    PORTD = data;
    PORTB |=  0x01;
    PORTB &= ~0x02;
    PORTB |=  0x04;
    __delay_ms(2);
    PORTB &= ~0x04;
    __delay_ms(2);
    
}
void LCD_Initialize(void){
    LCD_WriteCommand(0x01);
    LCD_WriteCommand(0x02);
    LCD_WriteCommand(0x06);
    LCD_WriteCommand(0x38);
    LCD_WriteCommand(0x0C);
}
void LCD_WriteString(const char *ptr){
    
    while(*ptr){
        
        LCD_WriteData(*ptr++);
    }
}