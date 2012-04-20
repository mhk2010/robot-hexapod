/*
 * ctrl_boussole.c
 *
 * Created: 18/11/2011 16:21:44
 *  Author: berryer
 */ 

#include "ctrl_boussole.h"

#define CMPS03_SLAVE_ADDRESS	0xC0	//addresse du module SRF08


/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//permet de lire la valeur mesuré en cm par le dernier pulse envoyé
Int16U CtrlBoussoleReadSensorMesure( void ) ;


/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Ecardinaux angle_mesure = E_CARD_NONE;
static Ecardinaux consigne_angle_cardinal = E_CARD_NONE;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlBoussole( void ) 
{
	DrvI2CBoussole();
}
//dispatcher
void CtrlBoussoleDispatcher( Event_t event ) 
{
	if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_100MS ))
	{
		CtrlBoussoleReadSensorMesure();
		if( ( consigne_angle_cardinal != E_CARD_NONE ) && ( angle_mesure == consigne_angle_cardinal ) )
		{
			DrvEventAddEvent( CONF_EVENT_BOUSSOLE_SENSOR );
		}
	}
}

//consigne de direction
void CtrlBoussoleSetConsigne( Ecardinaux angle ) 
{
	consigne_angle_cardinal = angle;
}

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//permet de lire la valeur mesuré en ° 
Int16U CtrlBoussoleReadSensorMesure( void ) 
{
	static Int16U angle = 0;
	angle = DrvI2CBoussoleRead(CMPS03_SLAVE_ADDRESS , 2) << 8;					
	angle += DrvI2CBoussoleRead(CMPS03_SLAVE_ADDRESS , 3);
	angle /= 10;
	
	if( ( ( angle >= 347 ) && ( angle <= 360 ) ) || ( ( angle < 22 ) && ( angle >= 0 ) ) )
	{
		angle_mesure = E_CARD_NORD ;
	}
	else if( ( angle >= 22 ) && ( angle <= 67 ) )
	{
		angle_mesure = E_CARD_NORD_EST ;
	}
	else if( ( angle >= 67 ) && ( angle <= 112 ) )
	{
		angle_mesure = E_CARD_EST ;
	}
	else if( ( angle >= 112 ) && ( angle <= 157 ) )
	{
		angle_mesure = E_CARD_SUD_EST ;
	}
	else if( ( angle >= 157 ) && ( angle <= 202 ) )
	{
		angle_mesure = E_CARD_SUD ;
	}
	else if( ( angle >= 202 ) && ( angle <= 247 ) )
	{
		angle_mesure = E_CARD_SUD_OUEST ;
	}
	else if( ( angle >= 247 ) && ( angle <= 292 ) )
	{
		angle_mesure = E_CARD_OUEST ;
	}
	else if( ( angle >= 292 ) && ( angle <= 347 ) )
	{
		angle_mesure = E_CARD_NORD_OUEST ;
	}
	else
	{
		angle_mesure = E_CARD_NONE;
	}
	return angle_mesure;
}
