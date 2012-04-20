/*
 * uart_protocole.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "Tools/tools_string.h"

#include "ctrl_uart_protocole.h"
#include "ctrl_patte.h"
#include "ctrl_tete.h"
#include "ctrl_marche.h"

#include "Drv/drv_servo.h"
#include "Drv/drv_led.h"
#include "Drv/drv_uart.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

////////////////////////////////////////PRIVATE PROTOCOLE/////////////////////////////////////////
Int8U i_message_from_digi[ 50U ];
Int8U i_message_len_from_digi = 0;

Int8U i_message_from_head[ 50U ];
Int8U i_message_len_from_head = 0;

//mesure de l'ultrason
Int16U ultrason_mesure = 0U;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

static void CtrlUartProtocoleHeadUs( void ) ;
static void CtrlUartProtocoleHeadLight( void ) ;

static void CtrlUartProtocoleBodyServo( void ) ;
static void CtrlUartProtocoleBodyMarche( void ) ;
static void CtrlUartProtocoleBodyHead( void ) ;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlUartProtocole( void )
{
}

//dispatcher
void CtrlUartProtocoleDispatcher( Event_t event )
{	
	//si on a recu un message provenant de la tete
	if ( DrvEventTestEvent(event ,CONF_EVENT_HEAD_MSG_RCV ))
	{
		//on allume la led pendant le traitement
		DrvLedOn(CONF_LED_RX_HEAD);
		//on lit le message
		DrvUart0ReadMessage( i_message_from_head, &i_message_len_from_head );
		//on envoie direct le message sur le wifi
		DrvUart1SendMessage( i_message_from_head, i_message_len_from_head );
		//on test si on prend des infos
		if( i_message_len_from_head > 0U )
		{
			//message ultrason
			//----------------
			if( i_message_from_head[ 2 ] == 0U )
			{
				CtrlUartProtocoleHeadUs();
			}	
			//message ambiant light
			//---------------------
			else if( i_message_from_head[ 2 ] == 2U )
			{
				
			}		
		}
		//on eteinds la led apres le traitement
		DrvLedOff(CONF_LED_RX_HEAD);
	}	
	
	//si on a recu un message provenant du wifi
	if ( DrvEventTestEvent(event ,CONF_EVENT_DIGI_MSG_RCV ))
	{
		//on allume la led pendant le traitement
		DrvLedOn(CONF_LED_RX_DIGI);
		//on lit le message provenant du wifi
		DrvUart1ReadMessage( i_message_from_digi, &i_message_len_from_digi );
		//on test si on prend des infos
		if( i_message_len_from_digi > 0U )
		{
			//si le message nous concerne
			//---------------------------
			if( i_message_from_digi[ 1U ] == 1U )
			{
				//on dispatch selon les controls
				
				//servos				 
				if( i_message_from_digi[ 2U ] == 0U )
				{
					CtrlUartProtocoleBodyServo();		
				}
							
				//controle des fonctions de la tete
				else if( i_message_from_digi[ 2U ] == 1U )
				{
					CtrlUartProtocoleBodyHead();
				}
				
				//marche			 
				else if( i_message_from_digi[ 2U ] == 2U )
				{
					CtrlUartProtocoleBodyMarche();	
				}	
				
			}	
			//si le message nous concerne pas
			//-------------------------------
			else
			{
				//on l'envoie a la tete
				DrvUart0SendMessage( i_message_from_digi, i_message_len_from_digi );
			}			
		}
		//on eteinds la led apres le traitement
		DrvLedOff(CONF_LED_RX_DIGI);			
	}	
}	

//on lit la mesure US
Int16U CtrlUartProtocoleReadHeadUs( void ) 
{
	return ultrason_mesure;
}	

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CtrlUartProtocoleBodyServo( void ) 
{
	EServoVitesse vit;
	//on cherche la vitesse
	if( i_message_from_digi[ 5U ] == 0U )
	{
		vit = E_SERVO_VITESSE_0;
	}
	else if( i_message_from_digi[ 5U ] == 1U )
	{
		vit = E_SERVO_VITESSE_1;
	}
	else if( i_message_from_digi[ 5U ] == 2U )
	{
		vit = E_SERVO_VITESSE_2;
	}
	else if( i_message_from_digi[ 5U ] == 3U )
	{
		vit = E_SERVO_VITESSE_3;
	}
	else if( i_message_from_digi[ 5U ] == 4U )
	{
		vit = E_SERVO_VITESSE_4;
	}
	else 
	{
		vit = E_SERVO_VITESSE_5;
	}
					
	//on cherche le servo
	if( i_message_from_digi[ 3U ] == 0U )
	{
		DrvServoMoveToPosition( CONF_SERVO_TETE_H_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 1U )
	{
		DrvServoMoveToPosition( CONF_SERVO_TETE_V_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 2U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 3U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 4U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE_INDEX, i_message_from_digi[ 4U ], vit);	
	}	
	else if( i_message_from_digi[ 3U ] == 5U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 6U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE_INDEX, i_message_from_digi[ 4U ], vit);	
	}	
	else if( i_message_from_digi[ 3U ] == 7U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 8U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_AVANT_DROITE_EPAULE_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 9U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_AVANT_DROITE_COUDE_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 10U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE_INDEX, i_message_from_digi[ 4U ], vit);	
	}	
	else if( i_message_from_digi[ 3U ] == 11U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_MILIEU_DROITE_COUDE_INDEX, i_message_from_digi[ 4U ], vit);	
	}
	else if( i_message_from_digi[ 3U ] == 12U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE_INDEX, i_message_from_digi[ 4U ], vit);	
	}	
	else if( i_message_from_digi[ 3U ] == 13U )
	{
		DrvServoMoveToPosition( CONF_SERVO_PATTE_ARRIERE_DROITE_COUDE_INDEX, i_message_from_digi[ 4U ], vit);	
	}
}

static void CtrlUartProtocoleBodyMarche( void ) 
{
	EServoVitesse vit;
	//on cherche la vitesse
	if( i_message_from_digi[ 4U ] == 0U )
	{
		vit = E_SERVO_VITESSE_0;
	}
	else if( i_message_from_digi[ 4U ] == 1U )
	{
		vit = E_SERVO_VITESSE_1;
	}
	else if( i_message_from_digi[ 4U ] == 2U )
	{
		vit = E_SERVO_VITESSE_2;
	}
	else if( i_message_from_digi[ 4U ] == 3U )
	{
		vit = E_SERVO_VITESSE_3;
	}
	else if( i_message_from_digi[ 4U ] == 4U )
	{
		vit = E_SERVO_VITESSE_4;
	}
	else 
	{
		vit = E_SERVO_VITESSE_5;
	}
					
	//on cherche la marche a suivre
	CtrlMarcheMove(i_message_from_digi[ 3U ], vit);	
}

static void CtrlUartProtocoleBodyHead( void ) 
{
	//on lance un scan
	if( i_message_from_digi[ 3U ] == 0U )
	{
		CtrlTeteStartScan();
	}
}

static void CtrlUartProtocoleHeadLight( void ) 
{
	Int16U left_light_mesure = 0U;
	Int16U right_light_mesure = 0U;
	left_light_mesure = (Int16U)((Int16U)(i_message_from_head[ 3U ] >> 8U )| i_message_from_head[ 4U ]);
	right_light_mesure = (Int16U)((Int16U)(i_message_from_head[ 5U ] >> 8U )| i_message_from_head[ 6U ]);
	//on lance un event selon l'ecart entre les deux LDR
	if( right_light_mesure < left_light_mesure )
	{
		if(( left_light_mesure - right_light_mesure ) > 200U)
		{
			//on lance l'event
			DrvEventAddEvent( CONF_EVENT_ALERT_LIGHT );
		}
	}
	else 
	{
		if(( right_light_mesure - left_light_mesure ) > 200U)
		{
			//on lance l'event
			DrvEventAddEvent( CONF_EVENT_ALERT_LIGHT );
		}
	}
}

//valeur mesurer par l'us
void CtrlUartProtocoleSendReadHeadUs( void ) 
{
	Int8U message[ 5U ] = {'*',0,0,'#','#'};
	//on l'envoie a la tete
	DrvUart0SendMessage( message, 5U );
}

static void CtrlUartProtocoleHeadUs( void ) 
{
	ultrason_mesure = (Int16U)((Int16U)(i_message_from_head[ 3U ] >> 8U )| i_message_from_head[ 4U ]);
	//on lance l'event
	DrvEventAddEvent( CONF_EVENT_ALERT_US_PROX );
}