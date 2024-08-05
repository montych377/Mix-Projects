#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define GPIO_PIN_0 0
#define GPIO_PIN_SET    1
#define GPIO_PIN_RESET  0
#define GPIO_PIN_INPUT  0
#define GPIO_PIN_OUTPUT 1
// Define a structure for GPIO registers
typedef struct {
    volatile uint8_t PIN;  // Input Pins Address
    volatile uint8_t DDR;  // Data Direction Register
    volatile uint8_t PORT; // Data Register
} GPIO_TypeDef;

// Define base addresses for GPIO ports
#define GPIOB ((GPIO_TypeDef *)0x36)  // Base address for GPIOB
#define GPIOC ((GPIO_TypeDef *)0x33)  // Base address for GPIOC
#define GPIOD ((GPIO_TypeDef *)0x30)  // Base address for GPIOD


void HAl_GPIO_WritePin(GPIO_TypeDef *GPIOx,uint8_t Pin,uint8_t state)
{
    GPIOx->PORT = (state << Pin);
}
void HAl_GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint8_t Pin)
{
    GPIOx->PORT ^= (1 << Pin);
}

void HAL_GPIO_DirectionPin(GPIO_TypeDef *GPIOx,uint8_t Pin,uint8_t dir)
{
    GPIOx->DDR  = (dir << Pin);
}


int main(void) {
    HAL_GPIO_DirectionPin(GPIOB,GPIO_PIN_0,GPIO_PIN_OUTPUT);

    while (1) {
        HAl_GPIO_TogglePin(GPIOB,GPIO_PIN_0);

        _delay_ms(500);
    }

    return 0;
}
