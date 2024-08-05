#include "GLCD.h"

#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h> 


void Delay();
void Wait();

int main(void)
{
 Delay();
 InitLCD(); 
 LCD_Clear(); 

 DisplayText(1,3,"blog.circuits4you.com");
 DisplayText(1,15,"   GLCD 128x64 Demo ");
 circle(40,40,20,1);
 line(20,20,64,64,1);
 rect(15,15,100,60,1);
 //PutPixel(unsigned char x,unsigned char y, char color);
 //line(char x0, char y0, char x1, char y1,char color) 
 //DisplayCharSmall(unsigned char x,unsigned char y, char d)


  Wait();
  Wait();
  Wait();
  Wait();
  LCD_Clear();
  Delay100ms();
}

/*********************************************************************************/
/*      100 mSec Delay                    */
/*********************************************************************************/
void Delay100ms()
{
int k;
 for(k=-29000;k<29000;k++)
 {
  asm("nop");
 }
}
/*********************************************************************************/
/*         DELAY 100mSec                                */
/*********************************************************************************/
void Delay()
{
 int t;
  for(t=-22500;t<22500;t++);
}
/****************************************************************************************/
/*           WAIT                                              */
/****************************************************************************************/
void Wait()
{
  Delay100ms();
  Delay100ms();
  Delay100ms();
  Delay100ms();
  Delay100ms();
  Delay100ms();
  Delay100ms();
  Delay100ms();
  Delay100ms();
  Delay100ms();
  Delay100ms();
}