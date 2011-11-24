/*
 * drv_i2c.h
 *
 * Created: 16/11/2011 12:20:01
 *  Author: berryer
 */ 


#ifndef DRV_I2C_H_
#define DRV_I2C_H_


#include "Tools/tools_typedefs.h"
#include <compat/twi.h>

#include "Conf/conf_hard.h"
#include "Mic/mic_io_ports.h"


#define I2C_SLAVE_OWN_ADDRESS        (0x05U << 1U)   // Slave I2C address
#define TIMEOUT_I2C				     50
void DrvI2C(void);



#endif /* DRV_I2C_H_ */