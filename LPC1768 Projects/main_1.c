#include <reg51.h>

void UART_Init()
{
	TMOD = 0x20;
	TH1 = 0XFD;
	SCON = 0X50;
	TR1 = 1;
}

void UART_TX(unsigned char dat)
{	
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}

char UART_RX( void )
{
	while(!RI);
	RI = 0;
	return SBUF;
}
void UARt_String(unsigned char *ptr)
{
	while(*ptr)
	{
		UART_TX(*ptr++);
	}
	
}
void delay(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<1000;j++)
		{
			
		}
	}
}
int main()
{
	UART_Init();
	UARt_String("jhdkagdea");
	while(1)
	{
		
		char x = UART_RX();
		UART_TX(x);
		delay(100);
	}
}