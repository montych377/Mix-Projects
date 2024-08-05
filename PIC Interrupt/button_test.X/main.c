
//#define F_CPU 1000000UL
//#include <avr/io.h> 
//#include <util/delay.h>
//
//
//int main()
//{
//    uint8_t j=0;
//    uint8_t k=0;
//    uint8_t arr[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//    DDRD = 0xff;
//    
//    while(1) 
//    {
//        for(uint8_t i=0;i<8-j;i++){
//            
//            PORTD |= arr[i];
//            _delay_ms(50);
//            PORTD &= ~arr[i];
//            _delay_ms(50);
//            
//        }
//        PORTD |= arr[7-k];
//        _delay_ms(100);
//        k++;
//        if(k>7){
//            k=0;
//            PORTD = 0x00;
//        }
//        j++;
//        if(j>7){
//            j=0;
//        }
//    }
//}






#define F_CPU 1000000UL
#include <avr/io.h> 
#include <util/delay.h>


typedef union{
    
    struct{
        
        uint8_t b0:1;
        uint8_t b1:1;
        uint8_t b2:1;
        uint8_t b3:1;
        uint8_t b4:1;
        uint8_t b5:1;
        uint8_t b6:1;
        uint8_t b7:1;
    };
    
    uint8_t x;
}Typedef_PinConfig;

void  Data_Write(uint8_t data) {
    Typedef_PinConfig y;
    y.b0= (0x01 & data) ? 1 : 0;
    y.b1= (0x02 & data) ? 1 : 0;
    y.b2= (0x04 & data) ? 1 : 0;
    y.b3= (0x08 & data) ? 1 : 0;
    y.b4= (0x10 & data) ? 1 : 0;
    y.b5= (0x20 & data) ? 1 : 0;
    y.b6= (0x40 & data) ? 1 : 0;
    y.b7= (0x80 & data) ? 1 : 0;
    
    PORTD = y.x;

}

int main()
{
    DDRD = 0xff;

    while(1) 
    {
        
        Data_Write(0x01);
        _delay_ms(100);
        Data_Write(0x02);
        _delay_ms(100);
        Data_Write(0x04);
        _delay_ms(100);
        Data_Write(0x08);
        _delay_ms(100);
        Data_Write(0x10);
        _delay_ms(100);
        Data_Write(0x20);
        _delay_ms(100);
        Data_Write(0x40);
        _delay_ms(100);
        Data_Write(0x80);
        _delay_ms(100);
    }
}
