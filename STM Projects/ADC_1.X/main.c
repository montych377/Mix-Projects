/*
 * File:   main.c
 * Author: Sofcon_Lab2
 *
 * Created on 8 April, 2023, 9:29 AM
 */
#define F_CPU 1000000UL
#include <util/delay.h>
#include <stdio.h>
#include <xc.h>
#include "LCD.h"
#include "ADC.h"


int main(void) {
    char arr[15];
    DDRD = 0xff;
    DDRB = 0xff;
    ADC_Initialize();
    LCD_Initialize();
    while(1){
        uint16_t adc0 = ADC_Read(0);
        
        uint16_t adc1 = ADC_Read(1);
        
        uint16_t adc2 = ADC_Read(2);
        
        uint16_t adc3 = ADC_Read(3);
        
        sprintf(arr,"A0:%04d",adc0);
        LCD_Location(1,0);
        LCD_WriteString(arr);
        
        sprintf(arr,"A1:%04d",adc1);
        LCD_Location(1,8);
        LCD_WriteString(arr);
        
        sprintf(arr,"A2:%04d",adc2);
        LCD_Location(2,0);
        LCD_WriteString(arr);
        
        sprintf(arr,"A3:%04d",adc3);
        LCD_Location(2,8);
        LCD_WriteString(arr);
        
        if(adc0 > 100 && adc0<200){
            PORTD |= 0x01;
        }else{
            PORTD &= ~0x01;
        }
        if(adc1 > 250 && adc1 < 450){
            PORTD |= 0x02;
        }
        else{
            PORTD &= ~0x02;
        }
        if(adc2 > 900 && adc2 <1000){
            PORTD |= 0x04;
        }
        else{
            PORTD &= ~0x04;
        }
        if(adc3 > 1000){
            PORTD |= 0x08;
        }
    }
    return 0;
}


