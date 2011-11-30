/*
 * app_robot.c
 *
 * Created: 22/11/2011 15:43:10
 *  Author: berryer
 */ 
#include "app_robot.h"

/////////////////////////////////////////PRIVATE DEFINE//////////////////////////////////////////
#define TIMEOUT_INIT	10//1sec

typedef enum EESeqRobot
{
  E_SEQUENCE_ROBOT_USING_PROXIMITY,
  E_SEQUENCE_ROBOT_PROXIMITY,
  E_SEQUENCE_ROBOT_USING_LUMIERE,
  E_SEQUENCE_ROBOT_LUMIERE,
  E_SEQUENCE_ROBOT_NONE,
}ESeqRobot;

typedef enum EEHumeurRobot
{
  E_HUMEUR_ROBOT_CURIEUX,
  E_HUMEUR_ROBOT_PEUREUX,
  E_HUMEUR_ROBOT_MECHANT,
  E_HUMEUR_ROBOT_NONE,
}EHumeurRobot;

/////////////////////////////////////////PRIVATE TYPEDEF//////////////////////////////////////////
//strucutre qui defini le vie du robot
typedef struct {
	Boolean init;
	ESeqRobot seq;
	EHumeurRobot humeur;
} robot_life_t;

//strucutre qui defini le robot
typedef struct {
	robot_life_t life;
	move_t *body;
	tete_t *tete;
} robot_t;

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) ;

///////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
//structure robot
static robot_t robot;
static Int8U timeout_sequence_using = 0;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
Boolean RobotLifeInit(void) 
{
	Boolean o_success = TRUE;
	timeout_sequence_using = 0;
	//on init la structure du robot
	robot.life.init = TRUE;
	
	robot.life.seq = E_SEQUENCE_ROBOT_LUMIERE;
	robot.life.humeur = E_HUMEUR_ROBOT_NONE;
	robot.body = CtrlMarcheGetStruct();
	robot.tete = CtrlTeteGetStruct();
	
	return o_success;
}	

//on reagit aux evenements
void RobotLife ( Event_t event ) 
{

	if( robot.life.seq == E_SEQUENCE_ROBOT_USING_LUMIERE )
	{
		SeqLightDispatcher(event);
		if ( DrvEventTestEvent(event, CONF_EVENT_FIND_NEAR_OBJECT ))
		{
			CtrlMarcheMoveStep( E_MOVE_BACKWORD, E_SPEED_3 ) ;
		}
	}
	else if( robot.life.seq == E_SEQUENCE_ROBOT_USING_PROXIMITY )
	{
		SeqProximityDispatcher(event);
	}						
	//event 1 sec
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
		if( RobotLifeCheckInit() )
		{
			//robot.life.seq /= (ESeqRobot)RAND();
			robot.life.init = FALSE;
		}
		if( robot.life.seq == E_SEQUENCE_ROBOT_LUMIERE )
		{
			SeqLightStartScan();
			timeout_sequence_using = 0;
			robot.life.seq = E_SEQUENCE_ROBOT_USING_LUMIERE;
		}
		else if( robot.life.seq == E_SEQUENCE_ROBOT_PROXIMITY )
		{
			SeqProximityStartScan();
			timeout_sequence_using = 0;
			robot.life.seq = E_SEQUENCE_ROBOT_USING_PROXIMITY;
		}
		//si la sequence fait plus de 100 sec on la stop
		else if( timeout_sequence_using > 100)
		{
			//on la reinit
			timeout_sequence_using = 0;
			robot.life.seq = E_SEQUENCE_ROBOT_NONE;
			CtrlMarcheMove( E_MOVE_STOP, E_SPEED_0 );
			CtrlTeteScanProximityAngle(NEUTRE_TETE_HORIZONTAL);
		}	
		timeout_sequence_using++;		
				
	}
	if ( DrvEventTestEvent(event, CONF_EVENT_FRONT_OF_LIGHT ))
	{
		CtrlTeteScanProximityAngle(NEUTRE_TETE_HORIZONTAL);
		robot.life.seq = E_SEQUENCE_ROBOT_NONE;
	}
	if ( DrvEventTestEvent(event, CONF_EVENT_FRONT_OF_OBJECT ))
	{
		CtrlTeteScanProximityAngle(NEUTRE_TETE_HORIZONTAL);
		robot.life.seq = E_SEQUENCE_ROBOT_NONE;
	}	
	

	
}

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) 
{
	return robot.life.init;	
}


