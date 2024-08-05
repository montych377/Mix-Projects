#include <reg51.h>



int main()
{
	int i;
	unsigned char a;
	SM1 = 1;
	REN = 1;
	TMOD = 0x20;
	TH1 = TL1 = 0xFD;
	TR1 = 1;
	
	while(1)
	{
		
		SBUF = 'A';
		while(TI == 0);
		TI = 0;
		for(i = 0;i<10000;i++);

	}
	
}
	