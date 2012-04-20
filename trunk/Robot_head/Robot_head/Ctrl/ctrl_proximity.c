/*
 * ctrl_proximity.c
 *
 * Created: 12/12/2011 19:11:35
 *  Author: louis
 */ 

#include "ctrl_proximity.h"
#include "ctrl_tete.h"
#include "ctrl_ultrason.h"


#define NB_SHOT		24
static Int8U temp_angle = START_ANGLE_DETECT;
static Int16U angles_mesure[NB_SHOT];
static Int16U index_tab ;
static Int8U start_timeout = 0U;
static Boolean launch_proximity_scan = FALSE;
static proximity_result_t result_proximity;
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlProximity( void ) 
{
	temp_angle = START_ANGLE_DETECT;
	Int8U loop ;
	for(loop = 0; loop < NB_SHOT ; loop++)
	{
		angles_mesure[loop] = 0; 
	}
	index_tab =0;
	start_timeout = 0U;
	result_proximity.mesure_droite = 0;
	result_proximity.mesure_gauche = 0;
	result_proximity.mesure_milieu = 0;
	launch_proximity_scan = FALSE;
}

//dispatcher
void CtrlProximityDispatcher( Event_t event )  
{
	if ( DrvEventTestEvent( event, CONF_EVENT_TIMER_100MS ))
	{	
		if( launch_proximity_scan != FALSE)
		{
			if(start_timeout == 4)
			{
				if(temp_angle < END_ANGLE_DETECT)
				{
					//on mesure sur chaque angle
					index_tab = ( temp_angle - START_ANGLE_DETECT ) / 5;
					angles_mesure[index_tab] = CtrlUltraSonReadMesure();
					temp_angle += 5;
					CtrlUltraSonLaunchMesure();
					DrvServoMoveToPosition( CONF_SERVO_TETE_H, temp_angle );
				}	
				else
				{
					//on remet a zero les variables
					temp_angle = NEUTRE_TETE_HORIZONTAL;
					start_timeout = 0U;
					index_tab = 0;	
					launch_proximity_scan = FALSE;
					DrvServoMoveToPosition( CONF_SERVO_TETE_H, temp_angle );
					
					for(index_tab = 0; index_tab < NB_SHOT ; index_tab+=2)
					{
						//droite
						if( index_tab < (NB_SHOT / 3) )
						{		
							//on met des coef plus importants sur les cote	
							result_proximity.mesure_droite += angles_mesure[index_tab] ;				
						}
						//milieu
						else if( index_tab < ((NB_SHOT * 2 ) / 3) )
						{	
							result_proximity.mesure_milieu += angles_mesure[index_tab];
						}
						//gauche
						else 
						{
							result_proximity.mesure_gauche += angles_mesure[index_tab];
						}
						//angles_mesure[index_tab] = 0;
					}
					result_proximity.mesure_gauche /= 4;
					result_proximity.mesure_milieu /= 4;
					result_proximity.mesure_droite /= 4;
					//on envoie l'event de fin de scan proximite
					DrvEventAddEvent(CONF_EVENT_END_OF_PROX_SCAN);				
				}
			}
			else
			{
				//on lance des mesures en attendant la fin du timeout
				CtrlUltraSonLaunchMesure();
				start_timeout++;
			}
		}			
	}
}

//on lance un scan 
void CtrlProximityLaunchScan( void )
{
	Int8U loop ;
	for(loop = 0; loop < NB_SHOT ; loop++)
	{
		angles_mesure[loop] = 0; 
	}
	start_timeout = 0U;
	launch_proximity_scan = TRUE;
	result_proximity.mesure_droite = 0;
	result_proximity.mesure_gauche = 0;
	result_proximity.mesure_milieu = 0;
	temp_angle = START_ANGLE_DETECT;
	DrvServoMoveToPosition( CONF_SERVO_TETE_H, temp_angle );
}

proximity_result_t CtrlProximityGetScanResult( void )
{
	return result_proximity;
}	

