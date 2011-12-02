/*
 * ctrl_tete.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_tete.h"
#include "ctrl_ultrason.h"


#define OFFSET_LIGHT 10

static Int8U timeout_event_200ms = 0;
static Int8U timeout_inter_scan_angle = 0;
static Int8U timeout_head_follow_light = 0;
static Boolean switch_mesure_ldr_g_d = FALSE;
static Boolean switch_mesure_us = FALSE;

static tete_t tete;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//on bouge la tete sur un angle et on scan
static void CtrlTeteScanningProximityAngle( void ) ;

//on cherche la position ou la lumiere est la plus forte
static void CtrlTeteSearchingLight( void );

//on cherche si il y a quelque chose devant
static void CtrlTeteScanningProximity( void );

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlTete( void ) 
{ 
	//init des variables privées
	switch_mesure_ldr_g_d = FALSE;
	timeout_event_200ms = 0;
	//on init la structure tete
	tete.scanning_proximity_angle = FALSE;
	tete.scanning_proximity = FALSE;
	tete.scanning_light = FALSE;
	tete.follow_light_enable = FALSE;
	tete.find_light_angle = FALSE;
	tete.light_angle = NEUTRE_TETE_HORIZONTAL;
	tete.position.angle_h = NEUTRE_TETE_HORIZONTAL;
	tete.position.angle_v = NEUTRE_TETE_VERTICAL;
	tete.mesure_ldr_gauche = 0U;
	tete.mesure_ldr_droite = 0U;
	tete.mesure_ultrason = 0U;	
	tete.mesure_infrarouge = 0U;
	
	//on ajoute les ADCs
	DrvAdcEnableAdc( CONF_ADC_LDR_GAUCHE );
	DrvAdcEnableAdc( CONF_ADC_LDR_DROITE );
	DrvAddServo( CONF_SERVO_TETE_H , NEUTRE_TETE_HORIZONTAL );
	DrvAddServo( CONF_SERVO_TETE_V , NEUTRE_TETE_VERTICAL );
	
}

//dispatcher
void CtrlTeteDispatcher( Event_t event )  
{
	if( tete.follow_light_enable == TRUE )
	{
		if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_10MS ))
		{
			timeout_head_follow_light++;
			if( timeout_head_follow_light == 5)
			{
				timeout_head_follow_light = 0;
				CtrlTeteSearchingLight();
			}
		}			
	}
	
	if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_100MS ))
	{
		//si on ne scan pas alors on mesure regulierement les capteurs
		if( tete.scanning_light == TRUE )
		{
			CtrlTeteSearchingLight();
		}
		else if( tete.scanning_proximity == TRUE )
		{
			CtrlTeteScanningProximity();
		}
		else if( tete.scanning_proximity_angle == TRUE )
		{
			timeout_event_200ms++;
			//le temps que le servo atteigne sa position
			if(timeout_event_200ms == 2)
			{
				CtrlTeteScanningProximityAngle();
				timeout_event_200ms = 0;
			}
			
		}	
	}
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
				
	}		
}

//on recupere la structure
tete_t* CtrlTeteGetStruct( void )
{
	return &tete;	
}

//on fait un scan horizontal
void CtrlTeteMove( Int8U angle_horizontal, Int8U angle_vertical)
{
	tete.position.angle_h = angle_horizontal;
	tete.position.angle_v = angle_vertical;
	//on positionne la tete a l'endroit voulu
	DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
	DrvServoMoveToPosition( CONF_SERVO_TETE_V , tete.position.angle_v );
}

//on suit la lumiere
void CtrlTeteStartFollowLight( void )
{
	tete.follow_light_enable = TRUE;
	timeout_head_follow_light = 0;
}

//on fait un scan a un angle precis
void CtrlTeteScanProximityAngle( Int8U angle )
{
	if(tete.scanning_proximity_angle != TRUE)
	{
		//on positionne la tete a l'endroit voulu
		tete.position.angle_h = angle ;
		tete.follow_light_enable = FALSE;
		tete.scanning_proximity_angle = TRUE;
		DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
		switch_mesure_us = FALSE;
	}		
}

//on fait un scan horizontal
void CtrlTeteStartScanProximity( void )
{
	if(tete.scanning_proximity != TRUE)
	{
		//on positionne la tete a l'endroit voulu
		tete.position.angle_h = START_ANGLE_DETECT ;
		tete.follow_light_enable = FALSE;
		DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
		tete.scanning_proximity = TRUE;
	}		
}

//on fait un scan de la lumiere
void CtrlTeteStartScanLight( void )
{
	if(tete.scanning_light != TRUE)
	{
		//on positionne la tete a l'endroit voulu
		tete.position.angle_h = NEUTRE_TETE_HORIZONTAL ;
		tete.follow_light_enable = FALSE;
		DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
		tete.scanning_light = TRUE;
		tete.find_light_angle = FALSE;
	}
}
////////////////////////////////////////PRIVATE FUNCTIONS//////////////////////////////////////////
//on bouge la tete sur un angle et on scan
static void CtrlTeteScanningProximityAngle( void )
{
	if ( switch_mesure_us == FALSE )
	{
		//on envoie le scan 
		CtrlUltraSonLaunchMesure();
		switch_mesure_us = TRUE;
	}
	else
	{
		//on lance les lecture de capteurs
		tete.mesure_ultrason = CtrlUltraSonReadMesure();
		//tete.mesure_infrarouge = DrvAdcReadChannel( CONF_ADC_IR );
		tete.scanning_proximity_angle = FALSE;
		if( tete.mesure_ultrason > SECURITY_PERIMETER )
		{
			DrvEventAddEvent( CONF_EVENT_FIND_NO_OBJECT );
		}
		else
		{
			//on confirme par le capteur IR
			//if( tete.mesure_infrarouge > 350)
			{
				DrvEventAddEvent( CONF_EVENT_FIND_NEAR_OBJECT );
			}
			/*else
			{
				DrvEventAddEvent( CONF_EVENT_FIND_NO_OBJECT );
			}*/
		}				
	}
}

//on bouge la tete pour faire un scan IR de ce qu'il y a devant
static void CtrlTeteScanningProximity( void )
{
	//si on a atteind la limite de temps inter scan
	if( timeout_inter_scan_angle >= TIMEOUT_HEAD_SCAN_SPEED )
	{
		//si on a pas fini de scanner
		if( tete.position.angle_h <= END_ANGLE_DETECT )
		{
			//on lance la mesure sur le capteur
			
			if( tete.position.angle_h != START_ANGLE_DETECT )
			{
				//on ne lit pas la premiere mesure car elle a pas été effectué
				//on lance les lecture de capteurs
				tete.mesure_ultrason = CtrlUltraSonReadMesure();
				//tete.mesure_infrarouge = DrvAdcReadChannel( CONF_ADC_IR );
			}
			CtrlUltraSonLaunchMesure();
			
			if(( tete.mesure_ultrason > SECURITY_PERIMETER )||( tete.position.angle_h == START_ANGLE_DETECT ))
			{
				//on bouge le servo de la tete horizontal
				tete.position.angle_h += OFFSET_ANGLE_DETECT;
				DrvServoMoveToPosition( CONF_SERVO_TETE_H, tete.position.angle_h );
			}
			else
			{
				//on confirme par le capteur IR
				/*if( tete.mesure_infrarouge > 350)
				{
					DrvEventAddEvent( CONF_EVENT_FIND_NEAR_OBJECT );
				}
				else
				{
					DrvEventAddEvent( CONF_EVENT_FIND_NO_OBJECT );
				}*/
				DrvEventAddEvent( CONF_EVENT_FIND_NEAR_OBJECT );
				tete.scanning_proximity = FALSE;
			}
		}
		else
		{
			//on a fini le scan
			
			//on met la tete au milieu
			DrvServoMoveToPosition( CONF_SERVO_TETE_H, NEUTRE_TETE_HORIZONTAL );
			tete.position.angle_h = START_ANGLE_DETECT ;
			tete.scanning_proximity = FALSE;
		}
		timeout_inter_scan_angle = 0;
	}
	else
	{
		timeout_inter_scan_angle++;
	}
}

//on cherche la position ou la lumiere est la plus forte
static void CtrlTeteSearchingLight( void )
{
	Int8U offset_min = 1;
	Int8U offset_mid = 3;
	Int8U offset_max = 6;
	//on lance la convertion 
	tete.mesure_ldr_gauche = DrvAdcReadChannel( CONF_ADC_LDR_GAUCHE );
	//on lance la convertion 
	tete.mesure_ldr_droite = DrvAdcReadChannel( CONF_ADC_LDR_DROITE  );
	
	//on calcul un offset dynamique en fct du taux de luminosité
	if( tete.mesure_ldr_gauche + tete.mesure_ldr_gauche < 1000 )
	{
		offset_min = 1;
		offset_mid = 2;
		offset_max = 3;
	}
	else if( tete.mesure_ldr_gauche + tete.mesure_ldr_gauche < 1500 )
	{
		
		offset_min = 1;
		offset_mid = 3;
		offset_max = 6;
	}
	else if( tete.mesure_ldr_gauche + tete.mesure_ldr_gauche < 2000 )
	{
		offset_min = 1;
		offset_mid = 4;
		offset_max = 8;
	}
	else
	{
		offset_min = 1;
		offset_mid = 5;
		offset_max = 10;
	}
	//si les 2 mesures des LDRs sont valables
	if( ( tete.mesure_ldr_gauche != 0U ) && ( tete.mesure_ldr_droite != 0U ) )
	{
		//on affine la recherche par dicotomie
		if( tete.mesure_ldr_gauche < tete.mesure_ldr_droite )
		{
			if(( tete.mesure_ldr_droite - tete.mesure_ldr_gauche ) > ( 4 * OFFSET_LIGHT ) )
			{
				//on positionne la tete a l'endroit voulu
				if( (tete.position.angle_h - offset_max) > MIN_TETE_HORIZONTAL )
				{
					tete.position.angle_h -= offset_max ;
				}
				else
				{
					tete.position.angle_h = MIN_TETE_HORIZONTAL ;
					tete.find_light_angle = TRUE;
				}
			}
			else if(( tete.mesure_ldr_droite - tete.mesure_ldr_gauche ) > ( 2 * OFFSET_LIGHT ) )
			{
				//on positionne la tete a l'endroit voulu
				if( (tete.position.angle_h - offset_mid) > MIN_TETE_HORIZONTAL )
				{
					tete.position.angle_h -= offset_mid ;
				}
				else
				{
					tete.position.angle_h = MIN_TETE_HORIZONTAL ;
					tete.find_light_angle = TRUE;
				}
			}
			else if(( tete.mesure_ldr_droite - tete.mesure_ldr_gauche ) > OFFSET_LIGHT )
			{
				//on positionne la tete a l'endroit voulu
				if( (tete.position.angle_h - offset_min) > MIN_TETE_HORIZONTAL )
				{
					tete.position.angle_h -= offset_min ;
				}
				else
				{
					tete.position.angle_h = MIN_TETE_HORIZONTAL ;
					tete.find_light_angle = TRUE;
				}
			}
			else
			{
				tete.find_light_angle = TRUE;
			}
		}	
		else
		{
			if(( tete.mesure_ldr_gauche - tete.mesure_ldr_droite ) > ( 4 * OFFSET_LIGHT ) )
			{
				//on positionne la tete a l'endroit voulu
				if( (tete.position.angle_h + offset_max) < MAX_TETE_HORIZONTAL )
				{
					tete.position.angle_h += offset_max ;
				}
				else
				{
					tete.position.angle_h = MAX_TETE_HORIZONTAL ;
					tete.find_light_angle = TRUE;
				}	
			}
			else if(( tete.mesure_ldr_gauche - tete.mesure_ldr_droite ) > ( 2 * OFFSET_LIGHT ) )
			{
				//on positionne la tete a l'endroit voulu
				if( (tete.position.angle_h + offset_mid) < MAX_TETE_HORIZONTAL )
				{
					tete.position.angle_h += offset_mid ;
				}
				else
				{
					tete.position.angle_h = MAX_TETE_HORIZONTAL ;
					tete.find_light_angle = TRUE;
				}
			}
			else if(( tete.mesure_ldr_gauche - tete.mesure_ldr_droite ) > OFFSET_LIGHT )
			{
				//on positionne la tete a l'endroit voulu
				if( (tete.position.angle_h + offset_min) < MAX_TETE_HORIZONTAL )
				{
					tete.position.angle_h += offset_min ;
				}
				else
				{
					tete.position.angle_h = MAX_TETE_HORIZONTAL ;
					tete.find_light_angle = TRUE;
				}
			}
			else
			{
				tete.find_light_angle = TRUE;
			}
		}
		if( tete.find_light_angle == TRUE )
		{
			tete.light_angle = tete.position.angle_h;
			tete.scanning_light = FALSE;
			tete.find_light_angle = FALSE;	
			//on envoie l'event 
			DrvEventAddEvent( CONF_EVENT_FIND_MAX_LIGHT );	
					
		}
		DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );		
	}
}	
