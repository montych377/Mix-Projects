//#include <LPC17xx.h>

//#define LCD_DATA_PORT  LPC_GPIO1->FIOPIN
//#define LCD_CTRL_PORT  LPC_GPIO2->FIOPIN

//#define LCD_DPORT_DIR  LPC_GPIO1->FIODIR
//#define LCD_CPORT_DIR  LPC_GPIO2->FIODIR 

//#define LCD_D0 20
//#define LCD_D1 21
//#define LCD_D2 22
//#define LCD_D3 23
//#define LCD_D4 24
//#define LCD_D5 25
//#define LCD_D6 26
//#define LCD_D7 27

//#define LCD_RS 0
//#define LCD_EN 1

//#define LCD_DATA_PIN_CONFIG  ((1<<LCD_D0)| (1<<LCD_D1)| (1<<LCD_D2)| (1<<LCD_D3)| (1<<LCD_D4)| (1<<LCD_D5)| (1<<LCD_D6)| (1<<LCD_D7))
//#define LCD_CTRL_PIN_CONFIG   (((1<<LCD_RS)|(1<<LCD_EN)))

//typedef struct {
//    volatile uint32_t FIOPIN;  // GPIO Port Pin Value Register
//    volatile uint32_t FIODIR;  // GPIO Port Direction Control Register
//    volatile uint32_t FIOMASK; // GPIO Port Mask Register
//    volatile uint32_t FIOPIN2; // GPIO Port Output Set Register
//    // ... other relevant registers
//} GPIO_Port;
//#define GPIO_PORT(portNum) ((GPIO_Port *)(LPC_GPIO0_BASE + (0x20 * portNum)))
//typedef union{
//	
//	struct {
//		
//		uint8_t b0:1;
//		uint8_t b1:1;
//		uint8_t b2:1;
//		uint8_t b3:1;
//		uint8_t b4:1;
//		uint8_t b5:1;
//		uint8_t b6:1;
//		uint8_t b7:1;
//		
//	};
//	
//	struct {
//		
//		uint8_t Nin1:4;
//		uint8_t Nin2:4;
//	};
//	
//	char x;
//}Typedef_LCD_BIT;

//void lcd_sendbyte(char byte);
//void LCD_WriteCommand(char cmd);
//void LCd_WriteData(char data);
//void LCD_Initialize( void );
//void Delay(int ms);

//int main( void ) {
//	
//	LCD_DPORT_DIR = LCD_DATA_PIN_CONFIG;
//	LCD_CPORT_DIR = LCD_CTRL_PIN_CONFIG;
//	
//	LCD_Initialize();
//	
//	
//	while(1) {
//		
//		LCD_WriteCommand(0x80);
//		LCd_WriteData('A');
//	}
//	
//}


////    LcdDataBusPort&=~(LCD_dataBusMask);                  // Clear previous data 
////    LcdDataBusPort|= (((byte >>0x00) & 0x01) << LCD_D0);
////    LcdDataBusPort|= (((byte >>0x01) & 0x01) << LCD_D1);
////    LcdDataBusPort|= (((byte >>0x02) & 0x01) << LCD_D2);
////    LcdDataBusPort|= (((byte >>0x03) & 0x01) << LCD_D3);
////    LcdDataBusPort|= (((byte >>0x04) & 0x01) << LCD_D4);
////    LcdDataBusPort|= (((byte >>0x05) & 0x01) << LCD_D5);
////    LcdDataBusPort|= (((byte >>0x06) & 0x01) << LCD_D6);
////    LcdDataBusPort|= (((byte >>0x07) & 0x01) << LCD_D7);


//void lcd_sendbyte(char byte){

//	Typedef_LCD_BIT y = (Typedef_LCD_BIT) byte;
//	
//	LCD_DATA_PORT &= ~(LCD_DATA_PIN_CONFIG);
//	
//	LCD_DATA_PORT |= ((y.b0&0x01) << LCD_D0);
//	LCD_DATA_PORT |= ((y.b1&0x02) << LCD_D1);
//	LCD_DATA_PORT |= ((y.b2&0x04) << LCD_D2);
//	LCD_DATA_PORT |= ((y.b3&0x08) << LCD_D3);
//	LCD_DATA_PORT |= ((y.b4&0x10) << LCD_D4);
//	LCD_DATA_PORT |= ((y.b5&0x20) << LCD_D5);
//	LCD_DATA_PORT |= ((y.b6&0x40) << LCD_D6);
//	LCD_DATA_PORT |= ((y.b7&0x80) << LCD_D7);
//	
//}

//void LCD_WriteCommand(char cmd){
//	
//	lcd_sendbyte(cmd);
//	LCD_CTRL_PORT &= ~(1<<LCD_RS);
//	LCD_CTRL_PORT |= (1<<LCD_EN);
//	Delay(1);
//	LCD_CTRL_PORT &= ~(1<<LCD_EN);
//	Delay(1);
//}
//void LCd_WriteData(char data){
//	
//	lcd_sendbyte(data);
//	LCD_CTRL_PORT |= (1<<LCD_RS);
//	LCD_CTRL_PORT |= (1<<LCD_EN);
//	Delay(1);
//	LCD_CTRL_PORT &= ~(1<<LCD_EN);
//	Delay(1);
//}
//void LCD_Initialize( void ) {
//	
//	LCD_WriteCommand(0x01);
//	LCD_WriteCommand(0x02);
//	LCD_WriteCommand(0x06);
//	LCD_WriteCommand(0x38);
//	LCD_WriteCommand(0x0C);
//}

//void Delay(int ms){
//	
//	uint16_t i,j;
//	for(i=0;i<ms;i++){
//		for(j=0;j<5000;j++);
//	}
//}
//	


#include "LPC17xx.h"

// LCD control bits
typedef union {
    struct {
        uint32_t rs : 1;  // Register select
        uint32_t rw : 1;  // Read/write control
        uint32_t en : 1;  // Enable control
        uint32_t bl : 1;  // Backlight control (if applicable)
        uint32_t reserved : 28;
    };
    uint32_t mask;
} LCD_ControlBits;

// LCD data byte
typedef uint8_t LCD_DataByte;

// GPIO port for LCD control and data
typedef struct {
    volatile LCD_ControlBits control;
    volatile LCD_DataByte data;
} LCD_GPIO_Port;

#define LCD_GPIO_BASE LPC_GPIO1_BASE
#define LCD_GPIO ((LCD_GPIO_Port *)LCD_GPIO_BASE)

#define LCD_RS_PIN  0
#define LCD_RW_PIN  1
#define LCD_EN_PIN  2

#define LCD_D0_PIN  20
#define LCD_D1_PIN  21
#define LCD_D2_PIN  22
#define LCD_D3_PIN  23
#define LCD_D4_PIN  24
#define LCD_D5_PIN  25
#define LCD_D6_PIN  26
#define LCD_D7_PIN  27

void delay(uint32_t count) {
    for (uint32_t i = 0; i < count; i++) {
        for (uint32_t j = 0; j < 10000; j++) {
            __NOP(); // A simple delay function
        }
    }
}

void lcdSendCommand(uint8_t command) {
    LCD_ControlBits controlBits;
    controlBits.rs = 0; // Command mode
    controlBits.rw = 0; // Write mode
    controlBits.en = 1; // Enable

    // Send command to LCD
    LCD_GPIO->control.mask = controlBits.mask;
    LCD_GPIO->data = command;
    delay(10);
    controlBits.en = 0; // Disable
    LCD_GPIO->control.mask = controlBits.mask;
    delay(10);
}

void lcdInit() {
    // Initialize GPIO settings for LCD control and data pins

    delay(15); // LCD power-up delay
    lcdSendCommand(0x38); // Function Set: 8-bit mode, 2 lines, 5x8 font
    lcdSendCommand(0x0E); // Display ON/OFF Control: Display ON, Cursor ON, Blink OFF
    lcdSendCommand(0x06); // Entry Mode Set: Increment cursor, No display shift
    lcdSendCommand(0x01); // Clear Display
    delay(2); // Clear display delay
}



void lcdSendData(uint8_t data) {
    LCD_ControlBits controlBits;
    controlBits.rs = 1; // Data mode
    controlBits.rw = 0; // Write mode
    controlBits.en = 1; // Enable

    // Send data to LCD
    LCD_GPIO->control.mask = controlBits.mask;
    LCD_GPIO->data = data;
    delay(10);
    controlBits.en = 0; // Disable
    LCD_GPIO->control.mask = controlBits.mask;
    delay(10);
}
void lcdPrintString(const char *str) {
    while (*str != '\0') {
        lcdSendData(*str);
        str++;
    }
}
int main() {
    // Initialize GPIO settings for LCD control and data pins

    lcdInit(); // Initialize the LCD
    lcdSendCommand(0x80); // Set cursor to the beginning of the first line
    lcdPrintString("Hello, World!");

    while (1) {
        // Main loop
    }
    return 0;
}