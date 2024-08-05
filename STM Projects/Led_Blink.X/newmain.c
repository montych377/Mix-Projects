/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 4 April, 2023, 2:40 AM
 */



#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>

int main(void) {
    
    DDRD = 0xff;
    while(1){
        PORTD = 0xff;
        _delay_ms(1000);
        PORTD = 0x00;
        _delay_ms(1000);
    }
    return 0;
}
