/*
 * uart_protocole.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "Tools/tools_string.h"

#include "ctrl_uart_protocole.h"

#include "Drv/drv_servo.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

////////////////////////////////////////PRIVATE PROTOCOLE/////////////////////////////////////////


#define E_PROTOCOLE_NB_PARAMETERS		5U

//structure de config des Uarts
typedef enum EEProtocoleAsciiState
{
	E_PROTOCOLE_ASCII_START,
	E_PROTOCOLE_ASCII_PAYLOAD,
	E_PROTOCOLE_ASCII_STOP,
	//---------------
	E_PROTOCOLE_ASCII_NB,
}EProtocoleAsciiState;


//structure protocole
typedef struct SSAsciiProtocole
{
	EProtocoleAsciiState state;
	Char payload[ NB_BYTES_SEND_MAX ];
	Int8U index_payload;
	Int8U index_end_payload;
	Int16U parameters[ E_PROTOCOLE_NB_PARAMETERS ];
}SAsciiProtocole;

//configuration initial des uarts
SAsciiProtocole AsciiProtocole;



////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
// ISR reception UART
void CtrlUartProtocoleReceipt_ISR( Int8U received_byte ) ;

//fonction de de decodage de trame de type ASCII
Boolean CtrlUartProtocoleValidAscii( Char trame [ NB_BYTES_SEND_MAX ] , Int8U index_fin_payload ) ;

// fonction de reception de trame si le type ASCII est activé
void CtrlUartProtocoleAsciiReceipt( Int8U received_byte ) ;
 
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlUartProtocole( void )
{
	//on init le driver utilisé
	DrvUart();
	DrvUartSetPtrfctReceiveComplete( CONF_UART_0_INDEX, CtrlUartProtocoleReceipt_ISR );
}

//dispatcher
void CtrlUartProtocoleDispatcher( Event_t event )
{
	if ( DrvEventTestEvent(event ,CONF_EVENT_UART_MSG_RCV ))
	{
		//on decode la trame
		CtrlUartProtocoleValidAscii( AsciiProtocole.payload , AsciiProtocole.index_end_payload );
		//on se tiens pres a recevoir une nouvelle trame
		AsciiProtocole.state = E_PROTOCOLE_ASCII_START;	
		AsciiProtocole.index_payload = 0;
		
		//on efface les anciens parametres
		for( Int8U loop = 0; loop < E_PROTOCOLE_NB_PARAMETERS ; loop++ )
		{
			AsciiProtocole.parameters[ loop ] = 0;
		}		
		
		//on decode les parametres de la trame
		Int8U start_index = 1U;
		Int8U index_parameter = 0;
		for( Int8U loop = start_index; loop <= AsciiProtocole.index_end_payload - 1U ; loop++ )
		{
			if ( ( AsciiProtocole.payload[ loop ] == '*' ) || ( loop == AsciiProtocole.index_end_payload - 1U ) )
			{
				//on a decouvert un parametres
				Int16U mult = 1;
				for( Int8U sub_loop = loop - 1; sub_loop >= start_index; sub_loop-- )
				{
					AsciiProtocole.parameters[ index_parameter ] += AsciiProtocole.payload[ sub_loop ] * mult;
					mult *= 10;
				}					
				
				//on a fini on garde le nouvel index
				start_index = loop + 1;
				//le prochain est un nouveau parametres
				index_parameter++;
			}
		}			
		if( ( Int8U ) AsciiProtocole.parameters[ 0U ] == E_PROTOCOLE_PARAMETER_SERVO )
		{
			if( ( Int8U ) AsciiProtocole.parameters[ 1U ] == E_PROTOCOLE_PARAMETER_SERVO_POSITION )
			{
				DrvServoIndexMoveToPosition(AsciiProtocole.parameters[ 2U ],AsciiProtocole.parameters[ 3U ]);
			}			
		}		
		else if( ( Int8U ) AsciiProtocole.parameters[ 0U ] == E_PROTOCOLE_PARAMETER_PATTE )
		{
			//CtrlMarcheSequence( );	
		}
	}		
}	

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

//fonction de de decodage de trame de type ASCII
Boolean CtrlUartProtocoleValidAscii( Char *trame , Int8U index_fin_payload )
{
	Boolean o_success = TRUE;
	Char caract_temp;
	//on boucle sur la trame
	for( Int8U loop = 1U; loop <= index_fin_payload - 2U; loop++ )
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

//fonction de reception de trame si le type ASCII est activé
void CtrlUartProtocoleAsciiReceipt( Int8U received_byte )
{
	switch( AsciiProtocole.state )
	{
		case E_PROTOCOLE_ASCII_START:
			{
				if( received_byte == '*' )
				{
					//on passe en payload
					AsciiProtocole.state = E_PROTOCOLE_ASCII_PAYLOAD;	
					AsciiProtocole.index_payload = 0;
					AsciiProtocole.index_end_payload = 0;
					
					AsciiProtocole.payload[AsciiProtocole.index_payload] = '*';
					AsciiProtocole.index_payload++;
						
				}
			}
		break;	
		case E_PROTOCOLE_ASCII_PAYLOAD:
			{
				if( 
					( AsciiProtocole.payload[AsciiProtocole.index_payload - 1] == '#' ) &&
					( received_byte == '#' )
				  )
				{
					AsciiProtocole.index_end_payload = AsciiProtocole.index_payload ;
					//on passe en fin de trame
					AsciiProtocole.state = E_PROTOCOLE_ASCII_STOP;	
					//on envoie l'event
					DrvEventAddEvent( CONF_EVENT_UART_MSG_RCV );	
				}
				//on ajoute le caractrere
				AsciiProtocole.payload[AsciiProtocole.index_payload] = received_byte;
				AsciiProtocole.index_payload++;			
				
				
			}
		break;		
		case E_PROTOCOLE_ASCII_STOP:
			{
				if( received_byte == '*' )
				{
					//on passe en payload
					AsciiProtocole.state = E_PROTOCOLE_ASCII_PAYLOAD;	
					AsciiProtocole.index_payload = 0;
					AsciiProtocole.index_end_payload = 0;
					
					AsciiProtocole.payload[AsciiProtocole.index_payload] = '*';
					AsciiProtocole.index_payload++;
				}
			}
		break;	
		default:
			{
				//on doit jamais arrivé ici
				AsciiProtocole.state = E_PROTOCOLE_ASCII_START;		
			}
		break;	
	}
}		




/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//ISR reception UART
void CtrlUartProtocoleReceipt_ISR( Int8U received_byte )
{
	CtrlUartProtocoleAsciiReceipt( received_byte );		 
}