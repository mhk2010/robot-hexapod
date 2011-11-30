/*
 * ctrl_tete.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_tete.h"
#include "ctrl_ultrason.h"


#define OFFSET_LIGHT 10

static Int8U inter_timeout_scan_angle = 0;
static Boolean switch_mesure_ldr_g_d = FALSE;
static Boolean switch_mesure_us = FALSE;

static tete_t tete;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//callback de fin de convertion
static void CtrlTeteEndAdcConvertion( Int8U index_adc ,Int16U adc_data );

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
	
	//on init la structure tete
	tete.scanning_proximity_angle = FALSE;
	tete.scanning_proximity = FALSE;
	tete.scanning_light = FALSE;
	tete.find_light_angle = FALSE;
	tete.light_angle = NEUTRE_TETE_HORIZONTAL;
	tete.position.angle_h = NEUTRE_TETE_HORIZONTAL;
	tete.position.angle_v = NEUTRE_TETE_VERTICAL;
	tete.mesure_ldr_gauche = 0U;
	tete.mesure_ldr_droite = 0U;
	tete.mesure_ultrason = 0U;	
	
	//on ajoute les ADCs
	DrvAdcEnableAdc( CONF_ADC_LDR_GAUCHE );
	DrvAdcEnableAdc( CONF_ADC_LDR_DROITE );
	DrvAddServo( CONF_SERVO_TETE_H , NEUTRE_TETE_HORIZONTAL );
	DrvAddServo( CONF_SERVO_TETE_V , NEUTRE_TETE_VERTICAL );
	
}

//dispatcher
void CtrlTeteDispatcher( Event_t event )  
{
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
			CtrlTeteScanningProximityAngle();
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

//on fait un scan horizontal
void CtrlTeteScanProximityAngle( Int8U angle )
{
	if(tete.scanning_proximity_angle != TRUE)
	{
		//on positionne la tete a l'endroit voulu
		tete.position.angle_h = angle ;
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
		tete.scanning_light = TRUE;
		tete.find_light_angle = FALSE;
	}
}

////////////////////////////////////////PRIVATE FUNCTIONS//////////////////////////////////////////
static void CtrlTeteEndAdcConvertion( EIoPin pin_name ,Int16U adc_data )
{
	//on toggle sur le choix de la lecture de la LDR
	switch_mesure_ldr_g_d ^= 0x01;
	if( pin_name == CONF_ADC_LDR_DROITE )
	{
		tete.mesure_ldr_gauche = adc_data;
	}
	else if( pin_name == CONF_ADC_LDR_GAUCHE ) 
	{
		tete.mesure_ldr_droite = adc_data;
	}
}

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
		//on ne lit pas la premiere mesure car elle a pas été effectué
		tete.mesure_ultrason = CtrlUltraSonReadMesure();
		tete.scanning_proximity_angle = FALSE;
	}
}

//on bouge la tete pour faire un scan IR de ce qu'il y a devant
static void CtrlTeteScanningProximity( void )
{
	//si on a atteind la limite de temps inter scan
	if( inter_timeout_scan_angle >= TIMEOUT_HEAD_SCAN_SPEED )
	{
		//si on a pas fini de scanner
		if( tete.position.angle_h <= END_ANGLE_DETECT )
		{
			//on lance la mesure sur le capteur
			
			if( tete.position.angle_h != START_ANGLE_DETECT )
			{
				//on ne lit pas la premiere mesure car elle a pas été effectué
				tete.mesure_ultrason = CtrlUltraSonReadMesure();
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
		inter_timeout_scan_angle = 0;
	}
	else
	{
		inter_timeout_scan_angle++;
	}
}

//on cherche la position ou la lumiere est la plus forte
static void CtrlTeteSearchingLight( void )
{
	//on prend les mesures de lumieres
	if( switch_mesure_ldr_g_d == FALSE)
	{
		//on lance la convertion 
		DrvAdcStartConvertion( CONF_ADC_LDR_GAUCHE , CtrlTeteEndAdcConvertion );
		//si les 2 mesures des LDRs sont valables
		if( ( tete.mesure_ldr_gauche != 0U ) && ( tete.mesure_ldr_droite != 0U ) )
		{
			//on affine la recherche par dicotomie
			if( tete.mesure_ldr_gauche > tete.mesure_ldr_droite )
			{
				if(( tete.mesure_ldr_gauche - tete.mesure_ldr_droite ) > ( 4 * OFFSET_LIGHT ) )
				{
					//on positionne la tete a l'endroit voulu
					if( tete.position.angle_h > MIN_TETE_HORIZONTAL )
					{
						tete.position.angle_h -= 6U ;
					}
					else
					{
						tete.position.angle_h = MIN_TETE_HORIZONTAL ;
						tete.find_light_angle = TRUE;
					}
					DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
					
				}
				else if(( tete.mesure_ldr_gauche - tete.mesure_ldr_droite ) > ( 2 * OFFSET_LIGHT ) )
				{
					//on positionne la tete a l'endroit voulu
					if( tete.position.angle_h > MIN_TETE_HORIZONTAL )
					{
						tete.position.angle_h -= 3U ;
					}
					else
					{
						tete.position.angle_h = MIN_TETE_HORIZONTAL ;
						tete.find_light_angle = TRUE;
					}
					DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
				}
				else if(( tete.mesure_ldr_gauche - tete.mesure_ldr_droite ) > OFFSET_LIGHT )
				{
					//on positionne la tete a l'endroit voulu
					if( tete.position.angle_h > MIN_TETE_HORIZONTAL )
					{
						tete.position.angle_h -= 1U ;
					}
					else
					{
						tete.position.angle_h = MIN_TETE_HORIZONTAL ;
						tete.find_light_angle = TRUE;
					}
					DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
				}
				else
				{
					tete.find_light_angle = TRUE;
				}
			}	
			else
			{
				if(( tete.mesure_ldr_droite - tete.mesure_ldr_gauche ) > ( 4 * OFFSET_LIGHT ) )
				{
					//on positionne la tete a l'endroit voulu
					if( tete.position.angle_h < MAX_TETE_HORIZONTAL )
					{
						tete.position.angle_h += 6U ;
					}
					else
					{
						tete.position.angle_h = MAX_TETE_HORIZONTAL ;
						tete.find_light_angle = TRUE;
					}
					DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
				}
				else if(( tete.mesure_ldr_droite - tete.mesure_ldr_gauche ) > ( 2 * OFFSET_LIGHT ) )
				{
					//on positionne la tete a l'endroit voulu
					if( tete.position.angle_h < MAX_TETE_HORIZONTAL )
					{
						tete.position.angle_h += 3U ;
					}
					else
					{
						tete.position.angle_h = MAX_TETE_HORIZONTAL ;
						tete.find_light_angle = TRUE;
					}
					DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
				}
				else if(( tete.mesure_ldr_droite - tete.mesure_ldr_gauche ) > OFFSET_LIGHT )
				{
					//on positionne la tete a l'endroit voulu
					if( tete.position.angle_h < MAX_TETE_HORIZONTAL )
					{
						tete.position.angle_h += 1U ;
					}
					else
					{
						tete.position.angle_h = MAX_TETE_HORIZONTAL ;
						tete.find_light_angle = TRUE;
					}
					DrvServoMoveToPosition( CONF_SERVO_TETE_H , tete.position.angle_h );
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
				//on envoie l'event 
				DrvEventAddEvent( CONF_EVENT_FIND_MAX_LIGHT );	
					
			}		
		}
	}
	else
	{
		//on lance la convertion 
		DrvAdcStartConvertion( CONF_ADC_LDR_DROITE , CtrlTeteEndAdcConvertion );
	}
}	
