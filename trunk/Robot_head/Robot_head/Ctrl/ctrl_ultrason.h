/*
 * ctrl_ultrason.h
 *
 * Created: 16/11/2011 12:07:51
 *  Author: berryer
 */ 


#ifndef CTRL_ULTRASON_H_
#define CTRL_ULTRASON_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"
#include "Drv/drv_i2c_ultrason.h"

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlUltraSon( void ) ;
//retourne la mesure 
Int16U CtrlUltraSonReadMesure( void ) ;
//permet d'envoyer sur l'uart un objet proche
void CtrlUltraSendUartProximity( void ) ;

#endif /* CTRL_ULTRASON_H_ */