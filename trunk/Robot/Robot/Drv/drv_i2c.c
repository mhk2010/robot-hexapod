/*
 * drv_i2c.c
 *
 * Created: 16/11/2011 12:19:55
 *  Author: berryer
 */ 


#include "drv_i2c.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv I2C 
void DrvI2C( void )
{
	// Configure port lines for SCL & SDA as input
	micIoPortsConfigureInput(CONF_I2C_SCL, PORT_PULL_UP);
	micIoPortsConfigureInput(CONF_I2C_SDA, PORT_PULL_UP);

	// Initialize the I2C interfaceTWSR = 0; 
	TWSR = 1;
	TWBR = 8;  
}
