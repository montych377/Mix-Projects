
//  External Interrupts ENT0 and ENT1
//#define F_CPU 1000000UL
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>
//
//volatile uint8_t UP_Counter = 0,DOWN_Counter = 0;
//ISR(INT0_vect) {
//    
//    UP_Counter++;
//}
//
//ISR(INT1_vect) {
//    
//    DOWN_Counter++;
//}
//
//void EXT0_Interrupt() {
//    
//    MCUCR =  (1<<ISC00)|(1<<ISC10);
//    GICR = (1<<INT0) | (1<<INT1);
//    sei();
//}
//int main() {
//    
//    DDRB |= (1<<PB0);
//    DDRB |= (1<<PB1);
//    DDRB |= (1<<PB2);
//    
//    EXT0_Interrupt();
//    
//    while(1) {
//        
//        if(DOWN_Counter == 10) {
//            
//            PORTB ^= (1<<PB0);
//        }
//        
//        if(UP_Counter == 10) {
//            
//            PORTB ^= (1<<PB1);
//        }
//    }
//}

//Timer0 Overflow Interrupt 
//#define F_CPU 1000000UL
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>
//
//volatile uint16_t Timer_Counter1 = 0;
//volatile uint16_t Timer_Counter2 = 0;
//volatile uint16_t Timer_Counter3 = 0;
//volatile uint16_t Timer_Counter4 = 0;
//
//void Timer0_Initialize() 
//{
//    TCCR0 = (1<<CS01);
//    TIMSK = (1<<TOIE0);
//  
//}
//
//void Timer1_Initialize() 
//{
//    TCCR1B = (1<<CS10);
//    TIMSK = (1<<TOIE1);
//}
//
//ISR(TIMER0_OVF_vect) 
//{
//    Timer_Counter1++;
//    Timer_Counter2++;
//    Timer_Counter3++;
//    Timer_Counter4++;
//    TCNT0 = 131;
//}
//
//int main() 
//{
//    DDRD |= (1<<PD0);
//    DDRD |= (1<<PD1);
//    DDRD |= (1<<PD2);
//    DDRD |= (1<<PD3);
//    
//    Timer0_Initialize();
//    Timer1_Initialize();
//    sei();
//    while(1) 
//    {
//        if(Timer_Counter1 == 200)
//        {
//            PORTD ^= (1<<PD0);
//            Timer_Counter1 = 0;
//        }
//        if(Timer_Counter2 == 500)
//        {
//            PORTD ^= (1<<PD1);
//            Timer_Counter2 = 0;
//        }
//        if(Timer_Counter3 == 800)
//        {
//            PORTD ^= (1<<PD2);
//            Timer_Counter3 = 0;
//        }
//        
//        if(Timer_Counter4 == 1000)
//        {
//            PORTD ^= (1<<PD3);
//            Timer_Counter4 = 0;
//        }
//
//    }
//}


//Timer1 Overflow Interrupt  

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t Timer1_Counter1 = 0;
volatile uint16_t Timer1_Counter2 = 0;
volatile uint16_t Timer1_Counter3 = 0;
volatile uint16_t Timer1_Counter4 = 0;


void Timer1_Initialize() 
{
    TCCR1B = (1<<CS11);
    TIMSK = (1<<TOIE1);
}

ISR(TIMER1_OVF_vect) 
{
    Timer1_Counter1++;
    Timer1_Counter2++;
    Timer1_Counter3++;
    Timer1_Counter4++;
    TCNT1 = 25000;
}

int main() 
{
    DDRD |= (1<<PD0);
    DDRD |= (1<<PD1);
    DDRD |= (1<<PD2);
    DDRD |= (1<<PD3);
    
    Timer1_Initialize();
    sei();
    while(1) 
    {
        if(Timer1_Counter1 == 200)
        {
            PORTD ^= (1<<PD0);
            Timer1_Counter1 = 0;
        }
        if(Timer1_Counter2 == 500)
        {
            PORTD ^= (1<<PD1);
            Timer1_Counter2 = 0;
        }
        if(Timer1_Counter3 == 800)
        {
            PORTD ^= (1<<PD2);
            Timer1_Counter3 = 0;
        }
        
        if(Timer1_Counter4 == 1000)
        {
            PORTD ^= (1<<PD3);
            Timer1_Counter4 = 0;
        }

    }
}