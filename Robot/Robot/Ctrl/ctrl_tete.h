/*
 * ctrl_tete.h
 *
 * Created: 14/11/2011 15:35:57
 *  Author: berryer
 */ 


#ifndef CTRL_TETE_H_
#define CTRL_TETE_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_servo.h"
#include "Drv/drv_event.h"
#include "Drv/drv_adc.h"


/////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////
#define OFFSET_TETE_HORIZONTAL		7U
#define NEUTRE_TETE_HORIZONTAL		90 - OFFSET_TETE_HORIZONTAL
#define MIN_TETE_HORIZONTAL			( NEUTRE_TETE_HORIZONTAL - 60 )
#define MAX_TETE_HORIZONTAL			( NEUTRE_TETE_HORIZONTAL + 60 )


#define NEUTRE_TETE_VERTICAL		150



//strucutre qui defini la position de la tete du robot
typedef struct SSTete{
	Int8U angle_h;
	Int8U angle_v;
	Boolean is_scaning;
} head_member_t;

//init de la tete
void CtrlTete( void ) ;
//on bouge la tete
void CtrlTeteMove( Int8U angle_tete_hor, Int8U angle_tete_ver, Int8U vitesse );
//dispatacher d'event
void CtrlTeteDispatcher( Event_t event );
//on recupere la structure
head_member_t* CtrlTeteGetStruct( void ) ;
//on start le scan de la tete
void CtrlTeteStartScan( void ) ;
//on stop le scan de la tete
void CtrlTeteStopScan( void ) ;
#endif /* CTRL_TETE_H_ */