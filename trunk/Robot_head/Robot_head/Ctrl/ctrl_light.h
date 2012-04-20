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

/////////////////////////////////////////PUBLIC ENUM/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlLight( void ) ;
//dispatcher
void CtrlLightDispatcher( Event_t event )  ;


//permet d'envoyer sur l'uart 
void CtrlLightSendUartLightMesure( void ) ;

#endif /* CTRL_LIGHT_H_ */