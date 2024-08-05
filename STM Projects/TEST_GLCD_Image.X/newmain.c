/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 24 May, 2023, 2:39 AM
 */

#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>

#define GLCD_DATA_PORT  PORTD
#define GLCD_CTRL_PORT  PORTC

#define GLCD_DPORT_DIR  DDRD
#define GLCD_CPORT_DIR  DDRC

#define RS PC0
#define RW PC1
#define EN PC2
#define RST PC3
#define CS1 PC4
#define CS2 PC5

void glcd_cmd(unsigned char cmd);
void glcd_data(unsigned char data);
void glcd_init();
void glcd_writechar(char *dta);
void glcd_writestring(char *str);
void glcd_writeImg(char *pxl);
void glcd_setcursor(uint8_t x,uint8_t y);


int main(void) {
    char data[]={0x01, 0x01, 0x7F, 0x01, 0x01};
    glcd_init();
    while(1){
        glcd_writechar(data);
        _delay_ms(500);
    }
    return 0;
}

void glcd_setcursor(uint8_t x,uint8_t y){
    
    
}
void glcd_writechar(char *dta){
    
    uint8_t i=0;
    glcd_setcursor(0,0);
    for(i=0;i<5;i++){
        glcd_data(*(dta+i));
    }
}
void glcd_writestring(char *str);
void glcd_writeImg(char *pxl);