/*
 * ctrl_boussole.h
 *
 * Created: 18/11/2011 16:21:57
 *  Author: berryer
 */ 


#ifndef CTRL_BOUSSOLE_H_
#define CTRL_BOUSSOLE_H_


#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"
#include "Drv/drv_i2c_boussole.h"



///////////////////////////////////////////PUBLIC ENULS///////////////////////////////////////////
typedef enum EEcardinaux
{
	E_CARD_NORD,		//347 <-> 22
	E_CARD_NORD_EST,	//22 <-> 67
	E_CARD_EST,		//67 <-> 112
	E_CARD_SUD_EST,	//112 <-> 157
	E_CARD_SUD,		//157 <-> 202
	E_CARD_SUD_OUEST,	//202 <-> 247
	E_CARD_OUEST,		//247 <-> 292
	E_CARD_NORD_OUEST,	//292 <-> 347
	E_CARD_NONE,
}Ecardinaux;


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlBoussole( void ) ;
//dispatcher
void CtrlBoussoleDispatcher( Event_t event ) ;
//consigne de direction
void CtrlBoussoleSetConsigne( Ecardinaux angle ) ;




#endif /* CTRL_BOUSSOLE_H_ */