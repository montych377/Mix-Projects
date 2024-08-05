#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
    int i,arr[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
    DDRD=0Xff;
    DDRC=0X01;
    while(1)
    {
        for(i=0;i<=9;i++)
        {
            PORTD=arr[i];
            _delay_ms(1000);
        }
    }
}