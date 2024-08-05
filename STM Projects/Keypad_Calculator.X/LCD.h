/* 
 * File:   LCD.h
 * Author: Sofcon_Lab2
 *
 * Created on 4 April, 2023, 8:53 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#define F_CPU 1000000UL
#include <xc.h>
#include <util/delay.h>

#define LCD_PORT      PORTD
#define LCD_PORT_DIR  DDRD
    
#define LCD_RS PD0
#define LCD_RW PD1
#define LCD_EN PD2
    
    
    void LCD_WriteCommand(unsigned char cmd);
    void LCD_WriteData(unsigned char data);
    void LCD_Initialize( void );
    void LCD_WriteString(const char *ptr);
    void LCD_Location(uint8_t row , uint8_t col);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

