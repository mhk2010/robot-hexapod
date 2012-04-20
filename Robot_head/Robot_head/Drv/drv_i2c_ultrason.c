/*
 * drv_i2c_ultrason.c
 *
 * Created: 18/11/2011 15:33:06
 *  Author: berryer
 */ 

#include "drv_i2c_ultrason.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Int16U timeout_ic = 0;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv I2C 
void DrvI2CUltraSon( void )
{

}

//on envoie un octet sur le registre
void DrvI2CUltraSonTransmit(Int8U address, Int8U reg, Int8U data)
{
	TWCR = 0xA4;                                                  // send a start bit on i2c bus
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}
	TWDR = address;                                               // load address of i2c device
	TWCR = 0x84;                                                  // transmit
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}
	TWDR = reg;
	TWCR = 0x84;                                                  // transmit
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}
	TWDR = data;
	TWCR = 0x84;                                                  // transmit
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}
	TWCR = 0x94;                                                  // stop bit
}

//on recois un octet
Int8U DrvI2CUltraSonRead(Int8U address, Int8U reg)
{
	timeout_ic=0;
	Int8U read_data = 0;
	TWCR = 0xA4;                                                  // send a start bit on i2c bus
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}                                         
	TWDR = address;                                               // load address of i2c device
	TWCR = 0x84;                                                  // transmit 
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}
	TWDR = reg;                                                   // send register number to read from
	TWCR = 0x84;                                                  // transmit
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}

	TWCR = 0xA4;                                                  // send repeated start bit
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}
	TWDR = address+1;                                             // transmit address of i2c device with readbit set
	TWCR = 0xC4;                                                  // clear transmit interupt flag
	while(!(TWCR & 0x80))										  // wait for confirmation of transmit 
	{
		if(timeout_ic++ > 1000)
		{
			timeout_ic = 0;
			break;
		}
	}
	TWCR = 0x84;                                                  // transmit, nack (last byte request)
	while(!(TWCR & 0x80))
	{
		if(timeout_ic++ > 1000)
		{
			break;
		}
	}										  // wait for confirmation of transmit 		
	read_data = TWDR;                                             // and grab the target data
	TWCR = 0x94;                                                  // send a stop bit on i2c bus
	return read_data;	

}
