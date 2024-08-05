/* 
 * File:   I2C_MASTER.h
 * Author: Sofcon_Lab2
 *
 * Created on 16 January, 2024, 9:47 PM
 */

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "HEADER.h"
    
#define READ  1
#define WRITE 0

#define SLAVE_ADDRESS 0x24
    
#define TW_START                 0x08
#define TW_REP_START             0x10
#define TW_MT_SLA_ACK            0x18
#define TW_MR_SLA_ACK            0x40
#define TW_MT_SLA_NACK           0x20
#define TW_MR_SLA_NACK           0x48
#define TW_MT_DATA_ACK           0x28
    
    void I2C_MasterInitialize();
    uint8_t I2C_SendStartBit(uint8_t Address);
    uint8_t I2C_SendREPStartBit(uint8_t Address);
    void I2C_WaitStartBit(uint8_t Address);
    void I2C_SendStopBit( void );
    uint8_t I2C_WriteData(uint8_t data);
    uint8_t I2C_ReadACK( void );
    uint8_t I2C_ReadNACK( void );

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_MASTER_H */

