

/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include <stdio.h>
/*
    Main application
*/
extern uint16_t counts;
extern uint8_t flag;
void lcd_init(void);
void lcd_data(uint8_t data);
void lcd_cmd(uint8_t cmd);
void lcd_string(uint8_t *ptr);
int main(void)
{
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    TRISC = 0x00;
    TRISB4=0;
    TRISB5=0;
    TRISB6=0;
    TRISB7=0;
    //ADC_Initialize();
    Timer0_Initialize();
    lcd_init();
    char arr[13] ={0};
    while(1)
    {
        if(flag)
        {
            sprintf(arr,"counts:%06d",counts);
            lcd_cmd(0x80);
            lcd_string((uint8_t *)arr);
            flag = 0;
        }
        
     
//        if(counts == 100)
//        {
//            RB7 ^= 1;
//            lcd_cmd(0xc0);
//            lcd_string((uint8_t *)"Led On ");
//            counts = 0;
//        }
//        else
//        {
//            RB7 = 0;
////            lcd_cmd(0xc0);
////            lcd_string((uint8_t *)"Led Off ");
//        }
    }    
}

void lcd_init(void)
{
    lcd_cmd(0x01);
    lcd_cmd(0x02);
    lcd_cmd(0x06);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
}
void lcd_data(uint8_t data)
{
    PORTC = data;
    RB4 = 1;
    RB5 = 0;
    RB6 = 1;
    __delay_ms(2);
    RB6 = 0;
    __delay_ms(2);
}
void lcd_cmd(uint8_t cmd)
{
    PORTC = cmd;
    RB4 = 0;
    RB5 = 0;
    RB6 = 1;
    __delay_ms(2);
    RB6 = 0;
    __delay_ms(2);
}
void lcd_string(uint8_t *ptr)
{
    while(*ptr != '\0')
    {
        lcd_data(*ptr++);
    }
}