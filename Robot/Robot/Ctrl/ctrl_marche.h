/*
 * ctrl_marche.h
 *
 * Created: 15/11/2011 17:08:59
 *  Author: berryer
 */ 


#ifndef CTRL_MARCHE_H_
#define CTRL_MARCHE_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"
#include "Drv/drv_servo.h"

////////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////
//donne l'enim des deplacments possible
typedef enum EEMove
{
  E_MOVE_STOP,
  E_MOVE_FORWARD,
  E_MOVE_BACKWARD,
  E_MOVE_LEFT,
  E_MOVE_RIGHT,
  E_MOVE_SIT_DOWN,
  E_MOVE_STAR,
  E_MOVE_NONE,
}EMove;



////////////////////////////////////////////PUBLIC STRUCTS/////////////////////////////////////////
//strucutre qui defini les mouvements du robot
typedef struct {
	EMove move;
	EServoVitesse speed;
} body_member_t;


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlMarche( void ) ;
//dispatcher
void CtrlMarcheDispatcher( Event_t event )  ;
//deplace le robot
void CtrlMarcheMove( EMove move, EServoVitesse speed ) ;
//on recupere la structure
body_member_t* CtrlMarcheGetStruct( void ) ;
//on arrte a la fin du mouvement
void CtrlMarcheMoveWantStop( void ) ;

#endif /* CTRL_MARCHE_H_ */