/*
 * drv_servo.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_servo.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static volatile Int8S pin_servo = -1;
static volatile servo_t MesServos[CONF_SERVO_NB];
static volatile Int8U nb_servo_active = 0;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static long map( long x, long in_min, long in_max, long out_min, long out_max);
static Int8U DrvServoConvertPinToIndex( Int8U index_servo );

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv servo 
void DrvServo( void )
{
	//on init le timer 1 tick = 1us
	TCCR1A	= 0;             
    TCCR1B	= _BV(CS11);     
    TCNT1	= 0;               
    TIFR1	|= _BV(OCF1A);     
    TIMSK1	|= _BV(OCIE1A) ;
}

// Ajout d'un Drv Servo 
void DrvAddServo( EIoPin pin , Int8U angle ) 
{
	MesServos[ nb_servo_active ].active			= TRUE;
	MesServos[ nb_servo_active ].pin			= pin;
	MesServos[ nb_servo_active ].ticks			= map( angle, MIN_ANGLE, MAX_ANGLE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	MesServos[ nb_servo_active ].moving			= FALSE;
	MesServos[ nb_servo_active ].ticks_consigne = map( angle, MIN_ANGLE, MAX_ANGLE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
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
void DrvServoMoveToPosition( EIoPin pin, Int8U angle )
{
	Int8U index_servo = DrvServoConvertPinToIndex(pin);
	if( index_servo != 0xFF )
	{
		MesServos[ index_servo ].moving = TRUE;
		MesServos[ index_servo ].ticks_consigne = map( angle, MIN_ANGLE, MAX_ANGLE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	} 
}

// bouge le servo a la position voulu en angle
void DrvServoIndexMoveToPosition( Int8U index_servo, Int8U angle )
{
	if( index_servo < nb_servo_active )
	{
		MesServos[ index_servo ].moving = TRUE;
		MesServos[ index_servo ].ticks_consigne = map( angle, MIN_ANGLE, MAX_ANGLE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	} 
}

// donne la position du servo en angle
Int8U DrvServoGetPosition( EIoPin pin )
{
	Int8U index_servo = DrvServoConvertPinToIndex(pin);
	if( index_servo != 0xFF )
	{
		return (Int8U)map( MesServos[ index_servo ].ticks_consigne, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, MIN_ANGLE, MAX_ANGLE);
	} 
	return index_servo;
}	


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static long map( long x, long in_min, long in_max, long out_min, long out_max)
{
	long temp = (x - in_min);
	temp *= (out_max - out_min);
	temp /= (in_max - in_min);
	temp += out_min;
	if(temp > out_max)
	{
		temp = out_max ;
	}
	else if(temp < out_min)
	{
		temp = out_min ;		
	}
	
	return temp;
}
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static Int8U DrvServoConvertPinToIndex( Int8U pin )
{
	for(Int8U loop_servo = 0U ; loop_servo < nb_servo_active ; loop_servo++)
	{
		if(MesServos[ loop_servo ].pin == pin)
		{
			return loop_servo;
		}
	}	
	return 0xFF;				
}

///////////////////////////////////////////ISR FUNCTIONS//////////////////////////////////////////
SIGNAL (TIMER1_COMPA_vect) 
{ 
	if(pin_servo < 0)
	{
		TCNT1 = 0;
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
			if( MesServos[pin_servo].moving == TRUE )
			{
				if( MesServos[pin_servo].ticks == MesServos[pin_servo].ticks_consigne )
				{
					MesServos[pin_servo].moving = FALSE;		
				}
				else if( MesServos[pin_servo].ticks > MesServos[pin_servo].ticks_consigne )
				{
					MesServos[pin_servo].ticks--;
				}
				else if( MesServos[pin_servo].ticks < MesServos[pin_servo].ticks_consigne )
				{
					MesServos[pin_servo].ticks++;
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