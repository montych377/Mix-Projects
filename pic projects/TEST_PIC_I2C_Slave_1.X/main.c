#define _XTAL_FREQ 12000000

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

#define rs RC0
#define rw RC1
#define en RC2
#define delay for(i=0;i<1000;i++)
int i;
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);

#define write_cmd 0xA0
#define read_cmd 0xA1
void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_restart();
void i2c_ack();
void i2c_nak();
void waitmssp();
void i2c_send(unsigned char dat);
void i2c_send_byte(unsigned char addr,unsigned char *count);
unsigned char i2c_read();
unsigned char i2c_read_byte(unsigned char addr);
void delay1();


void main()
{
    lcd_init();
    i2c_init();
    show("  I2C TuTorial  ");
    cmd(0xc2);
    show("Writing...");
    i2c_send_byte(0x0000,"EmbeTronicX");
    delay1();
    cmd(0xc2);
    show("Reading...");
    delay1();
    cmd(0xc2);
    dat(i2c_read_byte(0x0000));
    dat(i2c_read_byte(0x0001));
    dat(i2c_read_byte(0x0002));
    dat(i2c_read_byte(0x0003));
    dat(i2c_read_byte(0x0004));
    dat(i2c_read_byte(0x0005));
    dat(i2c_read_byte(0x0006));
    dat(i2c_read_byte(0x0007));
    dat(i2c_read_byte(0x0008));
    dat(i2c_read_byte(0x0009));
    dat(i2c_read_byte(0x000a));
    
    while(1);
}   
void delay1()
{
    unsigned int j,k;
    for(j=0;j<60000;j++) {
        for(k=0;k<2;k++);
    }
}

void i2c_init()
{
    TRISC3=TRISC4=1;
    SSPCON=0x28;                    //SSP Module as Master
    SSPADD=((11059200/4)/100)-1;    //Setting Clock Speed, My PCLK = 11.0592MHz
}
void i2c_start()
{
    SEN=1;
    waitmssp();
}
void i2c_stop()
{
    PEN=1;
    waitmssp();
}
void i2c_restart()
{
    RSEN=1;
    waitmssp();
}
void i2c_ack()
{
    ACKDT=0;
    ACKEN=1;
    waitmssp();
}
void i2c_nak()
{
    ACKDT=1;
    ACKEN=1;
    waitmssp();
}
void waitmssp()
{
    while(!SSPIF);
    SSPIF=0;
}
void i2c_send(unsigned char dat)
{
L1: SSPBUF=dat;
    waitmssp();
    while(ACKSTAT){i2c_restart;goto L1;}
}
void i2c_send_byte(unsigned char addr,unsigned char *count)
{
    i2c_start();
    i2c_send(write_cmd);
    i2c_send(addr>>8);
    i2c_send(addr);
    while(*count) {
        i2c_send(*count++);
    }
    i2c_stop();
}
unsigned char i2c_read()
{
    RCEN=1;
    waitmssp();
    return SSPBUF;
}   
unsigned char i2c_read_byte(unsigned char addr)
{
    unsigned char rec;
L:  i2c_restart();
    SSPBUF=write_cmd;
    waitmssp();
    while(ACKSTAT){goto L;}
    i2c_send(addr>>8);
    i2c_send(addr);
    i2c_restart();
    i2c_send(read_cmd);
    rec=i2c_read();
    i2c_nak();
    i2c_stop();
    return rec;
}


void lcd_init()
{
    TRISB=TRISC0=TRISC1=TRISC2=0;
    cmd(0x38);
    cmd(0x0c);
    cmd(0x06);
    cmd(0x80);
}
void cmd(unsigned char a)
{
    PORTB=a;
    rs=0;
    rw=0;
    en=1;
    delay;
    en=0;
}
void dat(unsigned char b)
{
    PORTB=b;
    rs=1;
    rw=0;
    en=1;
    delay;
    en=0;
}
void show(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}