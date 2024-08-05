/*
 * File:   newmain.c
 * Author: Sofcon_Lab2
 *
 * Created on 31 May, 2023, 2:30 AM
 */

#define _XTAL_FREQ 8000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include <stdlib.h>
#include "glcd-font.h"

#define GLCD_DATA_PORT   PORTD
#define GLCD_CTRL_PORT   PORTC
#define GLCD_DPORT_DIR   TRISD
#define GLCD_CPORT_DIR   TRISC

#define RS  0
#define RW  1
#define EN  2

#define RST 3
#define CS1 4
#define CS2 5

#define NUM_OPTIONS 8
uint8_t  page[]={0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF};
typedef struct MenuOption {
    const char* name;
    void (*action)();
    struct MenuOption* submenu;
    uint8_t submenuSize;
} MenuOption;

MenuOption mainMenu[NUM_OPTIONS] = {
    {"Main Menu   ", NULL, NULL, 0},
    {"Camera      ", NULL, NULL, 0},
    {"Multimedia  ", NULL, NULL, 0},
    {"Games       ", NULL, NULL, 0},
    {"Calender    ", NULL, NULL, 0},
    {"Gallery     ", NULL, NULL, 0},
    {"StopWatch   ", NULL, NULL, 0},
    {"Exit        ", NULL, NULL, 0}
};
void glcd_cmd(char cmd){
    GLCD_DATA_PORT = cmd;
    GLCD_CTRL_PORT &= ~(1<<RS);
    GLCD_CTRL_PORT &= ~(1<<RW);
    GLCD_CTRL_PORT |=  (1<<EN);
    __delay_us(10);
    GLCD_CTRL_PORT &= ~(1<<EN);
    __delay_us(10);
}
void glcd_data(char data){
    GLCD_DATA_PORT = data;
    GLCD_CTRL_PORT |=  (1<<RS);
    GLCD_CTRL_PORT &= ~(1<<RW);
    GLCD_CTRL_PORT |=  (1<<EN);
    __delay_us(10);
    GLCD_CTRL_PORT &= ~(1<<EN);
    __delay_us(10);
}
void glcd_PageSelect(char page){
    switch(page){
        case 0:
            GLCD_CTRL_PORT |= (1<<CS1);
            GLCD_CTRL_PORT &= ~(1<<CS2);
        break;    
        case 1:
            GLCD_CTRL_PORT &= ~(1<<CS1);
            GLCD_CTRL_PORT |=  (1<<CS2);
        break;    
        case 2:
            GLCD_CTRL_PORT |= (1<<CS1);
            GLCD_CTRL_PORT |= (1<<CS2);
        break;    
        case 3:
            GLCD_CTRL_PORT &= ~(1<<CS1);
            GLCD_CTRL_PORT &= ~(1<<CS2);
        break;
        
        default:
            GLCD_CTRL_PORT |= (1<<CS1);
            GLCD_CTRL_PORT &= ~(1<<CS2);
        break;    
    }
}
void glcd_init(){
    
    GLCD_DPORT_DIR = 0x00;
    GLCD_CPORT_DIR = 0x00;
    GLCD_DATA_PORT = 0x00;
    GLCD_CTRL_PORT = 0x00;
    GLCD_CTRL_PORT &= ~(1<<RST);
    __delay_us(10);
    GLCD_CTRL_PORT |= (1<<RST);
    __delay_us(10);
    glcd_PageSelect(2);
    __delay_us(10);
    glcd_cmd(0x0C);
    glcd_cmd(0x3f);
    __delay_us(10);
    glcd_PageSelect(3);
    __delay_us(10);
}


void  glcd_printChar(const char *ptr){
    
    uint8_t i=0;
    
    for(i=0;i<1;i++){
        glcd_data(ptr[i]);
    }
}

void glcd_WriteString(const char *str){
    int i = 0;
    int startfont=0,endfont=0;
    while(*str){
        startfont = (*str-32)*5;
        endfont = startfont +5 ;
        for(i=startfont;i<endfont;i++){
            glcd_data(sys5x7[i]);
            __delay_ms(1);
        }
        *str++;
    }
    
    
}

//void createimage(const char *image){
//    unsigned int i=0,j=0;
//    int page[]={0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF};
//
//
//    __delay_ms(1);
//    glcd_cmd(0xC0);    //Start line, (64 rows) selects from where to start(1 line)
//    for(i=0;i<=7;i++){
//        glcd_PageSelect(0);
//        glcd_cmd(page[i]);
//        glcd_cmd(0x40);    //Setting y-address
//        for(j=0+(i*128);j<=63+(i*128);j++){
//            glcd_data(image[j]);
//        }
//        glcd_PageSelect(1);
//        glcd_cmd(page[i]);
//        glcd_cmd(0x40);    //Setting y-address
//        for(j=64+(i*128);j<=127+(i*128);j++){
//            glcd_data(image[j]);
//        }
//        j=0;
//    }
//}
void glcd_SetCursor(char x,char y)
{
    glcd_cmd(x);
    glcd_cmd(0x40 + y);
    
}
void displayMenu(const MenuOption* menu, uint8_t size, uint8_t* currentOption){

    
    glcd_SetCursor(page[1],0);
    glcd_WriteString(">");

    while (1) {
//        if (!(PORTB & 0x01)) {
//            __delay_ms(50); 
//
//            if (menu[*currentOption].submenu != NULL && menu[*currentOption].submenuSize > 0  && menu[*currentOption].action != NULL) {
//                glcd_SetCursor(page[0],5);
//                menu[*currentOption].action();
//                displayMenu(menu[*currentOption].submenu, menu[*currentOption].submenuSize, currentOption);
//            } else {
//                if (menu[*currentOption].action != NULL) {
//                    glcd_SetCursor(page[1],5);
//                    menu[*currentOption + 1].action();
//                }
//            }
//        }

        if (!(PORTB & 0x02)) {
            __delay_ms(50); 
            *currentOption = (*currentOption + 1) % size;

            glcd_SetCursor(page[*currentOption],0);
            glcd_WriteString(">");
            
        }

//        if (!(PORTB & 0x04)) {
//            __delay_ms(50); 
//            *currentOption = (*currentOption - 1+size ) % size;
//
//            glcd_SetCursor(page[1],0);
//            glcd_WriteString(">");
//            glcd_SetCursor(page[1],5);
//            glcd_WriteString(menu[*currentOption].name);
//        }

        if ((PORTB & 0x08)) {
            __delay_ms(50); 
            return;
        }

        __delay_ms(200);
    }
}

void GLCD_ClrScr(void)
{
    for (uint8_t Page = 0; Page < 8; Page++)
    {
    glcd_PageSelect(1);
    glcd_cmd(0xb8 | Page);
    glcd_cmd(0x40);
    for (uint8_t Column = 0;Column < 128; Column++)
    {
    if (Column == 64)
    {
    glcd_PageSelect(0);
    glcd_cmd(0xb8 | Page);
    glcd_cmd(0x40);
    }
    glcd_data(0x00);
//This is Method 3
}
}
}


int main(void) {
    char M[] = {0x01,0x00,0x00,0x00,0x00};
    glcd_init();
    TRISB = 0x0f;
    uint8_t currentOption = 0;
    glcd_PageSelect(0);
    glcd_SetCursor(page[0],0);
    glcd_WriteString("LCD Menu Opt");
    for(uint8_t i=1;i<8;i++){

        glcd_SetCursor(page[i],5);
        glcd_WriteString(mainMenu[((&currentOption)+i)-1].name);
        
    }
    while(1){
        displayMenu(mainMenu, NUM_OPTIONS, &currentOption);
//        glcd_PageSelect(0);
//        glcd_SetCursor(page[1],0);
//        glcd_WriteString(mainMenu[currentOption].name);

    }
    return 0;
}
