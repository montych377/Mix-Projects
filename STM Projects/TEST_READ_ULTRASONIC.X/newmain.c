/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 19 May, 2023, 10:53 PM
 */
/*
#define F_CPU 1000000UL
#include <xc.h>
#include <util/delay.h>
#include <stdio.h>
#define TRIGGER_PIN PD2
#define ECHO_PIN    PD3

void setup(){
    DDRD |= (1<<TRIGGER_PIN);
    DDRD &= ~(1<<ECHO_PIN);
}

void sendPluse(){
    
    PORTD |= (1<<TRIGGER_PIN);
    _delay_ms(10);
    PORTD &= (1<<TRIGGER_PIN);
    _delay_ms(2);
}

uint16_t measureDistance(){
    sendPluse();
    uint16_t pulseDuration = 0;
    if(!(PIND & (1<<ECHO_PIN))){
        pulseDuration++;
        _delay_us(1);
    }
    
    uint16_t distance = pulseDuration * 0.034/2;
    
    return distance;
}

void lcd_cmd(char cmd){
    PORTB = cmd;
    PORTC &= ~0x01;
    PORTC &= ~0x02;
    PORTC  |= 0x04;
    _delay_ms(3);
    PORTC &= ~0x04;
    _delay_ms(3);
}

void lcd_data(char data){
    PORTB = data;
    PORTC |=  0x01;
    PORTC &= ~0x02;
    PORTC  |= 0x04;
    _delay_ms(3);
    PORTC &= ~0x04;
    _delay_ms(3);
}

void lcd_init(){
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x02);
    lcd_cmd(0x38);
    lcd_cmd(0x0c);
}

void lcd_string(const char *ptr){
    while(*ptr){
        lcd_data(*ptr++);
    }
}
int main(void) {
    char data[10];
    DDRB=DDRC = 0xff;
    setup();
    lcd_init();
    while(1){
        uint16_t distance = measureDistance();
        
        sprintf(data,"Distance : %d",distance);
        lcd_cmd(0x80);
        lcd_string(data);
        
        _delay_ms(500);
    }
    return 0;
}

 * */


#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define F_CPU 1000000UL




#include <util/delay.h>

#include <stdlib.h>


#define enable            PC2

#define registerselection PC0


void send_a_command(unsigned char command);

void send_a_character(unsigned char character);

void send_a_string(const char *string_of_characters);


static volatile int pulse = 0;

static volatile int i = 0;


int main(void)

{


    DDRB = 0xFF;
    DDRC = 0xff;
    DDRD = 0b11111001;

    _delay_ms(50);

    

    GICR|=(1<<INT0);

    MCUCR|=(1<<ISC00);

    

    TCCR1A = 0;

    

    int16_t COUNTA = 0;

    char SHOWA [16];

    


    send_a_command(0x01); //Clear Screen 0x01 = 00000001

    _delay_ms(50);

    send_a_command(0x38);

    _delay_ms(50);

    send_a_command(0b00001111);

    _delay_ms(50);

    

    sei();

    

    while(1)

    {

        PORTD|=(1<<PIND0);

        _delay_us(15);

        PORTD &=~(1<<PIND0);

        

        COUNTA = pulse/58;

        send_a_string ("CIRCUIT DIGEST");

        send_a_command(0x80 + 0x40 + 0);

        send_a_string ("DISTANCE=");

        sprintf(SHOWA,"%d",COUNTA);

        send_a_string(SHOWA);

        send_a_string ("cm    ");

        send_a_command(0x80 + 0);


    }

}


ISR(INT0_vect)

{

    if (i==1)

    {

        TCCR1B=0;

        pulse=TCNT1;

        TCNT1=0;

        i=0;

    }

    if (i==0)

    {

        TCCR1B|=(1<<CS10);

        i=1;

    }

}


void send_a_command(unsigned char command)

{

    PORTB = command;

    PORTC &= ~ (1<<registerselection);

    PORTC |= 1<<enable;

    _delay_ms(8);

    PORTC &= ~1<<enable;

    PORTB = 0;

}


void send_a_character(unsigned char character)

{

    PORTB = character;

    PORTC |= 1<<registerselection;

    PORTC |= 1<<enable;

    _delay_ms(8);

    PORTC &= ~1<<enable;

    PORTB = 0;

}

void send_a_string(const char *string_of_characters)

{

    while(*string_of_characters > 0)

    {

        send_a_character(*string_of_characters++);

    }

}

