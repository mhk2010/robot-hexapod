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
	proximity_result_t res;
} robot_life_t;

//strucutre qui defini le robot
typedef struct {
	robot_life_t life;
	move_t *body;
} robot_t;

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) ;

///////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
//structure robot
static robot_t robot;
static Int8U nb_sec_marche = 0;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
Boolean RobotLifeInit(void) 
{
	Boolean o_success = TRUE;
	//on init la structure du robot
	robot.life.init = FALSE;
	robot.body = CtrlMarcheGetStruct();
	
	return o_success;
}	

//on reagit aux evenements
void RobotLife ( Event_t event ) 
{
	//event 1 sec
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
		if( RobotLifeCheckInit() == FALSE )
		{
			//on est plus en init
			robot.life.init = TRUE;
			CtrlProximityLaunchScan();
		}
		if(robot.body->move != E_MOVE_STOP)
		{//on est entrain de faire un mmouvement
			nb_sec_marche++;
			if( nb_sec_marche == 2 )
			{
				CtrlMarcheMoveWantStop();
			}
		}
		else if( nb_sec_marche == 2 )
		{
			nb_sec_marche++;
		}
		else if( nb_sec_marche == 3 )
		{
			nb_sec_marche++;
			CtrlProximityLaunchScan();
			nb_sec_marche = 0;
		}
	}
	//on a fini de scanner
	if ( DrvEventTestEvent(event, CONF_EVENT_END_OF_PROX_SCAN ))
	{
		//on recuperere les donnee du scan 
		robot.life.res = CtrlProximityGetScanResult();
		//on traite les donnee en mouvement
		if(
		   (robot.life.res.mesure_droite > 20) && 
		   (robot.life.res.mesure_milieu > 20) && 
		   (robot.life.res.mesure_gauche > 20)
		  )
		{
			if(
			   (robot.life.res.mesure_droite >= robot.life.res.mesure_milieu) && 
			   (robot.life.res.mesure_droite >= robot.life.res.mesure_gauche)
			  )
			{
				//on va a droite
				CtrlMarcheMove(E_MOVE_RIGHT, E_SPEED_3 );
			}
			else if(
			   (robot.life.res.mesure_gauche >= robot.life.res.mesure_milieu) && 
			   (robot.life.res.mesure_gauche >= robot.life.res.mesure_droite)
			  )
			{
				//on va a gauche
				CtrlMarcheMove(E_MOVE_LEFT, E_SPEED_3 );
			}
			else if(
			   (robot.life.res.mesure_milieu >= robot.life.res.mesure_gauche) && 
			   (robot.life.res.mesure_milieu >= robot.life.res.mesure_droite)
			  )
			{
				//on va tout droit
				CtrlMarcheMove(E_MOVE_FORWORD, E_SPEED_3 );
			}
		}
		else
		{
			//il y a un obstacle tres pres de nous
			//on recul
			CtrlMarcheMove(E_MOVE_BACKWORD, E_SPEED_3 );
		}		
		nb_sec_marche = 0;
	}					
}

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) 
{
	return robot.life.init;	
}


