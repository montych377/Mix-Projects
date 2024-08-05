#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
    int counter = 0;
    int arr[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
    DDRD = 0xff;
    DDRC = 0x00;
    while(1)
    {
        if(PINC & 0x01)
        {
            counter++;
            while(PINC & 0x01);
        }
        PORTD = arr[counter];
    }
}
