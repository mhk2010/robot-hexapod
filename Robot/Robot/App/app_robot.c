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
	move_t *body;
	tete_t *tete;
} robot_t;

typedef enum EESequencement
{
  E_SEQUENCE_FACE_LUMIERE,
  E_SEQUENCE_FACE_LUMIERE_IN_USE,
  E_SEQUENCE_ULTRASON,
  E_SEQUENCE_ULTRASON_IN_USE,
  E_SEQUENCE_BUSY,
  E_SEQUENCE_NONE,
}ESequencement;
/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) ;

static void RobotLifeFollowLight(void) ;
static ESequencement step_sequencement = E_SEQUENCE_NONE;

///////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
static robot_t robot;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
Boolean RobotLifeInit(void) 
{
	Boolean o_success = TRUE;
	step_sequencement = E_SEQUENCE_FACE_LUMIERE;
	//on init la structure du robot
	robot.life.init = TRUE;
	robot.life.end = FALSE;
	robot.body = CtrlMarcheGetStruct();
	robot.tete = CtrlTeteGetStruct();
	
	return o_success;
}	

//onreagit aux evenements
void RobotLife ( Event_t event ) 
{
	//event 1 sec
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
		if(step_sequencement == E_SEQUENCE_FACE_LUMIERE)
		{
			//on lance le scan de lumiere
			CtrlTeteStartScanLight();
			step_sequencement = E_SEQUENCE_FACE_LUMIERE_IN_USE;
		}
		else if(step_sequencement == E_SEQUENCE_ULTRASON)
		{
			CtrlTeteStartScanProximity();
			step_sequencement = E_SEQUENCE_ULTRASON_IN_USE;
		}
	}
	if ( DrvEventTestEvent(event, CONF_EVENT_FIND_MAX_LIGHT ))
	{
		//on passe directement a l'etape de scan de proximité
		if( robot.tete->light_angle < NEUTRE_TETE_HORIZONTAL )
		{
			//on test si on fait un mouvement de plus
			if(( NEUTRE_TETE_HORIZONTAL - robot.tete->light_angle ) > 10 )
			{				
				CtrlMarcheMoveStep( E_MOVE_RIGHT, E_SPEED_5 ) ;
			}
			else
			{
				step_sequencement = E_SEQUENCE_FACE_LUMIERE;
			}	
		}
		else
		{	
			//on test si on fait un mouvement de plus
			if(( robot.tete->light_angle - NEUTRE_TETE_HORIZONTAL ) > 10 )
			{				
				CtrlMarcheMoveStep( E_MOVE_LEFT, E_SPEED_5 ) ;
			}
			else
			{
				step_sequencement = E_SEQUENCE_FACE_LUMIERE;
			}	
		}
	}
	if ( DrvEventTestEvent(event ,CONF_EVENT_MOVE_END ))
	{
		if(step_sequencement == E_SEQUENCE_FACE_LUMIERE_IN_USE)
		{
			step_sequencement = E_SEQUENCE_FACE_LUMIERE;
		}
		else if(step_sequencement == E_SEQUENCE_ULTRASON_IN_USE )
		{
			step_sequencement = E_SEQUENCE_ULTRASON;
		}
	}		
	
	if ( DrvEventTestEvent(event ,CONF_EVENT_FIND_NEAR_OBJECT ))
	{
		//on a vu quelque chose on recul
		CtrlMarcheMoveStep( E_MOVE_BACKWORD, E_SPEED_5 ) ;
	}		
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_100MS ))
	{

	}
}

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) 
{
	return robot.life.init;	
}


static void RobotLifeFollowLight(void) 
{
	step_sequencement = E_SEQUENCE_FACE_LUMIERE;
}