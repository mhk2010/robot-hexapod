/*
 * ctrl_tete.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_tete.h"
#include "ctrl_ultrason.h"




static Int8U inter_timeout_scan_angle = 0;
static Int8U scan_angle = 0;
static Boolean mesurelumiere_g_d = FALSE;

static tete_t tete;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//callback de fin de convertion
static void CtrlTeteEndAdcConvertion( Int8U index_adc ,Int16U adc_data );

//on bouge la tete
static void CtrlTeteMoveForScanning( void );

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlTete( void ) 
{ 
	//init des variables privées
	mesurelumiere_g_d = FALSE;
	scan_angle = 0;
	
	//on init la structure tete
	tete.scanning = FALSE;
	tete.position.angle_h = NEUTRE_TETE_HORIZONTAL;
	tete.position.angle_v = NEUTRE_TETE_VERTICAL;
	tete.mesure_ldr_gauche = 0U;
	tete.mesure_ldr_droite = 0U;
	for(Int8U loop_angle = 0U ; loop_angle < NB_ANGLE_DETECT ; loop_angle++)
	{
		tete.mesure_ultrason[ loop_angle ] = 0;
	}	
	
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
		//si on ne scan pas alors on mesure regulierement la distance d'un objet
		if( tete.scanning == FALSE )
		{
			//on lance la mesure ultrason 
			CtrlUltraSonLaunchMesure();
		}
		else
		{
			//on lit la mesure
			tete.mesure_ultrason[ scan_angle ] = CtrlUltraSonReadMesure();
			//on bouge la tete pour le prochain scan
			CtrlTeteMoveForScanning();
		}			
	}
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
		//si on ne scan pas alors on mesure regulierement les capteurs
		if( tete.scanning == FALSE )
		{
			//on prend les mesures de lumieres
			if( mesurelumiere_g_d == FALSE)
			{
				DrvAdcStartConvertion( CONF_ADC_LDR_GAUCHE , CtrlTeteEndAdcConvertion );
			}
			else
			{
				DrvAdcStartConvertion( CONF_ADC_LDR_DROITE , CtrlTeteEndAdcConvertion );
			}
		}		
	}
	if ( DrvEventTestEvent(event ,CONF_EVENT_US_SENSOR ))
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
void CtrlTeteStartScanHorizontal( void )
{
	//on positionne la tete a l'endroit voulu
	DrvServoMoveToPosition( CONF_SERVO_TETE_H , START_ANGLE_DETECT );
	tete.position.angle_h = START_ANGLE_DETECT ;
	tete.scanning = TRUE;
	scan_angle = 0;
}

////////////////////////////////////////PRIVATE FUNCTIONS//////////////////////////////////////////

static void CtrlTeteEndAdcConvertion( EIoPin pin_name ,Int16U adc_data )
{
	//on toggle sur le choix de la lecture de la LDR
	mesurelumiere_g_d ^= 0x01;
	if( pin_name == CONF_ADC_LDR_GAUCHE )
	{
		tete.mesure_ldr_gauche = adc_data;
	}
	else if( pin_name == CONF_ADC_LDR_DROITE ) 
	{
		tete.mesure_ldr_droite = adc_data;
	}
}


//on bouge la tete pour faire un scan IR de ce qu'il y a devant
static void CtrlTeteMoveForScanning( void )
{
	//si on a atteind la limite de temps inter scan
	if( inter_timeout_scan_angle >= TIMEOUT_HEAD_SCAN_SPEED )
	{
		//si on a pas fini de scanner
		if( tete.position.angle_h <= END_ANGLE_DETECT )
		{
			//on bouge le servo de la tete horizontal
			tete.position.angle_h += OFFSET_ANGLE_DETECT;
			scan_angle++;
			DrvServoMoveToPosition( CONF_SERVO_TETE_H, tete.position.angle_h );
			//on lance la mesure sur le capteur
			CtrlUltraSonLaunchMesure();
		}
		else
		{
			//on a fini le scan
			//on met la tete au milieu
			DrvServoMoveToPosition( CONF_SERVO_TETE_H, NEUTRE_TETE_HORIZONTAL );
			tete.position.angle_h = START_ANGLE_DETECT ;
			tete.scanning = FALSE;
		}
		inter_timeout_scan_angle = 0;
	}
	else
	{
		inter_timeout_scan_angle++;
	}
}