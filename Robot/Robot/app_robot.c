/*
 * app_robot.c
 *
 * Created: 22/11/2011 15:43:10
 *  Author: berryer
 */ 
#include "app_robot.h"

/////////////////////////////////////////PRIVATE DEFINE//////////////////////////////////////////

#define UNKNOWN_DISTANCE	0xFFFFU

/////////////////////////////////////////PRIVATE TYPEDEF//////////////////////////////////////////
//strucutre qui defini le vie du robot
typedef struct {
	Boolean init;
	Boolean prox_obj_dectected;
	Int8U angle_prox_obj_dectected;
	Int16U prox_obj_distance;
	Int16U old_prox_obj_distance;
} robot_life_t;

//strucutre qui defini le robot
typedef struct {
	robot_life_t life;
	body_member_t *body;
	head_member_t *head;
} robot_t;

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) ;

///////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
//structure robot
static robot_t robot;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
Boolean RobotLifeInit(void) 
{
	Boolean o_success = TRUE;
	//on init la structure du robot
	robot.life.init = FALSE;
	robot.life.prox_obj_dectected = FALSE;
	robot.life.prox_obj_distance = UNKNOWN_DISTANCE;
	robot.life.old_prox_obj_distance = UNKNOWN_DISTANCE;
	robot.life.angle_prox_obj_dectected = NEUTRE_TETE_HORIZONTAL;
	robot.body = CtrlMarcheGetStruct();
	robot.head = CtrlTeteGetStruct();
	
	return o_success;
}	

//on reagit aux evenements
void RobotLife ( Event_t event ) 
{
	// a l'init on lance un scan
	if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_1S ))
	{
		//si on est pas encore initialise
		if(RobotLifeCheckInit() == FALSE)
		{
			CtrlTeteStartScan();
			//on est maintenant initialiser 
			robot.life.init = TRUE;
		}
		
		//si on a detecter un objet est qu'on joue l action correspondante
		if( robot.life.prox_obj_dectected == TRUE )
		{
			//si on est pas en scan
			if( robot.head->is_scaning == FALSE )
			{
				if(robot.life.prox_obj_distance < SECURITY_PERIMETER)
				{
					//si l'objet s'eloigne
					if( robot.life.old_prox_obj_distance < robot.life.prox_obj_distance)
					{
						//on avance
						CtrlMarcheMove( E_MOVE_FORWARD , E_SERVO_VITESSE_5);					
					}
					//il se rapproche
					else
					{
						//si le dernier scanner est a gauche
						if( robot.life.angle_prox_obj_dectected > NEUTRE_TETE_HORIZONTAL )
						{
							//on avance
							CtrlMarcheMove( E_MOVE_RIGHT , E_SERVO_VITESSE_5);		
						}
						else if( robot.life.angle_prox_obj_dectected < NEUTRE_TETE_HORIZONTAL )
						{
							//on avance
							CtrlMarcheMove( E_MOVE_LEFT, E_SERVO_VITESSE_5);		
						}
						else
						{
							//si on est en marche 
							if(( robot.body->move != E_MOVE_BACKWARD ) && ( robot.body->move != E_MOVE_STOP ))
							{
								//on marche arriere
								CtrlMarcheMove( E_MOVE_BACKWARD , E_SERVO_VITESSE_5);	
							}	
						}
						
						
					}
				
					//si on est pas en scan
					if( robot.head->is_scaning == FALSE )
					{
						//on renvois une mesure US 
						CtrlUartProtocoleSendReadHeadUs();	
					}
					//on memorise la distance de l'objet
					robot.life.old_prox_obj_distance = robot.life.prox_obj_distance;	
				}	
				//il n'y a plus d'objet
				else
				{
					robot.life.prox_obj_dectected = FALSE;
				}
			}									
		}
		
	}	
	
	//on rescan toutes les 10 sec si on est stop
	if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_10S ))
	{
		//si le dernier scan est fini et que l'on est pas en mouvement 
		if(( robot.head->is_scaning == FALSE ) && ( robot.body->move == E_MOVE_STOP ) && (robot.life.prox_obj_dectected == FALSE))
		{
			CtrlTeteStartScan();
		}
	}			
	
	
	//si on recois l'event alert US on stop
	if ( DrvEventTestEvent(event, CONF_EVENT_ALERT_US_PROX ))
	{
		robot.life.prox_obj_distance = CtrlUartProtocoleReadHeadUs() ;
		//on viens de detecter un objet
		if(robot.life.prox_obj_dectected == FALSE)
		{
			//on a detecter un objet
			robot.life.prox_obj_dectected = TRUE;
			//on garde l'angle de detection
			robot.life.angle_prox_obj_dectected = robot.head->angle_h;
			//si on est entrain de scanner on stop
			if( robot.head->is_scaning == TRUE )
			{
				//on stop le scan
				CtrlTeteStopScan();
			}
			else 
			{
				//si on était en mouvement
				if( robot.body->move != E_MOVE_STOP )
				{
					//on stop
					CtrlMarcheMove( E_MOVE_STOP , E_SERVO_VITESSE_5);	
				}	
				//si on était en stop on recul
				else
				{
					//si l'objet est trop prés on recul 10cm
					if(robot.life.prox_obj_distance <= 10U)
					{
						//on stop
						CtrlMarcheMove( E_MOVE_BACKWARD , E_SERVO_VITESSE_5);	
					}
					else
					{
						//on se met en etoile
						CtrlMarcheMove( E_MOVE_STAR , E_SERVO_VITESSE_5);	
					}	
				}	
			}
		}			
	}					
}

/////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//test si on est en phase d'init
static Boolean RobotLifeCheckInit(void) 
{
	return robot.life.init;	
}


