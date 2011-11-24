/*
 * drv_i2c_boussole.h
 *
 * Created: 18/11/2011 15:18:26
 *  Author: berryer
 */ 


#ifndef DRV_I2C_BOUSSOLE_H_
#define DRV_I2C_BOUSSOLE_H_


#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"
#include "Mic/mic_io_ports.h"
#include "drv_i2c.h"


void DrvI2CBoussole(void);
void DrvI2CBoussoleTransmit(Int8U address, Int8U reg, Int8U data);
Int8U DrvI2CBoussoleRead(Int8U address, Int8U reg);




#endif /* DRV_I2C_BOUSSOLE_H_ */