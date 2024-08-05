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
#include<stdio.h>

volatile int adc_value=0;
volatile uint16_t counter1 = 0;
volatile uint16_t counter2 = 0;
volatile uint16_t counter3 = 0;

uint8_t ADC_Flag = 0;
 void LCD_Command(char cmd){
    
    PORTD = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    __delay_ms(2);
    PORTC &= ~0x04;
    __delay_ms(2);
}
void LCD_Data(char data){
    
    PORTD = data;
    PORTC |=  0x01;
    PORTC &= ~0x02;
    PORTC |=  0x04;
    __delay_ms(2);
    PORTC &= ~0x04;
    __delay_ms(2);
}

void LCD_Initialize(){
    
    TRISD = 0x00;
    TRISC = 0x00;
    
    LCD_Command(0x01);
    LCD_Command(0x02);
    LCD_Command(0x06);
    LCD_Command(0x38);
    LCD_Command(0x0C);
}
void LCD_String(const char *ptr){
    
    while(*ptr) {
        LCD_Data(*ptr++);
    }
}

void Timer2_Initialize(){
    
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 1;
    TMR2 = 132;
    PIE1bits.TMR2IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    T2CONbits.TMR2ON = 1;
}

void __interrupt() TMR2_ISR(){
    char arr[20] = {0};
    if(TMR2IF==1){
        ADCON0bits.CHS = 0b000;
        __delay_ms(100);
        GO_DONE = 1;
        while(GO_DONE ==1);
        int data = ADRESL|ADRESH<<8;
        GO_DONE = 0;
        sprintf(arr,"ADC : %04d",data);
        LCD_Command(0x80);
        LCD_String(arr);
        TMR2 = 132;
        TMR2IF = 0;
    }
    
    if(TMR1IF==1)
    {

        counter1++;
        counter2++;
        counter3++;

        TMR1L = 0x57;
        TMR1H = 0x9E;
        TMR1IF = 0;
    }
}

void Timer1_init(){
    
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1CKPS1 = 1;
    
    TMR1L = 0x57;
    TMR1H = 0x9E;
    
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    T1CONbits.TMR1ON = 1;
}

int main() {
    
    LCD_Initialize();
    TRISB = 0x00;
    PORTB = 0x00;
    Timer2_Initialize();
    Timer1_init();
    ADCON0bits.ADON = 1;
    ADCON1bits.ADFM = 1;
    
    while(1){
        
        if(counter1 == 1){
            
            PORTB^=0x01;
            counter1 = 0;
        }
        if(counter2 == 5){
            
            PORTB^=0x02;
            counter2 = 0;
        }
        if(counter3 == 10){
            
            PORTB^=0x04;
            counter3 = 0;
        } 
        
        
        
    }
}

