#define F_CPU 10000000L
#include<avr/io.h>
#include<util/delay.h>
int main ()
{
    DDRD = 0xff;
  
    
    int i;
  int arr[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80} ;
    while(1)
    {
        for(i=0; i<8 ; i++)
        {
            PORTD|=arr[i];
            _delay_ms(100);
        }
        PORTD=0x00;
    }
    return 0;
}