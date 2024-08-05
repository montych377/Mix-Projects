
/*#include <LPC17xx.h>


void _dalay_ms( uint32_t ms );
void UART_Initialize( void );
void UART_TransmitChar(uint8_t data);
uint8_t UART_ReceiveChar( void );
void UART_TransmitString( uint8_t *ptr);
int main( void ) {
	
	while(1) {
		
		
	}
}

void _dalay_ms( uint32_t ms ){
	
	uint32_t i=0,j=0;
	 for(i=0;i<ms;i++){
		 
		 for(j=0;j<5000;j++){
			 
			 __NOP();
		 }
	 }
}

void UART_Initialize( void ){
	
	
}
void UART_TransmitChar(uint8_t data);
uint8_t UART_ReceiveChar( void );
void UART_TransmitString( uint8_t *ptr);

*/



#include <LPC17xx.h>
#define BAUDRATE     9600
#define  WRDL       (0x03<<0)
#define THRE        (1<<5)
#define RDR         (1<<0)
#define MULVAL      15
#define DIVADDVAL   2
#define Ux_FIFO_EN  (1<<0)
#define RX_FIFO_RST (1<<1)
#define TX_FIFO_RST (1<<2)
#define DLAB_BIT    (1<<7)
#define CARRIAGE_RETURN 0x0D

void UART0_Init(uint32_t BaudRate);
void UART0_Write(char data);
char UART0_Read( void );
void UART0_String(char *ptr);
static char data1;

int main(void)
{
	UART0_Init(BAUDRATE);
	UART0_String("HELLO WORLD");
	while(1)          
	{
		char	data = UART0_Read();
		UART0_Write(data);
	}
}

void UART0_Write(char txData)
{
	while(!(LPC_UART0->LSR & THRE));
	LPC_UART0->THR = txData;
}

char UART0_Read( void ) {
	
	while(!(LPC_UART0->LSR & RDR));
	data1 = LPC_UART0->RBR;
	return data1;
	
}

void UART0_Init(uint32_t BaudRate)
{
	uint32_t UART0_PCLK = 0;
	uint32_t VAR_PCLK = 0;
	uint32_t REG_VALUE = 0;
	
	LPC_PINCON->PINSEL0 &= (unsigned int)~0x000000F0;
	LPC_PINCON->PINSEL0 |= 0x00000050;  

	LPC_UART0->FCR |= Ux_FIFO_EN | RX_FIFO_RST | TX_FIFO_RST;
	LPC_UART0->FDR = (MULVAL<<4) | DIVADDVAL;
	LPC_UART0->LCR = (DLAB_BIT)|(WRDL);
	
	UART0_PCLK = (LPC_SC->PCLKSEL0>>6) & 0x03;
	
	switch(UART0_PCLK)
	{
		case 0x00:
			
			VAR_PCLK = SystemCoreClock/4;
			break;
		
		case 0x01:
			
			VAR_PCLK = SystemCoreClock;
			break;
		
		case 0x02:
			
			VAR_PCLK = SystemCoreClock/2;
			break;
		case 0x03:
			
			VAR_PCLK = SystemCoreClock/8;
			break;
	}
	
	REG_VALUE = ( VAR_PCLK / (16 * BaudRate )); 
	LPC_UART0->DLL =  REG_VALUE & 0xFF;
	LPC_UART0->DLM = (REG_VALUE >> 0x08) & 0xFF;
	
}

void UART0_String(char *ptr){
	
	while(*ptr != '\0') {
		
		UART0_Write(*ptr++);
	}
}

