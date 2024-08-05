/* 
 * File:   LCD.h
 * Author: Sofcon_Lab2
 *
 * Created on 2 January, 2024, 9:36 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


void LCD_Command(char cmd);
void LCD_Data(char data);
void LCD_Initialize( void );
void LCD_String(const char *ptr);
void LCD_Location(uint8_t row, uint8_t col);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

