#include <lpc17xx.h>

#define I2C1_CONSET (1<<2)  // Start condition bit (STA)
#define I2C1_CONCLR (1<<4)  // Clear bit
#define I2C1_CONAA  (1<<2)  // Assert acknowledge bit (AA)
#define I2C1_CONSI  (1<<3)  // I2C interrupt bit
#define I2C1_CONSTO (1<<4)  // STOP bit
#define I2C1_CONSTA (1<<5)  // Repeated start condition bit (STO)

void I2C_Init(void) {
    // Configure the I2C0 peripheral
    LPC_PINCON->PINSEL0 &= ~(0xF << 4);   // Clear bits 4-7 for SDA0 and SCL0
    LPC_PINCON->PINSEL0 |= (0xA << 4);    // Set bits 4 and 6 for SDA0 and SCL0

    // Initialize the I2C0 peripheral
    LPC_I2C1->I2CONSET = 0x40;    // Enable I2C
    LPC_I2C1->I2SCLH = 75;       // Set SCL clock rate (for 100 kHz)
    LPC_I2C1->I2SCLL = 75;       // Set SCL clock rate (for 100 kHz)
}

void I2C_Start(void) {
    LPC_I2C1->I2CONSET = I2C1_CONSET;  // Set STA bit to initiate a START condition
    LPC_I2C1->I2CONCLR = I2C1_CONSI;   // Clear SI bit
    while ((LPC_I2C1->I2CONSET & I2C1_CONSI) == 0);  // Wait for SI bit to be set
}

void I2C_Stop(void) {
    LPC_I2C1->I2CONSET = I2C1_CONSTO;  // Set STO bit to initiate a STOP condition
    LPC_I2C1->I2CONCLR = I2C1_CONSI;   // Clear SI bit
}

void I2C_Write(uint8_t data) {
    LPC_I2C1->I2DAT = data;            // Load data into the data register
    LPC_I2C1->I2CONCLR = I2C1_CONSI;   // Clear SI bit
    while ((LPC_I2C1->I2CONSET & I2C1_CONSI) == 0);  // Wait for SI bit to be set
}

int main(void) {
    SystemInit();
    I2C_Init();
 

    while (1) {
			I2C_Start(); // Send the start condition
			I2C_Write(0x50); // 7-bit address of the Arduino (change as needed)
			I2C_Write('A'); // Send the character 'A'

			I2C_Stop(); // Send the stop condition
					// Your main code here
    }
    return 0;
}
