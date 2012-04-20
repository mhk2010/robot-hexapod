/*
 * ctrl_eye.h
 *
 * Created: 14/11/2011 15:35:57
 *  Author: berryer
 */ 


#ifndef CTRL_CAMERA_H_
#define CTRL_CAMERA_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_led.h"
#include "Drv/drv_event.h"

/////////////////////////////////////////PUBLIC DEFINES///////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlCamera( void ) ;

//dispatcher
void CtrlCameraDispatcher( Event_t event ) ;

#endif /* CTRL_EYE_H_ */