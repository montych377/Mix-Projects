#define F_CPU 1000000UL
#include<avr/io.h>

 int main()
 {
     DDRD=0Xff;
     while(1)
     {
         PORTD=0X3F;
     }
 }
