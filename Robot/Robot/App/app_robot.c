/*
 * app_robot.c
 *
 * Created: 22/11/2011 15:43:10
 *  Author: berryer
 */ 
#include "app_robot.h"

/////////////////////////////////////////PRIVATE DEFINE//////////////////////////////////////////
#define TIMEOUT_INIT	10//1sec
 
/////////////////////////////////////////PRIVATE TYPEDEF//////////////////////////////////////////
//strucutre qui defini le vie du robot
typedef struct {
	Boolean init;
	Boolean end;
} robot_life_t;

//strucutre qui defini le robot
typedef struct {
	robot_life_t life;
	move_t *mouvement;
	tete_t *tete;
} robot_t;

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
static Boolean RobotLifeCheckInit(void) ;

///////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
static robot_t robot;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
Boolean RobotLifeInit(void) 
{
	Boolean o_success = TRUE;
	
	//on init la structure du robot
	robot.life.init = TRUE;
	robot.life.end = FALSE;
	robot.mouvement = CtrlMarcheGetStruct();
	robot.tete = CtrlTeteGetStruct();
	
	//on met le robot dans sa position initial
	CtrlMarcheMove(robot.mouvement->move, robot.mouvement->speed);
	CtrlTeteMove( robot.tete->position.angle_h, robot.tete->position.angle_v);
	return o_success;
}	

void RobotLife ( Event_t event ) 
{
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
		if( robot.life.init == FALSE )
		{
			robot.life.init = TRUE;
		}
	}		
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_100MS ))
	{
		//on attend la fin de l init du robot
		if( RobotLifeCheckInit() )
		{
			CtrlTeteStartScanHorizontal();
		}
		else
		{
			//on est dans la periode d'init du robot
		}
	}			
}

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
static Boolean RobotLifeCheckInit(void) 
{
	return robot.life.init;	
}