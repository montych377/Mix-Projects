

void LCDout(char a)
{
 PORTD = a;
 Epulse();
}

void Delay1()
{
 int t;
  for(t=0;t<125;t++);
}


void InitLCD()
{
 DDRD = 0xFF;
 DDRA |=(1<<RS);
DDRA |=(1<<E);
DDRC |=(1<<CS1);
DDRC |=(1<<CS2);
DDRC |=(1<<RST);

PORTC &= ~(1<<RST);   //Make sure rst state
Delay1();
PORTC |= (1<<RST);   //Make sure rst state
Delay1();

PORTA &=~(1<<RS);  //Command mode
PORTC |= (1<<CS1);  //CS1 CS2 selected
PORTC |= (1<<CS2);  //CS1 CS2 selected
LCDout(0x3F);   //LCD on
LCDout(0xC0);   //z-axis to zero 

Delay1();
Delay1();
PORTC &=~ (1<<CS1);  
PORTC &=~ (1<<CS2);  
}

/*********************************************************************************/
/*         Enable Pulse                                 */
/*********************************************************************************/
void Epulse()
{
 //E=PA3
 PORTA = PORTA | 0x08;
 PORTA = PORTA & 0xF7;
}

/*********************************************************************************/
/*         PUT PIXEL(X,Y,color)                         */
/*********************************************************************************/
void PutPixel(unsigned char x,unsigned char y, char color)
{

//Inverse Display
//x = 127-x;
//y = 63-y;

unsigned char c,y1;
c=0;
y1=y; //+3
   
   while(y1 >= 8)
   {
     y1=y1-8;
  c++;
   }

if (x < 64)
{
 PORTA &=~(1<<RS);  //Command mode
    PORTC |= (1<<CS1);  //CS1 selected
 PORTC &=~(1<<CS2);
 c = c & 0x07;
 LCDout(0xB8 | c);  //C (y-axis) is having 3-bit address
 x = x & 0x3F;
 LCDout(0x40 | x);  //C (x-axis) is having 3-bit address
}
else
{
 x = x - 64;
 PORTA &=~(1<<RS);  //Command mode
 PORTC &=~(1<<CS1);  
    PORTC |= (1<<CS2);  //CS2 selected
 c = c & 0x07;
 LCDout(0xB8 | c);  //C (y-axis) is having 3-bit address
 x = x & 0x3F;
 LCDout(0x40 | x);  //C (x-axis) is having 3-bit address
 x = x+64;
}
 
 PORTA |= (1<<RS); 
  if(color==1)
  {
  Pix [x][c]=(Pix [x][c]) | (1<<y1) ;  //y1 is having bit position to set
  LCDout(Pix [x][c]);
 }
 else
 {
  Pix [x][c] &=~ (1<<y1);  //y1 is having bit position to reset
  LCDout(Pix [x][c]);
 }
}

/*********************************************************************************/
/*         LCD CLEAR                                    */
/*********************************************************************************/

void LCD_Clear()
{
unsigned char x,y;
 
unsigned char c;
c=0;
   for(y=0;y<8;y++)
    {
 c=y;
   for(x=0;x<128;x++)
    {
     Pix[x][y]=0x00;
  //=======================
   if ( x < 64)
   {
    PORTA &=~(1<<RS);  //Command mode
       PORTC |= (1<<CS1);  //CS1 selected
    PORTC &=~(1<<CS2);
    c = c & 0x07;
    LCDout(0xB8 | c);  //C (y-axis) is having 3-bit address
    x = x & 0x3F;
    LCDout(0x40 | x);  //C (x-axis) is having 3-bit address
   }
   else
   {
    x = x - 64;
    PORTA &=~(1<<RS);  //Command mode
    PORTC &=~(1<<CS1);  
       PORTC |= (1<<CS2);  //CS2 selected
    c = c & 0x07;
    LCDout(0xB8 | c);  //C (y-axis) is having 3-bit address
    x = x & 0x3F;
    LCDout(0x40 | x);  //C (x-axis) is having 3-bit address
    x = x+64;
   }
   PORTA |=(1<<RS);
   LCDout(0x00);
  //=======================
   
    }
    }
}
/*********************************************************************************/
/*         LINE(X0,Y0,X1,Y1,color)                      */
/*********************************************************************************/

void line(char x0, char y0, char x1, char y1,char color) 
{
 int dy = y1 - y0;
 int dx = x1 - x0;
 int stepx, stepy;
 if (dy < 0) { dy = -dy; stepy = -1; 
 } else { stepy = 1; 
 }
  if (dx < 0) { dx = -dx; stepx = -1; 
 } else { stepx = 1; 
 }
 dy <<= 1;        // dy is now 2*dy
 dx <<= 1;        // dx is now 2*dx
 
 PutPixel(x0, y0,color);

 if (dx > dy) {
  int fraction = dy - (dx >> 1); // same as 2*dy - dx
  while (x0 != x1) {
   if (fraction >= 0) {
    y0 += stepy;
    fraction -= dx;   // same as fraction -= 2*dx
   }
     x0 += stepx;
     fraction += dy;     // same as fraction -= 2*dy
     PutPixel(x0, y0,color);
  }
 } else {
  int fraction = dx - (dy >> 1);
  while (y0 != y1) {
   if (fraction >= 0) {
    x0 += stepx;
    fraction -= dy;
   }
  y0 += stepy;
  fraction += dx;
  PutPixel(x0, y0,color);
  }
 }
} 
/*********************************************************************************/
/*         RECT(X0,Y0,X1,Y1,color)                      */
/*********************************************************************************/
void rect(char x0, char y0, char x1, char y1,char color)
{
 line(x0,y0,x1,y0,color);
 line(x0,y0,x0,y1,color);
 line(x0,y1,x1,y1,color);
 line(x1,y0,x1,y1,color); 
}

/*********************************************************************************/
/*         Circle(X0,Y0,radius,color)                   */
/*********************************************************************************/
void circle(int xCenter, int yCenter, int radius, char c)
    {
        int x, y, r2;

        r2 = radius * radius;
        PutPixel(xCenter, yCenter + radius,c);
        PutPixel(xCenter, yCenter - radius,c);
        PutPixel(xCenter + radius, yCenter,c);
        PutPixel(xCenter - radius, yCenter,c);
        x = 1;
        y = (int) (sqrt(r2 - 1) + 0.5);
        while (x < y) {
            PutPixel(xCenter + x, yCenter + y,c);
            PutPixel(xCenter + x, yCenter - y,c);
            PutPixel(xCenter - x, yCenter + y,c);
            PutPixel(xCenter - x, yCenter - y,c);
            PutPixel(xCenter + y, yCenter + x,c);
            PutPixel(xCenter + y, yCenter - x,c);
            PutPixel(xCenter - y, yCenter + x,c);
            PutPixel(xCenter - y, yCenter - x,c);
            x += 1;
            y = (int) (sqrt(r2 - x*x) + 0.5);
        }
        if (x == y) {
            PutPixel(xCenter + x, yCenter + y,c);
            PutPixel(xCenter + x, yCenter - y,c);
            PutPixel(xCenter - x, yCenter + y,c);
            PutPixel(xCenter - x, yCenter - y,c);
        }
    }
/*********************************************************************************/
/*         Display Text (5x7)                       */
/*********************************************************************************/
void DisplayChar(unsigned char x,unsigned char y, char d)
{
unsigned char r,c,c1;
d=d-32;
 for(r=0;r<5;r++)
 {
  c1=0;   //4
  for(c=0;c<8;c++)
  {
   PutPixel(x+r,y+c1,((0x01) & (pgm_read_byte(&FontLookup[d][r]) >> c )));//>>(c+3)
   c1=c1+1;
  }
 }
}
/*********************************************************************************/
/*         Display Text (3x5)                       */
/*********************************************************************************/
void DisplayCharSmall(unsigned char x,unsigned char y, char d)
{
unsigned char r,c,c1;
 for(r=0;r<3;r++)
 {
  c1=4;  
  for(c=0;c<5;c++)
  {
   PutPixel(x+r,y+c1,((0x01) & (pgm_read_byte(&FontLookup1[d][r]) >> (c+3))));
   c1=c1-1;
  }
 }
}

/*********************************************************************************/
/*         Display Text (5x7)                       */
/*********************************************************************************/
void DisplayText(unsigned char x, unsigned char y, const char* d)
{
    int i;
    int j;
    j=strlen(d);
     for (i=0;i<j;i++)
     {
         DisplayChar((i*6)+x,y,*(d+i));
     } 
}