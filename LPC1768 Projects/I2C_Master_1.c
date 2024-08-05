#include <LPC17xx.h>


#define I2EN (1<<6) //Enable/Disable bit
#define STA  (1<<5) //Start Set/Clear bit
#define STO  (1<<4) //Stop bit
#define SI   (1<<3) //Serial Interrupt Flag Clear bit
#define AA   (1<<2) //Assert Acknowledge Set/Clear bit

void I2C_Initialize( void );
uint8_t I2C_Flag(void);
void I2C_Start( void );
void I2C_WriteAddress(uint8_t address);
void I2C_WriteData(uint8_t data);
void I2C_Stop( void );
uint32_t  I2C0_ReceiveData(uint8_t isLast);
void _delay_ms(uint32_t ms);

uint32_t R_Data = 0, i=0,j=0;

int main( void ) {
	
	
	LPC_GPIO2->FIODIR = 0xff;
	I2C_Initialize();
	
	while(1) {
		
		I2C_Start();
		_delay_ms(100);
		LPC_GPIO2->FIOPIN = 0x01;
		I2C_WriteAddress(0X20);
		_delay_ms(100);
		LPC_GPIO2->FIOPIN = 0x02;
		I2C_WriteData('A');
		_delay_ms(100);
		LPC_GPIO2->FIOPIN = 0x04;
		I2C_Stop();
		_delay_ms(100);
		LPC_GPIO2->FIOPIN = 0x08;
	}
	
}

void I2C_Initialize( void ) {
	
	LPC_PINCON->PINSEL0 = (0<<22)|(1<<23)|(0<<24)|(1<<25);
	LPC_I2C0->I2SCLL = 300;
	LPC_I2C0->I2SCLH = 300;
	LPC_I2C0->I2CONCLR = STA|STO|SI|AA ;
	LPC_I2C0->I2CONSET = I2EN;
}

uint8_t I2C_Flag(void) 
{
	int timeout = 0;
	while ( !(LPC_I2C0->I2CONSET & SI) ) //Wait till SI bit is set. This is important!
	{
		timeout++;
		if (timeout > 10000)
		{
			return 1; //In case we have some error on bus
		}
	}
	return 0; //SI has been set

}
void I2C_Start( void ){
	
	LPC_I2C0->I2CONCLR = STA|STO|SI|AA;
	LPC_I2C0->I2CONSET = STA;
	I2C_Flag();
}

void I2C_WriteAddress(uint8_t address){
	
	LPC_I2C0->I2DAT = address;
	LPC_I2C0->I2CONCLR = STA|STO|SI;
	I2C_Flag();
}

void I2C_WriteData(uint8_t data){
	
	LPC_I2C0->I2DAT = data;
	LPC_I2C0->I2CONCLR = STA|STO|SI;
	I2C_Flag();
}

void I2C_Stop( void ){
	
	LPC_I2C0->I2CONCLR = STA|STO|SI|AA;
	LPC_I2C0->I2CONSET = STO;
	I2C_Flag();
}

uint32_t  I2C0_ReceiveData(uint8_t isLast)
{
	if(isLast)
	{		
		LPC_I2C0->I2CONCLR = AA; //Send NACK to stop; I2C block will send a STOP automatically, so no need to send STOP thereafter.
	}
	else 
	{	 
    LPC_I2C0->I2CONSET = AA; //Send ACK to continue
	}
	LPC_I2C0->I2CONCLR = SI; //Clear SI to Start RX
	I2C_Flag(); //wait till RX is finished
	R_Data = LPC_I2C0->I2DAT;
	return R_Data;
}

void _delay_ms(uint32_t ms){
	
	for(i=0;i<ms;i++) {
		
		for(j=0;j<5000;j++);
		
	}
}

