/*
 * uart_protocole.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "Tools/tools_string.h"

#include "ctrl_uart_protocole.h"
#include "ctrl_camera.h"
#include "ctrl_ultrason.h"
#include "ctrl_microphone.h"
#include "ctrl_eye.h"
#include "ctrl_light.h"

#include "Drv/drv_adc.h"
#include "Drv/drv_uart.h"
#include "Drv/drv_led.h"

#include "stdio.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

////////////////////////////////////////PRIVATE PROTOCOLE/////////////////////////////////////////


Int8U i_message_from_body[ 50U ];
Int8U i_message_len_from_body = 0;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

 
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//init
void CtrlUartProtocole( void )
{
}

//dispatcher
void CtrlUartProtocoleDispatcher( Event_t event )
{			
	//si on a un message valide
	if ( DrvEventTestEvent(event ,CONF_EVENT_UART_MSG_RCV ))
	{	
		//on lit le message
		DrvUart0ReadMessage( i_message_from_body, &i_message_len_from_body );
		//on test si on prend des infos
		if( i_message_len_from_body > 0U )
		{
			if( ( Int8U ) i_message_from_body[ 2U ] == E_PROTOCOLE_WHO_EYES )
			{						
				if( ( Int8U ) i_message_from_body[ 3U ] == E_PROTOCOLE_CMD_LEFT_EYE_TOGGLE)
				{
					CtrlEyeToggle( LEFT )	;
				}
				else if( ( Int8U ) i_message_from_body[ 3U ] == E_PROTOCOLE_CMD_RIGHT_EYE_TOGGLE )
				{
					CtrlEyeToggle( RIGHT )	;
				}
				else if( ( Int8U ) i_message_from_body[ 3U ] == E_PROTOCOLE_CMD_EYES_ON )
				{
					CtrlEyeState( LEFT, STATE_LED_ON )	;
					CtrlEyeState( RIGHT, STATE_LED_ON )	;
				}
				else if( ( Int8U ) i_message_from_body[ 3U ] == E_PROTOCOLE_CMD_EYES_OFF )
				{
					CtrlEyeState( LEFT, STATE_LED_OFF )	;
					CtrlEyeState( RIGHT, STATE_LED_OFF );
				}
				else if( ( Int8U ) i_message_from_body[ 3U ] == E_PROTOCOLE_CMD_EYES_TOGGLE )
				{
					CtrlEyeToggle( LEFT );
					CtrlEyeToggle( RIGHT );
				}
				else if( ( Int8U ) i_message_from_body[ 3U ] == E_PROTOCOLE_CMD_EYES_HEARBEAT )
				{
					Boolean enable = ( Boolean ) i_message_from_body[ 4U ]; 
					CtrlEyeHeartBeat(enable);
				}
				else if( ( Int8U ) i_message_from_body[ 3U ] == E_PROTOCOLE_CMD_EYES_STATE )
				{
					CtrlEyeSendUartStateEyes();
				}
			}	
			else if( ( Int8U ) i_message_from_body[ 2U ] == E_PROTOCOLE_WHO_LIGHT )
			{
				CtrlLightSendUartLightMesure();
			}	
			else if( ( Int8U ) i_message_from_body[ 2U ] == E_PROTOCOLE_WHO_US )
			{
				CtrlUltraSendUartProximity();
			}	
		}		
	}		
}	

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

//fonction de de decodage de trame de type ASCII
Boolean CtrlUartProtocoleValidAscii( Char *trame , Int8U payload_size )
{
	Boolean o_success = TRUE;
	Char caract_temp;
	//on boucle sur la trame
	for( Int8U loop = 1U; loop <= payload_size - 2U; loop++ )
	{
		if (
			( TlsStringConvertAsciiToByte( trame[ loop ], &caract_temp ) ) || 
			( ( trame[ loop ] == '*' ) || ( trame[ loop ] == '#' ) )
		   )
		{
			if( !( ( trame[ loop ] == '*' ) || ( trame[ loop ] == '#' ) ) )
			{
				trame[ loop ] = caract_temp ;				
			}
		}
		else
		{
			return FALSE ;	
		}
	}
	return o_success;
}
/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
	
