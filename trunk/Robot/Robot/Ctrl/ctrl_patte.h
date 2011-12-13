/*
 * ctrl_patte.h
 *
 * Created: 10/11/2011 11:29:28
 *  Author: berryer
 */ 


#ifndef CTRL_PATTE_H_
#define CTRL_PATTE_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"
#include "Drv/drv_servo.h"

/////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////
#define NB_PATTES 6

#define ANGLE_MAX_COUDE			100
#define ANGLE_MID_COUDE			90
#define ANGLE_MIN_COUDE			80
#define ANGLE_MAX_EPAULE		120
#define ANGLE_MID_EPAULE		90
#define ANGLE_MIN_EPAULE		70

#define AVANT_GAUCHE			0 
#define MILIEU_GAUCHE			1 
#define ARRIERE_GAUCHE			2 
#define AVANT_DROITE			3
#define MILIEU_DROITE			4 
#define ARRIERE_DROITE			5 

#define NEUTRE_COUDE_AVANT_GAUCHE				39
#define NEUTRE_EPAULE_AVANT_GAUCHE				85
#define NEUTRE_COUDE_AVANT_DROITE				112
#define NEUTRE_EPAULE_AVANT_DROITE				79
#define NEUTRE_COUDE_MILIEU_GAUCHE				39
#define NEUTRE_EPAULE_MILIEU_GAUCHE				83
#define NEUTRE_COUDE_MILIEU_DROITE				112
#define NEUTRE_EPAULE_MILIEU_DROITE				85
#define NEUTRE_COUDE_ARRIERE_GAUCHE				39
#define NEUTRE_EPAULE_ARRIERE_GAUCHE			86
#define NEUTRE_COUDE_ARRIERE_DROITE				112
#define NEUTRE_EPAULE_ARRIERE_DROITE			78

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct {
	Int8U pin_servo;
	Int8U angle;
} patte_servo_t;

typedef struct {
	patte_servo_t epaule;
	patte_servo_t coude;
} patte_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlPatte( void ) ;
//on bouge une patte
void CtrlPatteMove( Int8U index, Int8U angle_epaule, Int8U angle_coude );


#endif /* CTRL_PATTE_H_ */