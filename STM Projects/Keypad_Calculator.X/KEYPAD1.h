/* 
 * File:   KEYPAD1.h
 * Author: Sofcon_Lab2
 *
 * Created on 4 April, 2023, 9:10 PM
 */

#ifndef KEYPAD1_H
#define	KEYPAD1_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "LCD.h"
    
#define KEYPAD_PORT       PORTB
#define KEYPAD_PORT_DIR   DDRB
    
    unsigned char Getkey( void );

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD1_H */

