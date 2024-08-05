#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
    DDRD=0Xff;
    DDRC=0X00;
    int  arr[]={0,0X01,0X02,0X04,0X08,0X10,0X20,0X040,0X080};
    int i=0;
    while(1)
    {
        if((PINC&0X01)==0X01)
        {
            i--;
           while((PINC&0X01)==0X01); 
         }
         PORTD =arr[i];
         
         if(i<0)
         {
             i=8;
         }
    }
       
}