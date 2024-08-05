
#define _XTAL_FREQ 8000000UL

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define BAUDRATE 9600
volatile unsigned char data = 'A';
volatile unsigned char arr[5] ={0};
volatile uint8_t counter =0;


 void LCD_Command(char cmd){
    
    PORTD = cmd;
    PORTB &= ~0x01;
    PORTB &= ~0x02;
    PORTB |=  0x04;
    __delay_ms(2);
    PORTB &= ~0x04;
    __delay_ms(2);
}
void LCD_Data(char data){
    
    PORTD = data;
    PORTB |=  0x01;
    PORTB &= ~0x02;
    PORTB |=  0x04;
    __delay_ms(2);
    PORTB &= ~0x04;
    __delay_ms(2);
}

void LCD_Initialize(){
    
    TRISD = 0x00;
    TRISB = 0x00;
    
    LCD_Command(0x01);
    LCD_Command(0x02);
    LCD_Command(0x06);
    LCD_Command(0x38);
    LCD_Command(0x0C);
}
void LCD_String(volatile unsigned char *ptr){
    
    while(*ptr) {
        LCD_Data(*ptr++);
    }
}


void UART_Initializer(unsigned long baud){
    
    SPBRG = (((_XTAL_FREQ)/(16*baud))-1);
    TXSTA = 0x24;
    RCSTA = 0x90;
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
   
}

void __interrupt() UART_TX() {
    
    
    if(RCIF == 1){
        
        if(OERR){
            
            CREN = 0;
            CREN= 1;
        }
        
        arr[counter] = RCREG;
        counter++;
        if(counter == 5){
            
            counter = 0;
        }
        LCD_Command(0x80);
        LCD_String(arr);
        RCIF = 0;
        
    }
    
}

int main(){
    LCD_Initialize();
    UART_Initializer(BAUDRATE);
    
    while(1) ;
}
