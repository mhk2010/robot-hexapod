/*
 * drv_servo.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_servo.h"
#include "drv_uart.h"

#define ConvertAngleToTick(angle) (((190U * angle) / 18U  + MIN_PULSE_WIDTH) * 2U)
#define ConvertTickToAngle(tick)  ((tick - 800U ) / 21U)

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static volatile Int8S pin_servo = -1;
static volatile Int8U nb_servo_active = 0U;

static volatile servo_t MesServos[ CONF_SERVO_NB ];

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv servo 
void DrvServo( void )
{
	//on init le timer 1 tick = 1us
	TCCR1A	= 0;             
    TCCR1B	|= _BV(CS11);     
    TCNT1	= 0;               
    TIFR1	|= _BV(OCF1A);     
    TIMSK1	|= _BV(OCIE1A) ;
}

// Ajout d'un Drv Servo 
void DrvAddServo( EIoPin pin , Int16U angle) 
{
	MesServos[ nb_servo_active ].active			= TRUE;
	MesServos[ nb_servo_active ].moving			= FALSE;
	MesServos[ nb_servo_active ].pin			= pin;
	MesServos[ nb_servo_active ].ticks			= ConvertAngleToTick(angle);
	MesServos[ nb_servo_active ].ticks_consigne = MesServos[ nb_servo_active ].ticks;
	MesServos[ nb_servo_active ].vitesse		= E_SERVO_VITESSE_0;
	
	micIoPortsConfigureOutput( pin );
	nb_servo_active++;
}

// Ajout d'un Drv Servo 
void DrvDeleteServo( EIoPin pin ) 
{
	Int8U remove_index_servo = 0xFF;
	
	for(Int8U loop_servo = 0U ; loop_servo < nb_servo_active ; loop_servo++)
	{
		if(MesServos[ nb_servo_active ].pin == pin)
		{
			remove_index_servo = loop_servo;
		}
		if( loop_servo >= remove_index_servo ) 
		{
			MesServos[ loop_servo ] = MesServos[ loop_servo + 1 ];
		}
		if( loop_servo == (nb_servo_active - 1U) ) 
		{
			nb_servo_active--;
		}
	}
}


// bouge le servo a la position voulu en angle
Boolean DrvServoMoveToPosition( Int8U index, Int16U angle, EServoVitesse vitesse)
{
	Boolean ret = FALSE; 
	
	if(MesServos[ index ].moving != TRUE)
	{
		ret = DrvServoDirectMoveToPosition(index, angle, vitesse);
	}
	return ret;
}


// bouge le servo a la position voulu en angle sans savoir si il été deja en mouvement
Boolean DrvServoDirectMoveToPosition( Int8U index, Int16U angle, EServoVitesse vitesse)
{
	Boolean ret = FALSE; 
	
	//consigne
	MesServos[ index ].ticks_consigne = ConvertAngleToTick(angle);
	if( MesServos[ index ].ticks_consigne != MesServos[index].ticks )
	{
		MesServos[ index ].vitesse	= vitesse;
		MesServos[ index ].moving	= TRUE;		
		//calcul de la vitesse d'incrementation pour atteindre la consigne
		if( MesServos[index].ticks < MesServos[index].ticks_consigne )
		{
			MesServos[index].increment = ( MesServos[index].ticks_consigne - MesServos[index].ticks ) / (1+ MesServos[ index ].vitesse);
		}
		else
		{
			MesServos[index].increment = ( MesServos[index].ticks - MesServos[index].ticks_consigne ) / (1+ MesServos[ index ].vitesse);
		}
			
		//si le calcul renvoit 0 on le met a 1
		if(MesServos[index].increment == 0U)
		{
			MesServos[index].increment = 1U;
		}
	}
	else
	{
		ret = TRUE;
	}
	return ret;
}

// si le servo a une consigne ne cours
Boolean DrvServoMoving( Int8U index ) 
{
	return MesServos[ index ].moving;
}

// donne la position du servo en angle
Int16U DrvServoGetPosition( Int8U index ) 
{
	return ConvertTickToAngle(MesServos[ index ].ticks);
}	


// envoie la position de tout les servo sur l'UART
void DrvServoSendUartPosition( void ) 
{
	Int8U o_message[ 19U ];
		
	//on envoie la position des servos
	o_message[ 0U ] = '*';
	o_message[ 1U ] = 1;
	o_message[ 2U ] = 0;
	for(Int8U loop_servo = 0U ; loop_servo < nb_servo_active ; loop_servo++)
	{
		o_message[ 3U + loop_servo ] = ConvertTickToAngle( MesServos[ loop_servo ].ticks_consigne );
	}		
	o_message[ 3U + nb_servo_active ] = '#';
	o_message[ 4U + nb_servo_active ] = '#';
	DrvUart1SendMessage( o_message, 19U );		
	
}


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


///////////////////////////////////////////ISR FUNCTIONS//////////////////////////////////////////
SIGNAL (TIMER1_COMPA_vect) 
{ 
	if(pin_servo < 0)
	{
		TCNT1 = 0U;
	}
	else
	{
		if( ( MesServos[pin_servo].active == TRUE ) && ( pin_servo < nb_servo_active ) )
		{
			micIoPortsConfigureToLowLevel(MesServos[pin_servo].pin);
		}
	}
		
	pin_servo++;
	if(pin_servo < nb_servo_active)
	{
		OCR1A = TCNT1 + MesServos[pin_servo].ticks ;
		if( ( MesServos[pin_servo].active == TRUE ) && ( pin_servo < nb_servo_active ) )
		{
			micIoPortsConfigureToHighLevel(MesServos[pin_servo].pin);
			//servo en mouvement
			if( MesServos[pin_servo].moving == TRUE )
			{
				//on souhaite atteindre la consigne
				if( MesServos[pin_servo].ticks < MesServos[pin_servo].ticks_consigne )
				{
					//on applique la nouvelle consigne				
					MesServos[pin_servo].ticks += MesServos[pin_servo].increment;

					//si on est en ovf on reajuste				
					if( MesServos[pin_servo].ticks >= MesServos[pin_servo].ticks_consigne )
					{
						MesServos[pin_servo].ticks = MesServos[pin_servo].ticks_consigne;
						MesServos[pin_servo].moving = FALSE;
					}						
				}
				else
				{
					//on applique la nouvelle consigne				
					MesServos[pin_servo].ticks -= MesServos[pin_servo].increment;
					
					//si on est en ovf on reajuste	
					if( MesServos[pin_servo].ticks <= MesServos[pin_servo].ticks_consigne )
					{
						MesServos[pin_servo].ticks = MesServos[pin_servo].ticks_consigne;
						MesServos[pin_servo].moving = FALSE;
					}
				}
			}
		}
	}
	else
	{
		if( TCNT1 <  (unsigned int)(REFRESH_INTERVAL + OFFSET_TIMER) )
		{
			OCR1A = (unsigned int)REFRESH_INTERVAL;  
		}
		else
		{
			OCR1A = TCNT1 + OFFSET_TIMER;
		}
		pin_servo = -1;
	}				
}