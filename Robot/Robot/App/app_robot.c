/*
 * app_robot.c
 *
 * Created: 22/11/2011 15:43:10
 *  Author: berryer
 */ 
#include "app_robot.h"

/////////////////////////////////////////PRIVATE DEFINE//////////////////////////////////////////
#define TIMEOUT_INIT	10//1sec


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
	
	robot.life.humeur = E_HUMEUR_ROBOT_NONE;
	robot.body = CtrlMarcheGetStruct();
	robot.tete = CtrlTeteGetStruct();
	
	return o_success;
}	

//on reagit aux evenements
void RobotLife ( Event_t event ) 
{
	if( robot.life.humeur == E_HUMEUR_ROBOT_CURIEUX )
	{
		HumCuriousDispatcher(event)	;
	}
				
	//event 1 sec
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
		if( RobotLifeCheckInit() )
		{
			//on est plus en init
			robot.life.init = FALSE;
			//on lance son humeur
			HumCuriousInit(TRUE);
			robot.life.humeur = E_HUMEUR_ROBOT_CURIEUX;
		}
	}		
}

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) 
{
	return robot.life.init;	
}


