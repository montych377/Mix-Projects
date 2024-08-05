#include <LPC17xx.h>


#define BAUDRATE           9600

#define SBIT_WordLenght    0x00u

#define SBIT_DLAB          0x07u

#define SBIT_FIFO          0x00u

#define SBIT_RxFIFO        0x01u

#define SBIT_TxFIFO        0x02u

#define SBIT_RDR           0x00u

#define SBIT_THRE          0x05u


void UART0_Initialization(uint32_t baudrate);
void UART0_TransmitChar(char ch);
char UART0_ReceiveChar( void );
void UART0_TransmitString(char *ptr);


int main( void )
{
	
	char ch=0;
	LPC_GPIO2 ->FIODIR = 0xff;
	SystemInit();
	UART0_Initialization(BAUDRATE);  

	
	UART0_TransmitString("HELLO WORLD\r\n");
	while(1)
	{
			UART0_TransmitString("Hello From LPC1768 Microcontroller\n");
			ch = UART0_ReceiveChar(); 
			UART0_TransmitChar('A');
		  for(int i=0;i<5000000;i++);
		
		if(ch == 'A') {
			
			LPC_GPIO2->FIOSET = 0x01;
			UART0_TransmitString("LED 1 ON\r\n");
		}
		if(ch == 'B'){
			
			LPC_GPIO2->FIOSET = 0x02;
			UART0_TransmitString("LED 2 ON\r\n");
		}
		
		if(ch == 'C') {
			
			LPC_GPIO2->FIOCLR = 0x01;
			UART0_TransmitString("LED 1 OFF\r\n");
		}
		if(ch == 'D'){
			
			LPC_GPIO2->FIOCLR = 0x02;
			UART0_TransmitString("LED 2 OFF\r\n");
		}
	}       
}

void UART0_Initialization(uint32_t baudrate)
{
    uint32_t UART0_CLOCK = 0,UART0_REGVALUE = 0;


    LPC_PINCON->PINSEL0 |= 0x00000050;       

    LPC_UART0->FCR = (1<<SBIT_FIFO) | (1<<SBIT_RxFIFO) | (1<<SBIT_TxFIFO); 
    LPC_UART0->LCR = (0x03<<SBIT_WordLenght) | (1<<SBIT_DLAB);   
	
		UART0_CLOCK = SystemCoreClock/4;
	
    UART0_REGVALUE = ( UART0_CLOCK / (16 * baudrate )); 
    LPC_UART0->DLL =  UART0_REGVALUE & 0xFF;
    LPC_UART0->DLM = (UART0_REGVALUE << 8) & 0xFF ;

    LPC_UART0->LCR &= ~(1<<SBIT_DLAB); 
}

void UART0_TransmitChar(char ch)
{
    while(!(LPC_UART0->LSR&(1<<SBIT_THRE))); 
    LPC_UART0->THR=ch;                             
}

char UART0_ReceiveChar( void )
{
    char ch; 
    while(!(LPC_UART0->LSR&(1<<SBIT_RDR)));  
    ch = LPC_UART0->RBR;                              
    return ch;
}

void UART0_TransmitString(char *ptr) {
	
	while(*ptr != '\0') {
		
		UART0_TransmitChar(*ptr++);
	}
}
		
