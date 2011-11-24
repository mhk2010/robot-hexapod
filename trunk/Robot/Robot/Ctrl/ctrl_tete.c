/*
 * ctrl_tete.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_tete.h"
#include "ctrl_ultrason.h"



#define TIMEOUT_SPEED			5 //(500ms)

#define START_ANGLE_DETECT		NEUTRE_TETE_HORIZONTAL - 60 
#define END_ANGLE_DETECT		NEUTRE_TETE_HORIZONTAL + 60  
#define OFFSET_ANGLE_DETECT		4 

static Int8U inter_timeout_scan_angle = 0;
static Boolean mesurelumiere_g_d = FALSE;

static tete_t tete;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CtrlTeteEndAdcConvertion( Int8U index_adc ,Int16U adc_data );

//on bouge la tete
static void CtrlTeteMoveForScanning( void );

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlTete( void ) 
{ 
	
	mesurelumiere_g_d = FALSE;
	inter_timeout_scan_angle = 0;
	
	tete.scanning = FALSE;
	tete.mesure_ultrason = 0U;
	tete.position.angle_h = NEUTRE_TETE_HORIZONTAL;
	tete.position.angle_v = NEUTRE_TETE_VERTICAL;
	tete.mesure_ldr_gauche = 0U;
	tete.mesure_ldr_droite = 0U;
	
	DrvAdcEnableAdc( CONF_ADC_IR );
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
		tete.mesure_ultrason = CtrlUltraSonReadMesure();
		if( tete.scanning == TRUE )
		{
			//on est en scan on incremente la valeur de l'angle horizontal
			tete.position.angle_h += OFFSET_ANGLE_DETECT;
		}		
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
	//si on a atteind la limite de temps
	if( inter_timeout_scan_angle >= TIMEOUT_SPEED )
	{
		if( tete.position.angle_h <= END_ANGLE_DETECT )
		{
			DrvServoMoveToPosition( CONF_SERVO_TETE_H, tete.position.angle_h );
			CtrlUltraSonLaunchMesure();
		}
		else
		{
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