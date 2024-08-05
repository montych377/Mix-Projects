#include <LPC17xx.h>

// CAN Controller Register Definitions
#define CAN1_BASE_ADDR  0x40040000
#define CAN1MOD         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x00)))
#define CAN1CMR         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x04)))
#define CAN1GSR         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x08)))
#define CAN1ICR         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x0C)))
#define CAN1IER         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x10)))
#define CAN1BTR         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x14)))
#define CAN1EWL         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x18)))
#define CAN1SR          (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x1C)))
#define CAN1RFS         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x20)))
#define CAN1RID         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x24)))
#define CAN1RDA         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x28)))
#define CAN1RDB         (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x2C)))
#define CAN1TFI1        (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x30)))
#define CAN1TID1        (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x34)))
#define CAN1TDA1        (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x38)))
#define CAN1TDB1        (*((volatile uint32_t *)(CAN1_BASE_ADDR + 0x3C)))

void CAN1_Init( void ) ;

void CAN1_SendMessage(uint32_t id, uint8_t *data, uint8_t len);

int main( void ) {
    
	  SystemInit();   // Initialize system clock
    CAN1_Init();    // Initialize CAN1

    uint8_t data[] = {0x01, 0x02, 0x03};
    uint32_t id = 0x123;

    while (1) {
        CAN1_SendMessage(id, data, sizeof(data));
    }
}

// Function to initialize CAN1
void CAN1_Init( void ) {
    // Power on the CAN1 peripheral
    LPC_SC->PCONP |= (1 << 13);

    // Configure CAN1 pins (P0.0 - CAN1_RD, P0.1 - CAN1_TD)
    LPC_PINCON->PINSEL0 &= ~(0x0000000F);
    LPC_PINCON->PINSEL0 |= 0x00000005;

    // Set the CAN1 controller to reset mode
    CAN1MOD = 1;

    // Set the CAN1 controller to normal operating mode
    CAN1MOD = 0;

    // Configure the CAN1 Baud Rate (assuming a 500 Kbps baud rate)
    CAN1BTR = 0x001C0002;
}

// Function to send a CAN message
void CAN1_SendMessage(uint32_t id, uint8_t *data, uint8_t len) {
	
		int i=0;
    CAN1TFI1 = (len << 16);     // Set data length
    CAN1TID1 = id;              // Set message ID

    // Copy data into CAN message buffer
    for (i = 0; i < len; i++) {
        CAN1TDA1 = data[i];
    }

    // Request transmission
    CAN1CMR = 0x21;
}
