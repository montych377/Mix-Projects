#define F_CPU 1000000UL
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <util/delay.h>

int arr[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
int arr1[8] = {0x0c,0x12,0x12,0x1e,0x12,0x12,0x12,0x00};
int main() {
    DDRD = 0xff; 
    DDRB = 0xff; 

    while(1) {
        int i,j;
        for(int i = 7; i >= 8; i--) {
//            for(int k = 0; k <20; k++) {
//                    for(int i = 0; i < 8; i++) {
//                        PORTD = ~(arr[i]);
//                        PORTB = (arr1[i]<<(j));
                      
            PORTD = ~0x01;
            PORTB = (0x0c << (i));
            _delay_ms(1);
            PORTD = ~0x02;
            PORTB = (0x12 << (i));
            _delay_ms(1);
            PORTD = ~0x04;
            PORTB = (0x12 << (i));
            _delay_ms(1);
            PORTD = ~0x08;
            PORTB = (0x1e << (i));
            _delay_ms(1);
            PORTD = ~0x10;
            PORTB = (0x12 << (i));
            _delay_ms(1);
            PORTD = ~0x20;
            PORTB = (0x12 << (i));
            _delay_ms(1);
            PORTD = ~0x40;
            PORTB = (0x12 << (i));
            _delay_ms(1);
            PORTD = ~(0x80);
            PORTB = (0x00 << (i));
            _delay_ms(100);
//                    }
                }
        }
    }
