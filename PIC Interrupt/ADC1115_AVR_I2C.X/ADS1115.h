/* 
 * File:   ADS1115.h
 * Author: Sofcon_Lab2
 *
 * Created on 16 January, 2024, 11:50 PM
 */

#ifndef ADS1115_H
#define	ADS1115_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "HEADER.h"
    
#define ADS1115_ADDR_GND (0b1001000)
#define ADS1115_ADDR_VDD (0b1001001)
#define ADS1115_ADDR_SDA (0b1001010)
#define ADS1115_ADDR_SCL (0b1001011)

/************************************************************************/
/* ADS1115 REGISTER														*/
/************************************************************************/

#define ADS1115_REG_CONVERSION	0x00
#define ADS1115_REG_CONFIG		0x01
#define ADS1115_REG_LO_THRESH	0x02
#define ADS1115_REG_HI_THRESH	0x03

/************************************************************************/
/* ADS1115 CONFIG REGISTER BIT NR										*/
/************************************************************************/

#define ADS1115_OS 			15
#define ADS1115_IMUX2 		14
#define ADS1115_IMUX1 		13
#define ADS1115_IMUX0 		12
#define ADS1115_PGA2 		11
#define ADS1115_PGA1 		10
#define ADS1115_PGA0 		9
#define ADS1115_MODE 		8
#define ADS1115_DR2 		7
#define ADS1115_DR1 		6
#define ADS1115_DR0 		5
#define ADS1115_COMP_MODE 	4
#define ADS1115_COMP_POL 	3
#define ADS1115_COMP_LAT 	2
#define ADS1115_COMP_QUE1 	1
#define ADS1115_COMP_QUE0	0

/************************************************************************/
/* ADS1115 CONFIG REGISTER BITS											*/
/************************************************************************/

// Bit 0,1
#define ADS1115_COMP_QUE_CON1			(0x0000)
#define ADS1115_COMP_QUE_CON2			(0x0001)
#define ADS1115_COMP_QUE_CON4			(0x0002)
#define ADS1115_COMP_QUE_DIS			(0x0003)

// Bit 2
#define ADS1115_COMP_LAT_NonLatching	(0x0000)
#define ADS1115_COMP_LAT_Latching		(0x0004)

// Bit 3
#define ADS1115_COMP_POL_3_ACTIVELOW	(0x0000)
#define ADS1115_COMP_POL_3_ACTIVEHIGH	(0x0008)

// Bit 4
#define ADS1115_COMP_MODE_TRADITIONAL	(0x0000)
#define ADS1115_COMP_MODE_WINDOWCOMP	(0x0010)

// Bit 5,6,7
#define ADS1115_DR_8SPS					(0x0000)
#define ADS1115_DR_16SPS				(0x0020)
#define ADS1115_DR_32SPS				(0x0040)
#define ADS1115_DR_64SPS				(0x0060)
#define ADS1115_DR_128SPS				(0x0080)
#define ADS1115_DR_250SPS				(0x00A0)
#define ADS1115_DR_475SPS				(0x00C0)
#define ADS1115_DR_860SPS				(0x00E0)

// Bit 8
#define ADS1115_MODE_CONTINUOUS			(0x0000)
#define ADS1115_MODE_SINGLE				(0x0100) 

// Bit 9,10,11
#define ADS1115_PGA_6_144				(0x0000)
#define ADS1115_PGA_4_096				(0x0200)
#define ADS1115_PGA_2_048				(0x0400)
#define ADS1115_PGA_1_024				(0x0600)
#define ADS1115_PGA_0_512				(0x0800)
#define ADS1115_PGA_0_256				(0x0A00)
#define ADS1115_PGA_0_256_2				(0x0C00)
#define ADS1115_PGA_0_256_3				(0x0E00)

// Bit 12,13,14
#define ADS1115_MUX_AIN0_AIN1			(0x0000)
#define ADS1115_MUX_AIN0_AIN3			(0x1000)
#define ADS1115_MUX_AIN1_AIN3			(0x2000)
#define ADS1115_MUX_AIN2_AIN3			(0x3000)
#define ADS1115_MUX_AIN0_GND			(0x4000)
#define ADS1115_MUX_AIN1_GND			(0x5000)
#define ADS1115_MUX_AIN2_GND			(0x6000)
#define ADS1115_MUX_AIN3_GND			(0x7000)

// Bit 15
#define ADS1115_OS_OFF					(0x0000)
#define ADS1115_OS_SINGLE				(0x8000)


uint8_t ADS1115_Write(uint8_t Address, uint8_t REG,uint16_t data);
uint16_t ADS1115_Read(uint8_t Address,uint8_t REG);
uint16_t ADS1115_ReadMultiChannel(uint8_t Address,uint8_t REG,uint8_t channel);


#ifdef	__cplusplus
}
#endif

#endif	/* ADS1115_H */

