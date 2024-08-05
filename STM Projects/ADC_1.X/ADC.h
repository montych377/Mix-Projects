/* 
 * File:   ADC.h
 * Author: Sofcon_Lab2
 *
 * Created on 8 April, 2023, 9:50 AM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "LCD.h"
    
    void ADC_Initialize( void );
    uint16_t ADC_Read(uint8_t channel);



#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

