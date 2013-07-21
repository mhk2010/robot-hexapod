/*
 * ctrl_eye.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_eye.h"
#include "ctrl_ultrason.h"

#include "Drv/drv_led.h"
#include "Drv/drv_uart.h"

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
		if(hearbeat_enable == TRUE)
		{
			CtrlEyeHeartBeat(hearbeat_enable);
		}
	}
	if ( DrvEventTestEvent( event, CONF_EVENT_US_ALARM_PROX ))
	{
		CtrlEyeBlinkSpeed( 5 ,CtrlUltraSonReadMesure());
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
	DrvLedDirectFlash(CONF_INDEX_EYE_LEFT, 2 ,5,10);
	DrvLedDirectFlash(CONF_INDEX_EYE_RIGHT, 2 ,5,10);
	hearbeat_enable = enable;
}

// return the led state
void CtrlEyeGetState ( ELedState *left_eye_state, ELedState *right_eye_state)
{
	*left_eye_state = DrvLedGetState(CONF_INDEX_EYE_LEFT);
	*right_eye_state = DrvLedGetState(CONF_INDEX_EYE_RIGHT);
}

//permet d'envoyer sur l'uart 
void CtrlEyeSendUartStateEyes( void ) 
{
	ELedState left_eye_state = STATE_LED_OFF, right_eye_state = STATE_LED_OFF;
	CtrlEyeGetState ( &left_eye_state, &right_eye_state);
	Char buffer[8U];
	
	buffer[0U] = '*';
	buffer[1U] = E_PROTOCOLE_HEAD;
	buffer[2U] = E_PROTOCOLE_WHO_EYES;
	buffer[3U] = E_PROTOCOLE_CMD_EYES_STATE;
	buffer[4U] = left_eye_state;
	buffer[5U] = right_eye_state;
	buffer[6U] = '#';
	buffer[7U] = '#';
	DrvUartDirectSendBytes(CONF_UART_0_INDEX,(Int8U*)buffer,8U);
}
