#include <LPC17xx.h>
#include <stdio.h>

// LCD Configuration (Modify this according to your LCD)
#define LCD_DATA_PORT LPC_GPIO2
#define LCD_CTRL_PORT LPC_GPIO1
#define RS_PIN (1 << 24)
#define RW_PIN (1 << 25)
#define EN_PIN (1 << 26)

void delay_ms(uint32_t ms) {
    uint32_t i;
    for (i = 0; i < ms * 10000; i++);
}

void LCD_Command(uint8_t cmd) {
    LCD_DATA_PORT->FIOPIN0 = cmd << 2; // Assuming data pins are connected to P2.2 to P2.9
    LCD_CTRL_PORT->FIOPIN0 &= ~RS_PIN; // RS low for command
    LCD_CTRL_PORT->FIOPIN0 &= ~RW_PIN; // RW low for write
    LCD_CTRL_PORT->FIOPIN0 |= EN_PIN;  // Enable high
    delay_ms(1);
    LCD_CTRL_PORT->FIOPIN0 &= ~EN_PIN; // Enable low
    delay_ms(1);
}

void LCD_Data(uint8_t data) {
    LCD_DATA_PORT->FIOPIN0 = data << 2; // Assuming data pins are connected to P2.2 to P2.9
    LCD_CTRL_PORT->FIOPIN0 |= RS_PIN;   // RS high for data
    LCD_CTRL_PORT->FIOPIN0 &= ~RW_PIN;  // RW low for write
    LCD_CTRL_PORT->FIOPIN0 |= EN_PIN;   // Enable high
    delay_ms(1);
    LCD_CTRL_PORT->FIOPIN0 &= ~EN_PIN;  // Enable low
    delay_ms(1);
}

void LCD_Init() {
    // Initialize your LCD here (e.g., configure pins, set up initialization sequence)
    // This will depend on your specific LCD module.
}

void ADC_Init() {
    // Enable the ADC peripheral clock
    LPC_SC->PCONP |= (1 << 12);

    // Configure the ADC for ADC0 (Channel 0)
    LPC_PINCON->PINSEL1 |= (1 << 14); // P0.23 as AD0.0

    // Set the ADC clock divider (assuming PCLK_ADC is 25 MHz)
    LPC_ADC->ADCR = (1 << 2) | (24 << 8);
}

uint16_t ADC_Read() {
    // Start the conversion by setting the START bit in ADCR
    LPC_ADC->ADCR |= (1 << 24);

    // Wait for conversion to complete
    while (!(LPC_ADC->ADGDR & (1 << 31)));

    // Read the ADC data from ADGDR
    return (LPC_ADC->ADGDR >> 4) & 0xFFF;
}

int main( void ) {
    SystemInit();
    LCD_Init();
    ADC_Init();

    while (1) {
        uint16_t adc_value = ADC_Read();

        // Convert the ADC value to a string
        char adc_str[10];
        sprintf(adc_str, "%d", adc_value);

        // Print the string on the LCD
        // (You should replace this with your actual LCD code)

        // Delay before the next reading
        delay_ms(1000);
    }

    return 0;
}
kkk