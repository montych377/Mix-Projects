/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 30 May, 2023, 2:02 AM
 */

#define _XTAL_FREQ 1000000

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define rs RD2
#define en RD3

#define R1 RB0
#define R2 RB1
#define R3 RB2
#define R4 RB3
#define C1 RB4
#define C2 RB5
#define C3 RB6
#define C4 RB7

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();
unsigned char key();
void keyinit();
unsigned char keypad[4][4]={
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};
unsigned char rowloc,colloc;

void main()
{
    unsigned int i;
    TRISD=0;
    lcd_init();
    keyinit();
    unsigned char b;
    cmd(0x80);
    show("  Enter the Key ");
    while(1)
    {
        cmd(0xc7);
        b=key();
        dat(b);
        
    }   
}
void lcd_init()
{
    cmd(0x02);
    cmd(0x28);
    cmd(0x0e);
    cmd(0x06);
    cmd(0x80);
}
void cmd(unsigned char a)
{
    rs=0; 
    PORTD&=0x0F;
    PORTD|=(a&0xf0);
    en=1;
    lcd_delay();
    en=0;
    lcd_delay();
    PORTD&=0x0f;
    PORTD|=(a<<4&0xf0);
    en=1;
    lcd_delay();
    en=0;
    lcd_delay();
}
void dat(unsigned char b)
{
    rs=1; 
    PORTD&=0x0F;
    PORTD|=(b&0xf0);
    en=1;
    lcd_delay();
    en=0;
    lcd_delay();
    PORTD&=0x0f;
    PORTD|=(b<<4&0xf0);
    en=1;
    lcd_delay();
    en=0;
    lcd_delay();
}
void show(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}
void lcd_delay()
{
    unsigned int lcd_delay;
    for(lcd_delay=0;lcd_delay<=1000;lcd_delay++);
}
void keyinit()
{
    TRISB=0XF0;
    OPTION_REG&=0X7F;           //ENABLE PULL UP
}
unsigned char key()
{
    PORTB=0X00;
    while(C1&&C2&&C3&&C4);
    while(!C1||!C2||!C3||!C4) {
        R1=0;
        R2=R3=R4=1;
        if(!C1||!C2||!C3||!C4) {
            rowloc=0;
            break;
        }
        R2=0;R1=1;
        if(!C1||!C2||!C3||!C4) {
            rowloc=1;
            break;
        }
        R3=0;R2=1;
        if(!C1||!C2||!C3||!C4) {
            rowloc=2;
            break;
        }
        R4=0; R3=1;
        if(!C1||!C2||!C3||!C4){
            rowloc=3;
            break;
        }
    }
    if(C1==0&&C2!=0&&C3!=0&&C4!=0)
    {
        colloc=0;
    }
    else if(C1!=0&&C2==0&&C3!=0&&C4!=0)
    {
        colloc=1;
    }
    else if(C1!=0&&C2!=0&&C3==0&&C4!=0)
    {
        colloc=2;
    }
    else if(C1!=0&&C2!=0&&C3!=0&&C4==0)
    {
        colloc=3;
    }
    while(C1==0||C2==0||C3==0||C4==0);
    
    return (keypad[rowloc][colloc]);
}