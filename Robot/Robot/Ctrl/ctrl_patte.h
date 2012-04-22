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
//on fixe le nombre de pattes
#define NB_PATTES 6U

//on fixe le nom des pattes
#define AVANT_GAUCHE			0U
#define MILIEU_GAUCHE			1U 
#define ARRIERE_GAUCHE			2U 
#define AVANT_DROITE			3U
#define MILIEU_DROITE			4U 
#define ARRIERE_DROITE			5U 

//on fixe les angles min et max du servo coude
#define ANGLE_MID_COUDE			90U
#define ANGLE_DETLA_COUDE		40U
#define ANGLE_MAX_COUDE			ANGLE_MID_COUDE - ANGLE_DETLA_COUDE
#define ANGLE_MIN_COUDE			ANGLE_MID_COUDE + ANGLE_DETLA_COUDE

//on fixe les angles min et max du servo epaule
#define ANGLE_MID_EPAULE		90U
#define ANGLE_DETLA_EPAULE		20U
#define ANGLE_MAX_EPAULE		ANGLE_MID_EPAULE - ANGLE_DETLA_EPAULE
#define ANGLE_MIN_EPAULE		ANGLE_MID_EPAULE + ANGLE_DETLA_EPAULE

//on fixe les position neutre
#define NEUTRE_COUDE_AVANT_GAUCHE				ANGLE_MID_COUDE
#define NEUTRE_EPAULE_AVANT_GAUCHE				ANGLE_MID_EPAULE
#define NEUTRE_COUDE_AVANT_DROITE				ANGLE_MID_COUDE
#define NEUTRE_EPAULE_AVANT_DROITE				ANGLE_MID_EPAULE
#define NEUTRE_COUDE_MILIEU_GAUCHE				ANGLE_MID_COUDE
#define NEUTRE_EPAULE_MILIEU_GAUCHE				ANGLE_MID_EPAULE
#define NEUTRE_COUDE_MILIEU_DROITE				ANGLE_MID_COUDE
#define NEUTRE_EPAULE_MILIEU_DROITE				ANGLE_MID_EPAULE
#define NEUTRE_COUDE_ARRIERE_GAUCHE				ANGLE_MID_COUDE
#define NEUTRE_EPAULE_ARRIERE_GAUCHE			ANGLE_MID_EPAULE
#define NEUTRE_COUDE_ARRIERE_DROITE				ANGLE_MID_COUDE
#define NEUTRE_EPAULE_ARRIERE_DROITE			ANGLE_MID_EPAULE




/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
//structure d'un servo 
typedef struct {
	Int8U pin;
	Int8U index;
	Int8U angle;
	Int8S offset;
} patte_servo_t;

//structure d'une patte de 2 servos
typedef struct {
	patte_servo_t epaule;
	patte_servo_t coude;
} patte_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlPatte( void ) ;
//on bouge une patte
Boolean CtrlPatteMove( Int8U index, Int8U angle_epaule, Int8U angle_coude, EServoVitesse vitesse );

//on bouge une patte direct sans attendre quel finisse son mouvement
Boolean CtrlPatteDirectMove( Int8U index, Int8U angle_epaule, Int8U angle_coude, EServoVitesse vitesse );

#endif /* CTRL_PATTE_H_ */