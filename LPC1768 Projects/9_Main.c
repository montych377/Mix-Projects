#include <LPC17xx.h>

typedef enum{
	
	LED1 = 0,
	LED2 ,
	LED3,
	LED4
}typedef_led;

typedef struct {
	
	uint32_t port;
	uint32_t pin;
}Typedef_Led_Config;

const Typedef_Led_Config led1 = {1,LED1};
const Typedef_Led_Config led2 = {1,LED2};
const Typedef_Led_Config led3 = {1,LED3};
const Typedef_Led_Config led4 = {1,LED4};

void LED_Initialize(Typedef_Led_Config pin){
	
	LPC_GPIO
	
	_TypeDef* gpio_port = (LPC_GPIO_TypeDef*) LPC_GPIO_BASE;
	gpio_port->FIODIR |= (1<<pin.pin);
}

void GPIO_Set_High(Typedef_Led_Config pin){
	
	LPC_GPIO_TypeDef* gpio_port = (LPC_GPIO_TypeDef*) LPC_GPIO_BASE;
	gpio_port->FIOSET |= (1<<pin.pin);
}

void GPIO_Set_Low(Typedef_Led_Config pin){
	
	LPC_GPIO_TypeDef* gpio_port = (LPC_GPIO_TypeDef*) LPC_GPIO_BASE;
	gpio_port->FIOCLR |= (1<<pin.pin);
}

void delay(uint32_t ms){
	
	volatile uint32_t i=0;
	for(i=0;i<ms;i++);
	
}
int main( void  ){
	
	LED_Initialize(led1);
	LED_Initialize(led2);
	LED_Initialize(led3);
	LED_Initialize(led4);
	
	while(1){
		
		GPIO_Set_High(led1);
		delay(1000000);
		
		GPIO_Set_High(led2);
		delay(1000000);
		
		GPIO_Set_High(led3);
		delay(1000000);
		
		GPIO_Set_High(led4);
		delay(1000000);
		
		GPIO_Set_Low(led1);
		GPIO_Set_Low(led2);
		GPIO_Set_Low(led3);
		GPIO_Set_Low(led4);
		delay(1000000);
		
	}
	
}
