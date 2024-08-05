#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
    /*DDRD=0xff;
    uint8_t a[]={0x01,0x02,0x04,0x08},i;
    while(1)
    {
        for(i=0;i<4;i++)
        {
            PORTD|=a[i];
            _delay_ms(500);
        }
        for(i=0;i<4;i++)
        {
            PORTD&=~a[i];
            _delay_ms(500);
        }
    }*/
    
    /*DDRD=0xff;
    DDRC=0x00;
    uint8_t a[]={0x01,0x02,0x04,0x08},i=0;
    while(1)
    {
        if((PINC&0x01)==0x01)
        {
            i++;
            while((PINC&0x01)==0x01);
        }
            PORTD=a[i];
    }*/
    /*uint8_t i=0;
    DDRD=0xff;
    DDRC=0x00;
    while(1)
    {
        if((PINC&0x01)==0x01)
        {
            i++;
        while((PINC&0x01)==0x01);
        }
        if(i==1)
        {
            PORTD=0x00;
        }
        if(i==2)
        {
            PORTD=0x01;
        }
        if(i>2)
        {
            i=1;
        }
    }*/
}
