/*
 * ctrl_accel.h
 *
 * Created: 16/11/2011 12:07:06
 *  Author: berryer
 */ 


#ifndef CTRL_ACCEL_H_
#define CTRL_ACCEL_H_


#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"
#include "Drv/drv_adc.h"

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlAccel( void ) ;
//dispatcher
void CtrlAccelDispatcher( Event_t event ) ;
//qualibration
void CtrlAccelQualibration( void ) ;

#endif /* CTRL_ACCEL_H_ */