/*
 * ctrl_ultrason.c
 *
 * Created: 16/11/2011 12:07:43
 *  Author: berryer
 */ 

#include "ctrl_ultrason.h"

#define SRF08_SLAVE_ADDRESS		0xE0	//addresse du module SRF08

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//permet de lire la valeur mesuré en cm par le dernier pulse envoyé
static void CtrlUltraSonReadSensorMesure( void ) ;
//permet d'envoyé un pulse 
static void CtrlUltraSonSendPulse( void ) ;

/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Boolean want_mesure = FALSE;
static Boolean send_pulse = FALSE;
static Int16U us_mesure = 0;


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlUltraSon( void ) 
{
	DrvI2CUltraSon();
	want_mesure = FALSE;
	send_pulse = FALSE;
	us_mesure = 0;
}

//dispatcher
void CtrlUltraSonDispatcher( Event_t event ) 
{
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_100MS ))
	{
		//si on souhaite une mesure
		if ( want_mesure == TRUE )
		{
			if ( send_pulse == FALSE )
			{
				CtrlUltraSonSendPulse();
				send_pulse = TRUE;
			}
			else
			{
				//sei();
				CtrlUltraSonReadSensorMesure();	
				//cli();
				want_mesure = FALSE;
				send_pulse = FALSE;	
			}					
		}
	}
}

//on lance la mesure 
void CtrlUltraSonLaunchMesure( void ) 
{
	want_mesure = TRUE;
}

//retourne la mesure 
Int16U CtrlUltraSonReadMesure( void ) 
{
	return us_mesure;
}


/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//permet de lire la valeur mesuré en cm par le dernier pulse envoyé
static void CtrlUltraSonReadSensorMesure( void ) 
{
	us_mesure = DrvI2CUltraSonRead(SRF08_SLAVE_ADDRESS,2) << 8;					
	us_mesure += DrvI2CUltraSonRead(SRF08_SLAVE_ADDRESS,3);
}

//permet d'envoyé un pulse 
static void CtrlUltraSonSendPulse( void ) 
{
	DrvI2CUltraSonTransmit(SRF08_SLAVE_ADDRESS, 0x00, 0x51);
}	