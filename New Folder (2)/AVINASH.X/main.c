#define F_CPU 1000000UL
#include<avr/io.h>
#include <util/delay.h>
int main()
{
    int i,arr[]={0X01,0X02,0X04,0X08,0X10,0X20,0X40,0X80};
    DDRD =0Xff;
    while(1)  
    {
       for(i=0;i<=8;i++)
       {
           PORTD|=arr[i];
           _delay_ms(500);
       }
       PORTD=0x00;
        for(i=8;i>=0;i--)
       {
           PORTD|=arr[i];
           _delay_ms(500);
       }
       PORTD=0x00;
    }
    
    
}
    
        
        
    
