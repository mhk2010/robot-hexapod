/*
 * ctrl_light.h
 *
 * Created: 12/12/2011 19:26:56
 *  Author: louis
 */ 


#ifndef CTRL_LIGHT_H_
#define CTRL_LIGHT_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"
#include "Drv/drv_servo.h"

/////////////////////////////////////////PUBLIC ENUM/////////////////////////////////////////
//enum du taux de luminosité
typedef enum 
{
	VERY_HIGHT_LUMINOSITY,
	HIGHT_LUMINOSITY,
	LOW_LUMINOSITY,
	DARK_ROOM,
} luminosity_level_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlLight( void ) ;
//dispatcher
void CtrlLightDispatcher( Event_t event )  ;
//on lance un scan 
void CtrlLightLaunch( void );



#endif /* CTRL_LIGHT_H_ */