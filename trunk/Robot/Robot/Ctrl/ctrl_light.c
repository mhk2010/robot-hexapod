/*
 * ctrl_light.c
 *
 * Created: 12/12/2011 19:26:48
 *  Author: louis
 */ 

#include "Ctrl/ctrl_light.h"
#include "Ctrl/ctrl_tete.h"

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//renvoit le taux de luminosite de l'environnement
static luminosity_level_t CtrlLightGetLightIntensity( void );

/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Boolean launch_follow_light = FALSE;
static Int8U start_timeout_follow_light = 0U;
static Int16U mesure_ldr_gauche = 0U;
static Int16U mesure_ldr_droite = 0U;
static luminosity_level_t ambiante_luminosity = 0U;
static Int8U angle_follow_light = NEUTRE_TETE_HORIZONTAL;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlLight( void ) 
{
	launch_follow_light = FALSE;
	start_timeout_follow_light = 0U;
	mesure_ldr_gauche = 0U;
	mesure_ldr_droite = 0U;
	ambiante_luminosity = 0U;
	angle_follow_light= NEUTRE_TETE_HORIZONTAL;
}

//dispatcher
void CtrlLightDispatcher( Event_t event )  
{
	if ( DrvEventTestEvent( event, CONF_EVENT_TIMER_10MS ))
	{	
		if( launch_follow_light != FALSE)
		{
			start_timeout_follow_light++;
			if( start_timeout_follow_light == 5U)
			{
				start_timeout_follow_light = 0U;
				//on test le taux de luminosité de l'environnement
				ambiante_luminosity = CtrlLightGetLightIntensity();
				if( mesure_ldr_gauche < mesure_ldr_droite )
				{
					if((mesure_ldr_droite - mesure_ldr_gauche) > 200)
					{
						angle_follow_light -= 10;
					}
					else if((mesure_ldr_droite - mesure_ldr_gauche) > 100)
					{
						angle_follow_light -= 5;
					}
					else
					{
						angle_follow_light -= 1;
						if((mesure_ldr_droite - mesure_ldr_gauche) < 2)
						{
							//on a trouve que la source lumineuse est sur ub des cote du robot
							DrvEventAddEvent( CONF_EVENT_FIND_MAX_LIGHT );	
							launch_follow_light = FALSE;	
						}
					}
				}	
				else
				{
					if((mesure_ldr_gauche - mesure_ldr_droite) > 200)
					{
						angle_follow_light += 10;
					}
					else if((mesure_ldr_gauche - mesure_ldr_droite) > 100)
					{
						angle_follow_light += 5;
					}
					else
					{
						angle_follow_light += 1;
						if((mesure_ldr_gauche - mesure_ldr_droite) < 2)
						{
							//on a trouve que la source lumineuse est sur ub des cote du robot
							DrvEventAddEvent( CONF_EVENT_FIND_MAX_LIGHT );	
							launch_follow_light = FALSE;	
						}
					}
				}
				if(( angle_follow_light <= MAX_TETE_HORIZONTAL ) && ( angle_follow_light >= MIN_TETE_HORIZONTAL ))
				{
					DrvServoMoveToPosition( CONF_SERVO_TETE_H , angle_follow_light );
				}
				else
				{
					//on a trouve que la source lumineuse est sur ub des cote du robot
					DrvEventAddEvent( CONF_EVENT_FIND_MAX_LIGHT );	
					launch_follow_light = FALSE;		
				}						
			}
			else
			{
				//on lance la convertion 
				mesure_ldr_gauche = DrvAdcReadChannel( CONF_ADC_LDR_GAUCHE );
				//on lance la convertion 
				mesure_ldr_droite = DrvAdcReadChannel( CONF_ADC_LDR_DROITE  );
			}
		}					
	}
}

//on lance un scan 
void CtrlLightLaunchFollowLight( void )
{
	launch_follow_light = TRUE;
	mesure_ldr_gauche = 0U;
	mesure_ldr_droite = 0U;
	start_timeout_follow_light = 0U;
	ambiante_luminosity = 0U;
	angle_follow_light= NEUTRE_TETE_HORIZONTAL;
	DrvServoMoveToPosition( CONF_SERVO_TETE_H , angle_follow_light);
}


/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

//renvoit le taux de luminosite de l'environnement
static luminosity_level_t CtrlLightGetLightIntensity( void )
{
	luminosity_level_t lum;
	if (( mesure_ldr_gauche + mesure_ldr_droite ) < 500 )
	{
		lum = VERY_HIGHT_LUMINOSITY;
	}
	else if (( mesure_ldr_gauche + mesure_ldr_droite ) < 1500 )
	{
		lum = HIGHT_LUMINOSITY;
	}
	else if (( mesure_ldr_gauche + mesure_ldr_droite ) <= 2000 )
	{
		lum = LOW_LUMINOSITY;
	}
	else if (( mesure_ldr_gauche + mesure_ldr_droite ) > 2000 )
	{
		lum = DARK_ROOM;
	}
	return lum;
}