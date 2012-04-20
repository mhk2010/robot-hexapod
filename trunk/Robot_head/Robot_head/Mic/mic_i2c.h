/*
 * mic_i2c.h
 *
 * Created: 16/11/2011 14:03:00
 *  Author: berryer
 */ 


#ifndef MIC_I2C_H_
#define MIC_I2C_H_


#include "Tools/tools_typedefs.h"


/** defines the data direction (reading from I2C device) in i2c_start(),i2c_rep_start() */
#define I2C_READ    1

/** defines the data direction (writing to I2C device) in i2c_start(),i2c_rep_start() */
#define I2C_WRITE   0


void MicI2cinit(void);
void i2c_stop(void);
Int8U i2c_start(Int8U addr);
Int8U i2c_rep_start(Int8U addr);
void i2c_start_wait(Int8U addr);
Int8U i2c_write(Int8U data);
Int8U i2c_readAck(void);
Int8U i2c_readNak(void);

Int8U i2c_read(Int8U ack);

#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak(); 


#endif /* MIC_I2C_H_ */