#include <lpc17xx.h>

/* Configure the data bus and Control bus as per the hardware connection */
#define LcdDataBusPort      LPC_GPIO1->FIOPIN
#define LcdControlBusPort   LPC_GPIO2->FIOPIN

#define LcdDataBusDirnReg   LPC_GPIO1->FIODIR
#define LcdCtrlBusDirnReg   LPC_GPIO2->FIODIR

#define LCD_D4     10
#define LCD_D5     9
#define LCD_D6     8
#define LCD_D7     4

#define LCD_RS     0
#define LCD_RW     1
#define LCD_EN     2



/* Masks for configuring the DataBus and Control Bus direction */
#define PortDataBusConfig ((1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))
#define PortCtrlBusConfig ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))
#define LCD_dataBusMask   ((1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))

/* local function to generate some delay */
void delay(int cnt)
{
    int i;
    for(i=0;i<cnt;i++);
}





/* Function send the a nibble on the Data bus (LCD_D4 to LCD_D7) */
void sendNibble(char nibble)
{
    LcdDataBusPort&=~(LCD_dataBusMask);                   // Clear previous data
    LcdDataBusPort|= (((nibble >>0x00) & 0x01) << LCD_D4);
    LcdDataBusPort|= (((nibble >>0x01) & 0x01) << LCD_D5);
    LcdDataBusPort|= (((nibble >>0x02) & 0x01) << LCD_D6);
    LcdDataBusPort|= (((nibble >>0x03) & 0x01) << LCD_D7);
}


/* Function to send the command to LCD. 
   As it is 4bit mode, a b
\yte of data is sent in two 4-bit nibbles */
void Lcd_CmdWrite(char cmd)
{
    sendNibble((cmd >> 0x04) & 0x0F);   //Send higher nibble
    LcdControlBusPort &= ~(1<<LCD_RS); // Send LOW pulse on RS pin for selecting Command register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN);

    delay(10000);

    sendNibble(cmd & 0x0F);            //Send Lower nibble
    LcdControlBusPort &= ~(1<<LCD_RS); // Send LOW pulse on RS pin for selecting Command register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN); 

    delay(10000);
}



void Lcd_DataWrite(char dat)
{
    sendNibble((dat >> 0x04) & 0x0F);   //Send higher nibble
    LcdControlBusPort |= (1<<LCD_RS);  // Send HIGH pulse on RS pin for selecting data register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN);

     delay(10000);

    sendNibble(dat & 0x0F);            //Send higher nibble
    LcdControlBusPort |= (1<<LCD_RS);  // Send HIGH pulse on RS pin for selecting data register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN); 

    delay(10000);
}

void LCD_WriteString(const char *ptr){
	
	while(*ptr){
		Lcd_DataWrite(*ptr++);
	}
}

int main( void )
{
    char i,a[]={"Engineers Garage"};
    SystemInit();                              //Clock and PLL configuration

    LcdDataBusDirnReg = PortDataBusConfig;    // Configure all the LCD pins as output
    LcdCtrlBusDirnReg = PortCtrlBusConfig;


    Lcd_CmdWrite(0x02);                // Initialize Lcd in 4-bit mode
    Lcd_CmdWrite(0x28);                // enable 5x7 mode for chars 
    Lcd_CmdWrite(0x0E);                // Display OFF, Cursor ON
    Lcd_CmdWrite(0x01);                // Clear Display
    Lcd_CmdWrite(0x80);                // Move the cursor to beginning of first line
 
		LCD_WriteString("Hello World!!");
    while(1);
}