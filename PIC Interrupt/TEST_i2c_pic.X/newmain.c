#include "common.h"
#include "i2c.h"
#include "ssd1306_unbuffered.h"
#include <stdlib.h>
#define NUM_OPTIONS 8

typedef struct{
    
    const char* name;
    void (*action)();
    struct Typedef_MenuOPT* submenu;
    uint8_t submenuSize;
    
}Typedef_MenuOPT;

Typedef_MenuOPT MAIN_MENU[NUM_OPTIONS] = {
    {"1.Main Menu    ", NULL, NULL, NULL},
    {"2.Camera       ", NULL, NULL, NULL},
    {"3.Multimedia   ", NULL, NULL, NULL},
    {"4.Games        ", NULL, NULL, NULL},
    {"5.Calender     ", NULL, NULL, NULL},
    {"6.Gallery      ", NULL, NULL, NULL},
    {"7.StopWatch    ", NULL, NULL, NULL},
    {"8.Exit         ", NULL, NULL, NULL}
} ;
void oled_puts(const char* c, uint8_t size) {
    while(*c != '\0') {
        SSD1306_PutStretchC(*c, size);
        c++;
    }
}
void Display_Menu(Typedef_MenuOPT menu,uint8_t size, uint8_t* currentOption);
void main(void) 
{
 
    I2C_Initialize(2000);
    TRISD = 0xff;
    SSD1306_Init(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    uint8_t arr[] = {0x78,0x47,0x41,0x47,0x78};
    SSD1306_ClearDisplay();
    while(1) {
//        SSD1306_GotoXY(1,CurrentOption+1);
//        oled_puts(MAIN_MENU[CurrentOption].name,1); 
//        
//        if((PORTD & 0x01)== 0x01){
//            CurrentOption++;
//            if(CurrentOption > 7){
//                CurrentOption = 0;
//            }
//            while((PORTD & 0x01)== 0x01);
//        }
        
        //Display_Menu(MAIN_MENU,NUM_OPTIONS,&CurrentOption);
        SSD1306_GotoXY(1,1);
        oled_puts("SOFCON PRIVATE LTD.",1);
        SSD1306_GotoXY(1,3);
        oled_puts("CH.. MANHWAR HASAN",1);
        SSD1306_GotoXY(1,5);
        oled_puts("EMBEDDED FACUILTY",1);

    }

    return;
}
//void Display_Menu(Typedef_MenuOPT menu,uint8_t size, uint8_t *currentOption){
//    SSD1306_GotoXY(1,1);
//    oled_puts(">",1);
//    SSD1306_GotoXY(2,1);
//    oled_puts(menu[*currentOption].name,1);
//}