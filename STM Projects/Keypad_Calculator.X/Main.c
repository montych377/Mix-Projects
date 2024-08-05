/*
 * File:   Main.c
 * Author: Sofcon_Lab2
 *
 * Created on 4 April, 2023, 8:53 PM
 */
#include <stdlib.h>
#include <stdio.h>

#include "LCD.h"
#include "KEYPAD1.h"

void calculator( void );

int main(void) {
    
    KEYPAD_PORT_DIR = 0x0f;
    LCD_Initialize();
    
    while(1){
        calculator();
    }
    return 0;
}

void calculator( void ){
    unsigned char num1[10],num2[10],operator;
    int i = 0,j = 0;
    long int result;
    KEYPAD_PORT = 0xf0;
        LCD_WriteCommand(0x01);
        LCD_WriteString("Enter num1:");
        while(1){
            if(PINB != 0xf0){
                unsigned char key = Getkey();
                _delay_ms(200); 
                if(key >='0' && key<= '9'){
                    num1[i] = key;
                    i++;
                    num1[i] = '\0';
                    LCD_WriteData(key);
                }
                else if(key =='='){
                    i=0;
                    break;
                }

            }
        }
        LCD_WriteCommand(0x01);
        LCD_WriteString("Enter op :");
        while(1){
            if(PINB != 0xf0){
                char key = Getkey();
                _delay_ms(200);
                if(key =='+' || key =='-' || key == '/' || key == '*'){
                    operator = key;
                    LCD_WriteData(key);
                    break;
                }
            }
        }
        
        LCD_WriteCommand(0x01);
        LCD_WriteString("Enter num2 :");
        while(1){
            if(PINB != 0xf0){
                char key = Getkey();
                _delay_ms(200);
                if(key >='0' && key <='9'){
                    num2[j] = key;
                    j++;
                    num2[j] = '\0';
                    LCD_WriteData(key);
                }
                else if(key == '='){
                    j=0;
                    break;
                }
            }
        }
        
        long int n1 = atoi(num1);
        long int n2 = atoi(num2);
        
        switch(operator){
            case '+':
                result = n1+n2;
                break;
            case '-':
                result = n1-n2;
                break;
            case '*':
                result = n1*n2;
                break;
            case '/':
                result = n1/n2;
                break;
            default:
                break;
                
        }
        
        LCD_WriteCommand(0x01);
        char str[16];
        sprintf(str,"%d",result);
        LCD_WriteString(str);
        _delay_ms(5000);

}
