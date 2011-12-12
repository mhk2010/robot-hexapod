/*
 * ctrl_proximity.c
 *
 * Created: 12/12/2011 19:11:35
 *  Author: louis
 */ 

#include "ctrl_proximity.h"
#include "ctrl_tete.h"



static Int8U temp_angle = START_ANGLE_DETECT;
static Int16U angles_mesure[120U];
static Int16U index_tab ;
static Int8U start_timeout = 0U;
static Boolean launch_proximity_scan = FALSE;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlProximity( void ) 
{
	temp_angle = START_ANGLE_DETECT;
	Int8U loop ;
	for(loop = 0; loop < 120 ; loop++)
	{
		angles_mesure[loop] = 0; 
	}
	index_tab =0;
	start_timeout = 0U;
	launch_proximity_scan = FALSE;
}
//dispatcher
void CtrlProximityDispatcher( Event_t event )  
{
	if ( DrvEventTestEvent( event, CONF_EVENT_TIMER_100MS ))
	{	
		if( launch_proximity_scan != FALSE)
		{
			if(start_timeout == 2)
			{
				if(temp_angle < END_ANGLE_DETECT)
				{
					index_tab = temp_angle - 20;
					angles_mesure[index_tab] = CtrlUltraSonReadMesure();
					temp_angle += 1;
					CtrlUltraSonLaunchMesure();
					DrvServoMoveToPosition( CONF_SERVO_TETE_H, temp_angle );
					if( angles_mesure[index_tab] > SECURITY_PERIMETER )
					{
						DrvEventAddEvent( CONF_EVENT_FIND_NO_OBJECT );
					}
					else
					{	
						DrvEventAddEvent( CONF_EVENT_FIND_NEAR_OBJECT );
					}					
				}	
				else
				{
					temp_angle = NEUTRE_TETE_HORIZONTAL;
					index_tab = 0;
					start_timeout = 0U;
					launch_proximity_scan = FALSE;
					DrvServoMoveToPosition( CONF_SERVO_TETE_H, temp_angle );
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
	for(loop = 0; loop < 120 ; loop++)
	{
		angles_mesure[loop] = 0; 
	}
	start_timeout = 0U;
	launch_proximity_scan = TRUE;
}

