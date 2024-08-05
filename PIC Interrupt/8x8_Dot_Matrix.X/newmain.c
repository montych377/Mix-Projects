#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// Function to initialize the ports
void init_ports() {
    DDRB = 0xFF; // Set PORTB as output for rows
    DDRD = 0xFF; // Set PORTD as output for columns
    PORTB = 0x00; // Initialize PORTB to low
    PORTD = 0x00; // Initialize PORTD to low
}
void shift_left(uint8_t pattern[8]) {
    for (int i = 0; i < 8; i++) {
        pattern[i] = (pattern[i] >> 1) ;
    }
}
// Function to display a pattern on the 8x8 dot matrix display
void display_pattern(uint8_t pattern[8]) {
    for (int i = 0; i < 8; i++)
    {
        PORTD = (1 << i); // Select the current row
        PORTB = pattern[i]; // Output the column data
        _delay_ms(1); // Short delay to prevent flickering
    }
    
}

int main(void) {
    // Initialize the ports
    init_ports();
    
    // Define a pattern to display (example: a smiley face)
    uint8_t pattern[8] = 
    {
0b00001000,
  0b00001100,
  0b11111110,
  0b11111111,
  0b11111110,
  0b00001100,
  0b00001000,
  0b00000000

    };
    uint8_t pattern1[8] = 
    {
        0b00000000,
        0b00000010,
        0b00000010,
        0b00001010,
        0b00001010,
        0b00101010,
        0b00101010,
        0b10101010
    };
    uint8_t j = 0;
    // Main loop
    while (1)
    {
        if(j==8)
        {
            display_pattern(pattern);
            goto label;
        }
        label:    
            display_pattern(pattern); // Display the pattern
            _delay_ms(200);
            shift_left(pattern);
        j++;
        
        
//        
//        display_pattern(pattern1); // Display the pattern
//        _delay_ms(200);
//        shift_left(pattern1);
    }

    return 0;
}
