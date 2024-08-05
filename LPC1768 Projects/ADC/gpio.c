
#include <lpc17xx.h>
#include "stdutils.h"
#include "gpio.h"


void GPIO_PinFunction(gpioPins_et enm_pinNumber, uint8_t var_pinFunction_u8)
{
    uint8_t var_portNumber_u8;
	uint32_t *ptr_PINCON;
	uint8_t var_pinNumber_u8 = enm_pinNumber; 

    var_portNumber_u8 =  (enm_pinNumber>>5);  //Divide the pin number by 32 go get the PORT number
    var_pinNumber_u8  =   var_pinNumber_u8 & 0x1f;  //lower 5-bits contains the bit number of a 32bit port 	

    
    var_portNumber_u8 = var_portNumber_u8*2;
    if(var_pinNumber_u8>=16)
    {
       var_portNumber_u8++; 
       var_pinNumber_u8 = var_pinNumber_u8-16;
    }
    
    var_pinNumber_u8 = var_pinNumber_u8 * 2;
    
    ptr_PINCON    = ((uint32_t *)&LPC_PINCON->PINSEL0  + var_portNumber_u8);
    
    *(uint32_t *)(ptr_PINCON) &= ~(0x03UL << var_pinNumber_u8);
	*(uint32_t *)(ptr_PINCON) |= (((uint32_t)var_pinFunction_u8) << var_pinNumber_u8);
    
}



/***************************************************************************************************
                  void GPIO_PinDirection(gpioPins_et enm_pinNumber, uint8_t var_pinDirn_u8)
 ***************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be updated.
                             Refer the gpio.h for pin numbering.
                gpioDirection_et: Direction to be configured ie. INPUT/OUTPUT.
                              

 * Return value    : none

 * description :This function sets the specified direction as INPUT/OUTPUT.  
 ***************************************************************************************************/
void GPIO_PinDirection(gpioPins_et enm_pinNumber, uint8_t var_pinDirn_u8)
{

    uint8_t var_portNumber_u8;
    LPC_GPIO_TypeDef *LPC_GPIO_PORT;
	uint8_t var_pinNumber_u8 = enm_pinNumber; 

    var_portNumber_u8 =  (enm_pinNumber>>5);  //Divide the pin number by 32 go get the PORT number
    var_pinNumber_u8  =   var_pinNumber_u8 & 0x1f;  //lower 5-bits contains the bit number of a 32bit port 	

    /* Go to particular port after decoding from the pin number and 
        set the direction as specified*/
    
    LPC_GPIO_PORT = (LPC_GPIO_TypeDef*)(LPC_GPIO_BASE + ((var_portNumber_u8) << 5));
    util_UpdateBit(LPC_GPIO_PORT->FIODIR,var_pinNumber_u8,var_pinDirn_u8);   
}









/***************************************************************************************************
            void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t var_pinValue_u8)
 ***************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be updated.
                             Refer the gpio.h for pin numbering.
                gpioValue_et: Value to be updated(LOW/HIGH) on the selected pin.
                              

 * Return value    : none

 * description :This function updates the specified value on the selected pin.  
                Before updating the pins status, the pin function should be selected and then
                the pin should be configured as OUTPUT 
***************************************************************************************************/
void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t var_pinValue_u8)
{

    uint8_t var_portNumber_u8;
    LPC_GPIO_TypeDef *LPC_GPIO_PORT;
	uint8_t var_pinNumber_u8 = enm_pinNumber; 

    var_portNumber_u8 =  (enm_pinNumber>>5);  //Divide the pin number by 32 go get the PORT number
    var_pinNumber_u8  =   var_pinNumber_u8 & 0x1f;  //lower 5-bits contains the bit number of a 32bit port 	

    /* Go to particular port after decoding from the pin number and 
        update the value of the specified pin*/
    
    LPC_GPIO_PORT = (LPC_GPIO_TypeDef*)(LPC_GPIO_BASE + ((var_portNumber_u8) << 5));
    util_UpdateBit(LPC_GPIO_PORT->FIOPIN,var_pinNumber_u8,var_pinValue_u8);                
}








/***************************************************************************************************
                    uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber)
 ***************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be read.
                             Refer the gpio.h for pin numbering.

 * Return value    : 
                 uint8_t:    Status of the specified pin.

 * description :This function returns the status of the selected pin.
                Before reading the pins status, the pin function should be selected and accordingly
                the pin should be configured as INPUT 
 ***************************************************************************************************/
uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber)
{
    uint8_t returnStatus = 0;
    uint8_t var_portNumber_u8;
    LPC_GPIO_TypeDef *LPC_GPIO_PORT;
	uint8_t var_pinNumber_u8 = enm_pinNumber; 

    var_portNumber_u8 =  (enm_pinNumber>>5);  //Divide the pin number by 32 go get the PORT number
    var_pinNumber_u8  =   var_pinNumber_u8 & 0x1f;  //lower 5-bits contains the bit number of a 32bit port 	

    /* Go to particular port after decoding from the pin number and read the pins status */

    LPC_GPIO_PORT = (LPC_GPIO_TypeDef*)(LPC_GPIO_BASE + ((var_portNumber_u8) << 5));    
    returnStatus = util_IsBitSet(LPC_GPIO_PORT->FIOPIN,var_pinNumber_u8);
                  
    return returnStatus;
}
