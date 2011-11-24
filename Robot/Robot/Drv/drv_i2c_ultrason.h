/*
 * drv_i2c_ultrason.h
 *
 * Created: 18/11/2011 15:32:59
 *  Author: berryer
 */ 


#ifndef DRV_I2C_ULTRASON_H_
#define DRV_I2C_ULTRASON_H_


#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"
#include "Mic/mic_io_ports.h"
#include "drv_i2c.h"

void DrvI2CUltraSon(void);
void DrvI2CUltraSonTransmit(Int8U address, Int8U reg, Int8U data);
Int8U DrvI2CUltraSonRead(Int8U address, Int8U reg);


#endif /* DRV_I2C_ULTRASON_H_ */