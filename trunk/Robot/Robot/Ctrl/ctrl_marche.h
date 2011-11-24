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
typedef enum EEMove
{
  E_MOVE_STOP,
  E_MOVE_FORWORD,
  E_MOVE_BACKWORD,
  E_MOVE_LEFT,
  E_MOVE_RIGHT,
  E_MOVE_LEFT_SIDE,
  E_MOVE_RIGHT_SIDE,
}EMove;

typedef enum EESpeed
{
  E_SPEED_0 = 5,
  E_SPEED_1 = 4,
  E_SPEED_2 = 3,
  E_SPEED_3 = 2,
  E_SPEED_4 = 1,
  E_SPEED_5 = 0,
}ESpeed;


////////////////////////////////////////////PUBLIC STRUCTS/////////////////////////////////////////
//strucutre qui defini les mouvements du robot
typedef struct {
	EMove move;
	ESpeed speed;
} move_t;


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlMarche( void ) ;
//dispatcher
void CtrlMarcheDispatcher( Event_t event )  ;
//deplace le robot
void CtrlMarcheMove( EMove move, ESpeed speed ) ;
//on recupere la structure
move_t* CtrlMarcheGetStruct( void ) ;

#endif /* CTRL_MARCHE_H_ */