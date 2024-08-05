/* 
 * File:   BUTTON.h
 * Author: Sofcon_Lab2
 *
 * Created on 2 January, 2024, 10:14 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "LCD.h"

typedef enum {
	
			OK_BUTTON = 0,
			FUN_BUTTON,
			UP_BUTTON,
			DWN_BUTTON,
			MAX_BUTTONS
							
	}ButtonsType_Typedef;
	
	typedef struct {
		
			unsigned char state:1;
			unsigned char pressed:1;
			unsigned char released:1;
			unsigned char status:1;
			unsigned char :4;
		
	}Button_Typedef;
    
void Buttons_Initialize( void );	
void Buttons_Task( void );
void Button_Flashed( void ) ;	
unsigned char Button_Get(unsigned char button);
    

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_H */

