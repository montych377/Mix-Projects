#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#define BUTTON PCO
int main()
{
    DDRD=0xff;
    DDRC=0x03;
    char arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
    int i=0;
    int j=0;
    int size = sizeof(arr)/sizeof(arr[0]);
    while(1)
    {
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        { 
        PORTC=0x01;
        PORTD=arr[j];
        _delay_ms(1000);
        PORTC=0x02;
        PORTD=arr[i];
         _delay_ms(1000); 
        }
    }
    }  
}
     
    
    
    
    
