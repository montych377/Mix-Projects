#include "stm32f10x.h"

void delay(long cycles);
void gpio_ports_enable(void);

int main(void)
{
    gpio_ports_enable();
    for(;;) 
    {
          GPIOC->BSRR = GPIO_BSRR_BS13; 
          delay(5000000);
          GPIOC->BSRR = GPIO_BSRR_BR13; 
          delay(5000000); 
			
			
			
    }    
}

void gpio_ports_enable(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |     RCC_APB2ENR_IOPBEN|RCC_APB2ENR_IOPCEN; //ports A & B clock enabled
  GPIOC->CRH = 0x44344444; //Pin C13 enable. If you don't like number 13, use pin C_1_P.M. LOL
}

void delay(long cycles)
{
  while(cycles >0)
  cycles--; // Some stupid delay, it is not in milliseconds or microseconds, but rather in some 'wasted clock cycles'
}

