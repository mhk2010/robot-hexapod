/*
 * ctrl_proximity.h
 *
 * Created: 12/12/2011 19:11:43
 *  Author: louis
 */ 


#ifndef CTRL_PROXIMITY_H_
#define CTRL_PROXIMITY_H_


#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"
#include "Drv/drv_servo.h"

//strucutre qui defini le robot
typedef struct {
	Int16U mesure_droite ;
	Int16U mesure_milieu ;
	Int16U mesure_gauche ;
} proximity_result_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlProximity( void ) ;
//dispatcher
void CtrlProximityDispatcher( Event_t event )  ;
//on lance un scan 
void CtrlProximityLaunchScan( void );
//retourn les resultat du scan
proximity_result_t CtrlProximityGetScanResult( void );


#endif /* CTRL_PROXIMITY_H_ */