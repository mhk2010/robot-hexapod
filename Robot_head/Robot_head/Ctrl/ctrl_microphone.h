/*
 * ctrl_microphone.h
 *
 * Created: 16/11/2011 12:07:51
 *  Author: berryer
 */ 


#ifndef CTRL_MICROPHONE_H_
#define CTRL_MICROPHONE_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_event.h"
#include "Drv/drv_adc.h"

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlMicrophone( void ) ;

//dispatcher
void CtrlMicrophoneDispatcher( Event_t event ) ;
//retourne sur l'uart la mesure la plus forte
Int8U CtrlMicrophoneSendUartMesureLevelSide( void ) ;

#endif /* CTRL_MICROPHONE_H_ */