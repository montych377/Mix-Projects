#include "LCD.h"
#include "BUTTON.h"
#include <stdlib.h>

// Define keypad pins
#define OK_PIN PB0
#define UP_PIN PB1
#define DOWN_PIN PB2
#define BACK_PIN PB3

#define NUM_OPTIONS 8

typedef struct MenuOption {
    const char* name;
    void (*action)();
    struct MenuOption* submenu;
    uint8_t submenuSize;
} MenuOption;


void MainMenuFun();
void CameraMenuFun();
void MultimediaFun();
void GameMenuFun();
void CalenderMenuFun();
void GalleryMenuFun();
void StopWatchMenuFun();
void ExitMenuFun();
void SubCameraMenuFun();
void CameraSettingsMenuFun();

MenuOption SubmainMenu[NUM_OPTIONS] = {
    {"1.Main Menu1   ", NULL, NULL, 0},
    {"2.Main Menu2   ", NULL, NULL, 0},
    {"3.Main Menu3   ", NULL, NULL, 0},
    {"4.Main Menu4   ", NULL, NULL, 0},
    {"5.Main Menu5   ", NULL, NULL, 0},
    {"6.Main Menu6   ", NULL, NULL, 0},
    {"7.Main Menu7   ", NULL, NULL, 0},
    {"8.Main Menu8   ", NULL, NULL, 0}
};
MenuOption SubCalender[12] = {
    {"1.January      ", NULL, NULL, 0},
    {"2.Febeuary     ", NULL, NULL, 0},
    {"3.March        ", NULL, NULL, 0},
    {"4.April        ", NULL, NULL, 0},
    {"5.May          ", NULL, NULL, 0},
    {"6.June         ", NULL, NULL, 0},
    {"7.July         ", NULL, NULL, 0},
    {"8.August       ", NULL, NULL, 0},
    {"9.September    ", NULL, NULL, 0},
    {"10.October     ", NULL, NULL, 0},
    {"11.November    ", NULL, NULL, 0},
    {"11.December    ", NULL, NULL, 0}
};
MenuOption SubSubCamera[NUM_OPTIONS] = {
    {"Camera 11     ", &SubCameraMenuFun, NULL, 0},
    {"Camera 21     ", NULL, NULL, 0},
    {"Camera 31     ", NULL, NULL, 0},
    {"Camera 41     ", NULL, NULL, 0},
    {"Camera 51     ", NULL, NULL, 0},
    {"Camera 61     ", NULL, NULL, 0},
    {"Camera 71     ", NULL, NULL, 0},
    {"Camera 81     ", NULL, NULL, 0}
};
MenuOption SubCamera[NUM_OPTIONS] = {
    {"Camera Setting  ", &CameraSettingsMenuFun, &SubSubCamera, 8},
    {"Camera Filters  ", NULL, NULL, 0},
    {"Camera Edit     ", NULL, NULL, 0},
    {"Camera Config   ", NULL, NULL, 0},
    {"Camera Brightness", NULL, NULL, 0},
    {"Camera Contrast  ", NULL, NULL, 0},
    {"Camera Pannel    ", NULL, NULL, 0},
    {"Camera Photos    ", NULL, NULL, 0}
};
MenuOption SubMultimedia[NUM_OPTIONS] = {
    {"1.Multimedia 1 ", NULL, NULL, 0},
    {"2.Multimedia 2 ", NULL, NULL, 0},
    {"3.Multimedia 3 ", NULL, NULL, 0},
    {"4.Multimedia 4 ", NULL, NULL, 0},
    {"5.Multimedia 5 ", NULL, NULL, 0},
    {"6.Multimedia 6 ", NULL, NULL, 0},
    {"7.Multimedia 7 ", NULL, NULL, 0},
    {"8.Multimedia 8 ", NULL, NULL, 0}
};
MenuOption SubGames[NUM_OPTIONS] = {
    {"1.Pub g Mobile ", NULL, NULL, 0},
    {"2.Free Fire    ", NULL, NULL, 0},
    {"3.Snake Game   ", NULL, NULL, 0},
    {"4.Puzzle Game  ", NULL, NULL, 0},
    {"5.GTA VoiceCity", NULL, NULL, 0},
    {"6.BGMI Pub G   ", NULL, NULL, 0},
    {"7.Fast Faster 1", NULL, NULL, 0},
    {"8.Fast Faster 2", NULL, NULL, 0}
};

MenuOption mainMenu[NUM_OPTIONS] = {
    {"1.Main Menu    ", &MainMenuFun, &SubmainMenu, 8},
    {"2.Camera       ", &CameraMenuFun, &SubCamera, 8},
    {"3.Multimedia   ", &MultimediaFun, &SubMultimedia, 8},
    {"4.Games        ", &GameMenuFun, &SubGames, 8},
    {"5.Calender     ", &CalenderMenuFun, &SubCalender, 12},
    {"6.Gallery      ", &GalleryMenuFun, NULL, 0},
    {"7.StopWatch    ", &StopWatchMenuFun, NULL, 0},
    {"8.Exit         ", &ExitMenuFun, NULL, 0}
};
    
    
void displayMenu(const MenuOption* menu, uint8_t size, uint8_t* currentOption);



int main(void) {
    DDRB &= ~((1 << OK_PIN) | (1 << UP_PIN) | (1 << DOWN_PIN) | (1 << BACK_PIN)); // Set pins as input

    LCD_Initialize();
    uint8_t currentOption = 0;
    LCD_Command(0x80);
    LCD_String("  LCD Menu Opt :");
    
    while (1) {
        
        displayMenu(mainMenu, NUM_OPTIONS, &currentOption);
    }

    return 0;
}

void displayMenu(const MenuOption* menu, uint8_t size, uint8_t* currentOption) {
    
    LCD_Command(0xC0);
    LCD_Data('>');
    LCD_Command(0xC1);
    LCD_String(menu[*currentOption].name);

    while (1) {
        if ((PINB & 0x01)==0x01) {
            _delay_ms(50); 

            if (menu[*currentOption].submenu != NULL && menu[*currentOption].submenuSize > 0  && menu[*currentOption].action != NULL) {
                LCD_Command(0x80);
                menu[*currentOption].action();
                displayMenu(menu[*currentOption].submenu, menu[*currentOption].submenuSize, currentOption);
            } else {
                if (menu[*currentOption].action != NULL) {
                    LCD_Command(0xC0);
                    menu[*currentOption + 1].action();
                }
            }
        }

        if ((PINB & 0x02) == 0x02) {
            _delay_ms(50); 
            *currentOption = (*currentOption + 1) % size;

            LCD_Command(0xC0);
            LCD_Data('>');
            LCD_Command(0xC1);
            LCD_String(menu[*currentOption].name);
        }

        if ((PINB & 0x04) == 0x04) {
            _delay_ms(50); 
            *currentOption = (*currentOption - 1+size ) % size;

            LCD_Command(0xC0);
            LCD_Data('>');
            LCD_Command(0xC1);
            LCD_String(menu[*currentOption].name);
        }

        if (!(PINB & 0x08) == 0x08) {
            _delay_ms(50); 
            return;
        }

        _delay_ms(200);
    }
}
void MainMenuFun() {
    
    LCD_String("Main Menu Opt : ");
}
void CameraMenuFun() {
    
    LCD_String("Camera Menu Opt:");
}
void SubCameraMenuFun() {
    
    LCD_String("SubCamera Opt:");
}
void CameraSettingsMenuFun() {
    
    LCD_String("Cam Settings Opt:");
}
void MultimediaFun() {
    
    LCD_String("Multimedia Menu Opt:");
}
void GameMenuFun() {
    
    LCD_String("Game Menu Opt : ");
}
void CalenderMenuFun() {
    
    LCD_String("Calender Menu Opt:");
}
void GalleryMenuFun() {
    
    LCD_String("Gallery Menu Opt:");
}
void StopWatchMenuFun() {
    
    LCD_String("StopWatch Menu Opt:");
}
void ExitMenuFun() {
    
    LCD_String("Exit Menu Opt:");
}