#define _XTAL_FREQ 1000000
#include <xc.h>

int main() {
    
    TRISD = 0x00;
    while(1) {
        
        PORTD = 0xff;
        __delay_ms(1000);
        PORTD = 0x00;
        __delay_ms(1000);
    }
}