#include"KEYPAD1.h"

unsigned char Getkey( void ){
    PORTB = 0b11111110;
    if((PINB & (1<<PINB4))==0){
        
        _delay_ms(3);
        return '7';
    }
    
    else if((PINB & (1<<PINB5))==0){
        _delay_ms(3);
        return '8';
    }
    else if((PINB & (1<<PINB6))==0){
        _delay_ms(3);
        return '9';
    }
    else if((PINB & (1<<PINB7))==0){
        _delay_ms(3);
        return '/';
    }
    
    
    PORTB = 0b11111101;
    if((PINB & (1<<PINB4))==0){
        
        _delay_ms(3);
        return '4';
    }
    
    else if((PINB & (1<<PINB5))==0){
        _delay_ms(3);
        return '5';
    }
    else if((PINB & (1<<PINB6))==0){
        _delay_ms(3);
        return '6';
    }
    else if((PINB & (1<<PINB7))==0){
        _delay_ms(3);
        return '*';
    }
    
    
    
    PORTB = 0b11111011;
    if((PINB & (1<<PINB4))==0){
        
        _delay_ms(3);
        return '1';
    }
    
    else if((PINB & (1<<PINB5))==0){
        _delay_ms(3);
        return '2';
    }
    else if((PINB & (1<<PINB6))==0){
        _delay_ms(3);
        return '3';
    }
    else if((PINB & (1<<PINB7))==0){
        _delay_ms(3);
        return '-';
    }
    
    
    PORTB = 0b11110111;
    if((PINB & (1<<PINB4))==0){
        
        _delay_ms(3);
        return 'C';
    }
    
    else if((PINB & (1<<PINB5))==0){
        _delay_ms(3);
        return '0';
    }
    else if((PINB & (1<<PINB6))==0){
        _delay_ms(3);
        return '=';
    }
    else if((PINB & (1<<PINB7))==0){
        _delay_ms(3);
        return '+';
    }
    
    return 0;
  
}
