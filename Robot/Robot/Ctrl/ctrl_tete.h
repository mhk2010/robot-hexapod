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
#define MIN_TETE_HORIZONTAL					0
#define NEUTRE_TETE_HORIZONTAL				80
#define MAX_TETE_HORIZONTAL					160
#define NEUTRE_TETE_VERTICAL				140

#define TIMEOUT_HEAD_SCAN_SPEED		5 //(500ms)
#define START_ANGLE_DETECT			NEUTRE_TETE_HORIZONTAL - 60 
#define END_ANGLE_DETECT			NEUTRE_TETE_HORIZONTAL + 60  
#define OFFSET_ANGLE_DETECT			8 
#define NB_ANGLE_DETECT				( ( NEUTRE_TETE_HORIZONTAL + 60 ) + ( NEUTRE_TETE_HORIZONTAL - 60 ) ) / 4


//strucutre qui defini la position de la tete du robot
typedef struct {
	Int8U angle_h;
	Int8U angle_v;
} tete_position_t;

//strucutre qui defini la tete du robot
typedef struct {
	tete_position_t position;
	Boolean scanning_proximity;
	Boolean scanning_light;
	Boolean find_light_angle;
	Int8U light_angle;
	Int16U mesure_ultrason;
	Int16U mesure_ldr_gauche;
	Int16U mesure_ldr_droite;
} tete_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlTete( void ) ;
//dispatcher
void CtrlTeteDispatcher( Event_t event ) ;
//on place la tete ou l'on veut
void CtrlTeteMove( Int8U angle_horizontal, Int8U angle_vertical);
//on fait un scan horizontal
void CtrlTeteStartScanProximity( void );
//on fait un scan de la lumiere
void CtrlTeteStartScanLight( void );
//on recupere la structure
tete_t *CtrlTeteGetStruct( void );



#endif /* CTRL_TETE_H_ */