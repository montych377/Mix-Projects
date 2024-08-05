#include "BUTTON.h"
#include <string.h>

#define BUTTON1  PB0
#define BUTTON2  PB2
#define BUTTON3  PB3
#define BUTTON4  PB4

static Button_Typedef buttons_array[MAX_BUTTONS]= {0};

void Buttons_Initialize( void ) {
    
    memset(buttons_array,0,MAX_BUTTONS);
	
    DDRB &= ~(1<<BUTTON1);
    DDRB &= ~(1<<BUTTON2);
    DDRB &= ~(1<<BUTTON3);
    DDRB &= ~(1<<BUTTON4);
}

void Buttons_Task( void ) {
   
    int i = 0;	
	
    for(i = 0; i < MAX_BUTTONS;i++) {
        
			buttons_array[i].state = (i == 0) ? BUTTON1 : (i == 1) ? BUTTON2 : (i == 2) ? BUTTON3 : (i == 3) ? BUTTON4 : 0;   
        
        if(buttons_array[i].state == 0 && !buttons_array[i].pressed) {
            buttons_array[i].pressed = 1;
        }
        
        if(buttons_array[i].pressed && buttons_array[i].state)
        {
            buttons_array[i].pressed = 0;
            buttons_array[i].released = 1;
        }
        
        if(buttons_array[i].released) {
            buttons_array[i].released = 0;
            buttons_array[i].status = 1;
        }
    }  
}

void Button_Flashed( void ) {
	    int i = 0;	
	
    for(i = 0; i < MAX_BUTTONS;i++) {
			
			 buttons_array[i].status = 0;
		}
}
unsigned char Button_Get(unsigned char button) {
	
	
   
   	unsigned char val = buttons_array[button].status;
	    	
       buttons_array[button].status = 0;
	
    return val;
}
