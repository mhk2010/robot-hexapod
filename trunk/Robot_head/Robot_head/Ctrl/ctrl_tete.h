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
#define LEFT_TETE_HORIZONTAL				115
#define RIGHT_TETE_HORIZONTAL				45

#define TIMEOUT_HEAD_SCAN_SPEED		5 //(500ms)
#define START_ANGLE_DETECT			( NEUTRE_TETE_HORIZONTAL - 60 )
#define END_ANGLE_DETECT			( NEUTRE_TETE_HORIZONTAL + 60 )  


//strucutre qui defini la position de la tete du robot
typedef struct {
	Int8U angle_h;
	Int8U angle_v;
} tete_position_t;

void CtrlTete( void ) ;


#endif /* CTRL_TETE_H_ */