
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void UARtT_Initiaize(long baud) {
    UBRRL = (((F_CPU)/(16*baud))-1);
    UBRRH = (((F_CPU)/(16*baud))-1)<<8;
    UCSRB = (1<<TXEN) | (1<<RXEN);
    UCSRC = (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
}

void Uart_Tx(char data) {
    
    UDR = data;
    while((UCSRA & (1<<UDRE))==0);
}

char Uart_Rx( void ) {
    
    while((UCSRA & (1<<RXC)) == 0);
    return UDR;
}
void Uart_string(const char *ptr) {
    
    while(*ptr) {
        
        Uart_Tx(*ptr++);
        _delay_ms(10);
    }
}
int main() {
    
    UARtT_Initiaize(9600);

    while(1){
        
        Uart_string("Hello World!!\r\n");
        _delay_ms(100);
    }
}
