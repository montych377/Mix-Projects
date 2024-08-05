/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 14 June, 2023, 12:32 AM
 */

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

void main(void) {
    TRISD = 0x00;
    char arr[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
    while(1){
        for(int i=0;i<8;i++){
            PORTD = arr[i];
            __delay_ms(50);
        }
    }
    return;
}
