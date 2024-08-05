#include <LPC17xx.h>

void delay(int ms) {
	
	uint32_t i=0,j=0;
	
	for(i=0;i<ms;i++) {
		
		for(j=0;j<5000;j++);
	}
}
// Function for the initialization I2C0 bus
void I2C0_InitMasterMode (void)
{
    // Set I2C bus active
    LPC_SC->PCONP         |= (1<<7);          // Set the I2C0 bus power
    LPC_SC->PCLKSEL0     &=~(1<<14)|(1<<15);  // Set PCLK clock for I2C0 bus
                                              // bits 14 and 15 = 0 -> PCLK_peripheral = CCLK/4
                                              // CCLK = 100 MHz, PCLK = 100 MHz/4 = 25 MHz for bitrate frequency

    // First configure pins P0.27 and P0.28 as normal GPIO pins
    LPC_PINCON->PINSEL1 &=~(1<<22);           // Set pin P0.27 as GPIO
    LPC_PINCON->PINSEL1 &=~(1<<23);           // Set pin P0.27 as GPIO
    LPC_PINCON->PINSEL1 &=~(1<<24);           // Set pin P0.28 as GPIO
    LPC_PINCON->PINSEL1 &=~(1<<25);           // Set pin P0.28 as GPIO

    // Now configure pins P0.27 and P0.28 as I2C0 bus pins
    LPC_PINCON->PINSEL1 |= (1<<22);           // Set pin P0.27 as SDA0 I2C0
    LPC_PINCON->PINSEL1 &=~(1<<23);           // Set pin P0.27 as SDA0 I2C0
    LPC_PINCON->PINSEL1 |= (1<<24);           // Set pin P0.28 as SCL0 I2C0
    LPC_PINCON->PINSEL1 &=~(1<<25);           // Set pin P0.28 as SCL0 I2C0

    // Reset (clear) the STAC andSIC bits for configure the Master Mode I2C0 bus
    LPC_I2C0->I2CONCLR =  (1<<3);              // Reset (clear) SIC  bit (I2C interrupt)
    LPC_I2C0->I2CONCLR =  (1<<5);              // Reset (clear) STAC bit (START flag)

    /* Calculate and set the proper value of I2C0 clock registers for 100 kHz bitrate frequency
     * I2C0_Freq = PCLK/(SCLH + SCLL)
     * SCLH + SCLL = 25000 kHz/100 kHz = 250
     * SCLH = SCLL = 125 => 50% duty cycle
    */
    LPC_I2C0->I2SCLH    = 125;                 // SCL prescaler High register
    LPC_I2C0->I2SCLL    = 125;                 // SCL prescaler Low register

    // Configure I2C0 pin in the Standard Drive Mode
    LPC_PINCON->I2CPADCFG &=~(1<<0)|(1<<1)|(1<<2)|(1<<3);   // Standard Drive Mode (100 kbps)
                                                            // bit 0 reset to 0 - The SDA0 pin is in the standard drive mode
                                                            // bit 1 reset to 0 - The SDA0 pin has I2C glitch filtering and slew rate control enabled
                                                            // bit 2 reset to 0 - The SCL0 pin is in the standard drive mode
                                                            // bit 3 reset to 0 - The SCL0 pin has I2C glitch filtering and slew rate control enabled

    NVIC_EnableIRQ (I2C0_IRQn);                // Set the I2C0 Interrupts in the Global Interrupts; active
    LPC_I2C0->I2CONSET |= (1<<6);              // Enable the I2C0; bus bit 6
}

// The function for generate START condition
void I2C0_Start (void)
{
    LPC_I2C0->I2CONSET = (1<<5);      // Set the STA bit; bit 5
}

// I2C0 Interrupt function; Each Status Register change will cause enter into the I2C0_IRQHandler function
void I2C0_IRQHandler (void)
{
    LPC_GPIO0->FIOSET |= (1<<22);    // Turn the LED 1 P0.22 on

    switch (LPC_I2C0->I2STAT)        // Read value of the I2C0 Status Register
    {
        // I2C0 Status register value '0x08' meaning: 'A START condition has been transmitted'
        // Next step to do: 'SLA+W will be transmitted; ACK bit will be received'
        case 0x08:
            // Send on the I2C0 "Slave Device Address" = 160 (b0 = 0 -> Write to the Slave device)
            LPC_I2C0->I2DAT     = 160;       // Slave Address is '1010 00X' where X is Read (R=1) or Write (W=1) bit
            LPC_I2C0->I2CONSET  = (1<<2);    // Set the AA bit (Assert Acknowledge)
            LPC_I2C0->I2CONCLR  = (1<<3);    // Reset the SI bit
            LPC_GPIO2->FIOSET   |=(1<<2);    // Turn the LED on P2.2 on
        break;                               // Go out of the switch cases

        // Status value meaning: 'SLA+W has been transmitted; ACK has been received'
        // Next step to do: 'Data byte will be transmitted; ACK bit will be received'
        case 0x18:
            // Send on the I2C0 "First Word Data" = 0
            LPC_I2C0->I2DAT     =  0;
            LPC_I2C0->I2CONSET  = (1<<2);    // Set the AA bit (Assert Acknowledge)
            LPC_I2C0->I2CONCLR  = (1<<3);    // Reset the SI bit
            LPC_GPIO2->FIOSET   |=(1<<3);    // Turn the LED on P2.3 on
        break;                               // Go out of the switch cases

        // Status value meaning: 'Data byte in I2DAT has been transmitted; ACK has been received'
        // Next step to do: 'Data byte will be transmitted; ACK bit will be received'
        case 0x28:
            // Send on the I2C0 "Second Word Data" = 0
            LPC_I2C0->I2DAT     =  0;    
            LPC_I2C0->I2CONSET  = (1<<2);    // Set the AA bit (Assert Acknowledge)
            LPC_I2C0->I2CONCLR  = (1<<3);    // Reset the SI bit
            LPC_GPIO2->FIOSET   =(1<<4);     // Turn the LED on P2.4 on
        break;                               // Go out of the switch cases

        // When I2C0 Status register will give other values then show this value on the LEDs 2-6 and turn the LED 1 off
        default:
            LPC_GPIO0->FIOCLR |= (1<<22);                               // Turn the LED 1 P0.22 off
            LPC_GPIO2->FIOSET |= (1<<7);                                // Turn the LED 7 P2.7 on
            LPC_GPIO2->FIOCLR |= (1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6);    // Turn the LED 6-2 P2.2-P2.6 off
            LPC_GPIO2->FIOSET |= ((LPC_I2C0->I2STAT) >> 3);             // Shift 3 bits right I2C0 Status Register
                                                                        // 5 bits 7-3 give the actual status information about the I2C interface
        break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------- MAIN PROGRAM ---------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------------------------------------------------- //

/* 7 LEDs meaning:
 * LED 1 on the pin P0.22 - is turned on only if the program enters into the I2C0 Interrupt (START condition) (apart of enters into the 'default');
 * LED 2 on the pin P2.2  - is turned on only if the program enters into the I2C0 Interrupt and enters into the "case" with 0x08 value;
 * LED 3 on the pin P2.3  - is turned on only if the program enters into the I2C0 Interrupt and enters into the "case" with 0x28 value;
 * LED 5 on the pin P2.5  - is not used as a single LED;
 * LED 6 on the pin P2.6  - is not used as a single LED;
 * LED 7 on the pin P2.7  - is turned on only if the program enters into the I2C0 Interrupt and enters into the "default": then 'I2C Status Register' value (bits 7-3)
 *                          is displayed on the five LEDs (b7-LED5, b6-LED5, b5-LED4, b4-LED3, b3-LED2) so turning on LEDs combination like: 00000X gives 0x08, 
 *                          000X0X gives 0x28, etc. Just write three zeros on the right side.
 *                        - is toggling only if the program goes out of the I2C0 Interrupt and enters into the main 'for (;;)' loop in the main program;
*/

// Main program
int main (void)
{
    // Set the pins P2.3-P2.7 as the I2STAT register mirror in LEDs lights
    LPC_GPIO2->FIODIR |= (1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
    LPC_GPIO2->FIOCLR |= (1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);

    // Set the pin P0.22 as output with LED
    LPC_GPIO0->FIODIR |= (1<<22);        // Pin GPIO P0.22 as an output
    LPC_GPIO0->FIOCLR |= (1<<22);        // An output in low state

    // Initialization the I2C0 bus
    I2C0_InitMasterMode ();              // Initialization the I2C0 bus with 100 kbps bitrate frequency
    I2C0_Start ();                       // Generate the START condition, if START bit is set then program goes into "I2C0_IRQHandler"

    uint8_t a = 0;                       // A temporary 8-bit variable just for using 'for (;;)' loop below

    // Toggle the LED 7 on the pin P2.7
    for (a=0; a<255; a++)
    {
        LPC_GPIO2->FIOPIN     ^= (1<<7); // Turn the LED on P2.7 on
        delay (100);                     // Just wait for 100 ms
    }
}