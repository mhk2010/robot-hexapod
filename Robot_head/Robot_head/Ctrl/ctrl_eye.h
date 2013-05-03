/*
 * ctrl_eye.h
 *
 * Created: 14/11/2011 15:35:57
 *  Author: berryer
 */ 


#ifndef CTRL_EYE_H_
#define CTRL_EYE_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_led.h"
#include "Drv/drv_event.h"

/////////////////////////////////////////PUBLIC DEFINES///////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlEye( void ) ;

//dispatcher
void CtrlEyeDispatcher( Event_t event );

//on fait clignoter les yeux
void CtrlEyeBlink( Int8U nb_blink ) ;

//on joue un etat sur l'oeil
void CtrlEyeState( Int8U eye, ELedState state ) ;

//on toggle l'etat sur l'oeil
void CtrlEyeToggle( Int8U eye);

//on fait clignoter l oeil de gauche
void CtrlEyeLeftBlink( Int8U nb_blink ) ;

//on fait clignoter l oeil de droite
void CtrlEyeRightBlink( Int8U nb_blink ) ;

//on fait varier la vitesse de clignotement
void CtrlEyeBlinkSpeed( Int8U nb_blink ,Int8U speed ) ;

//on active ou non le hearbeat sur les leds
void CtrlEyeHeartBeat ( Boolean enable );
#endif /* CTRL_EYE_H_ */