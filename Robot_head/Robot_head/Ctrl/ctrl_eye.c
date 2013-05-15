/*
 * ctrl_eye.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_eye.h"
#include "ctrl_ultrason.h"

#include "Drv/drv_led.h"

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
#define BLINK_ON_TIME 5U
#define BLINK_OFF_TIME 10U

Boolean hearbeat_enable = FALSE;
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlEye( void ) 
{ 
	//on active les yeux
	DrvLed();
}

void CtrlEyeDispatcher( Event_t event )
{
	if ( DrvEventTestEvent( event, CONF_EVENT_TIMER_1S ))
	{
		if(CtrlUltraSonReadMesure() < SECURITY_PERIMETER)
		{
			CtrlEyeBlinkSpeed( 5 ,CtrlUltraSonReadMesure());
		}
		else
		{
			if(hearbeat_enable == TRUE)
			{
				CtrlEyeHeartBeat(hearbeat_enable);
			}
		}		
	}
}			

//on joue un etat sur l'oeil
void CtrlEyeState( Int8U eye, ELedState state ) 
{
	if(eye == LEFT)
	{
		if (state == STATE_LED_ON)
		{
			DrvLedOn(CONF_INDEX_EYE_LEFT) ;
		}
		else
		{
			DrvLedOff(CONF_INDEX_EYE_LEFT) ;
		}
	}
	else if(eye == RIGHT)
	{
		if (state == STATE_LED_ON)
		{
			DrvLedOn(CONF_INDEX_EYE_RIGHT) ;
		}
		else
		{
			DrvLedOff(CONF_INDEX_EYE_RIGHT) ;
		}
	}
}


//on toggle l'etat sur l'oeil
void CtrlEyeToggle( Int8U eye)
{
	if(eye == LEFT)
	{
		DrvLedToggle(CONF_INDEX_EYE_LEFT);		
	}
	else if(eye == RIGHT)
	{
		DrvLedToggle(CONF_INDEX_EYE_RIGHT);			
	}
}

//on fait clignoter l oeil de gauche
void CtrlEyeLeftBlink( Int8U nb_blink ) 
{ 
	DrvLedFlash(CONF_INDEX_EYE_LEFT, nb_blink, BLINK_ON_TIME, BLINK_OFF_TIME);
}

//on fait clignoter l oeil de droite
void CtrlEyeRightBlink( Int8U nb_blink ) 
{ 
	DrvLedFlash(CONF_INDEX_EYE_RIGHT, nb_blink, BLINK_ON_TIME, BLINK_OFF_TIME);
}

//on fait clignoter les yeux
void CtrlEyeBlink( Int8U nb_blink ) 
{ 
	DrvLedFlash(CONF_INDEX_EYE_LEFT, nb_blink, BLINK_ON_TIME, BLINK_OFF_TIME);
	DrvLedFlash(CONF_INDEX_EYE_RIGHT, nb_blink, BLINK_ON_TIME, BLINK_OFF_TIME);
}

//on fait clignoter les yeux
void CtrlEyeBlinkSpeed( Int8U nb_blink ,Int8U speed ) 
{ 
	DrvLedDirectFlash(CONF_INDEX_EYE_LEFT, nb_blink, (speed / 2U)+1U, (speed / 2U)+1U);
	DrvLedDirectFlash(CONF_INDEX_EYE_RIGHT, nb_blink, (speed / 2U)+1U, (speed / 2U)+1U);
}

//on active ou non le hearbeat sur les leds
void CtrlEyeHeartBeat ( Boolean enable )
{
	DrvLedDirectFlash(CONF_INDEX_EYE_LEFT, 2U,20,100);
	DrvLedDirectFlash(CONF_INDEX_EYE_RIGHT, 2U,20,100);
	hearbeat_enable = enable;
}
