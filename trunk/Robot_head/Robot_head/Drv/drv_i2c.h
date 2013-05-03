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


void DrvI2C(void);

// send I2C data to <device> register <sub>
void DrvI2CSend(Int8U device, Int8U sub, Int8U length, Int8U *data);



#endif /* DRV_I2C_H_ */