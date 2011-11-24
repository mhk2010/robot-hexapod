/*
 * ctrl_accel.c
 *
 * Created: 16/11/2011 12:06:58
 *  Author: berryer
 */ 


#include "ctrl_accel.h"
////////////////////////////////////////////PRIVATE ENUMS//////////////////////////////////////////


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CtrlAccelEndAdcConvertion( EIoPin pin_name ,Int16U adc_data );

/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
Int8U step_adc_convertion = 0;
Boolean is_qualibre = FALSE;

Int8U nb_convertion_x = 0;
Int16U moy_x = 0;
Int16U accel_X[ 10 ];

Int8U nb_convertion_y = 0;
Int16U moy_y = 0;
Int16U accel_Y[ 10 ];

Int8U nb_convertion_z = 0;
Int16U moy_z = 0;
Int16U accel_Z[ 10 ];

Int8U timeout_adc = 0;
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlAccel( void ) 
{
	DrvAdcEnableAdc( CONF_ADC_ACCEL_X );
	DrvAdcEnableAdc( CONF_ADC_ACCEL_Y );
	DrvAdcEnableAdc( CONF_ADC_ACCEL_Z );
}

//dispatcher
void CtrlAccelDispatcher( Event_t event ) 
{
	if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_100MS ))
	{
		if(timeout_adc >= 100)
		{
			if( step_adc_convertion == 0 )
			{
				DrvAdcStartConvertion( CONF_ADC_ACCEL_X , CtrlAccelEndAdcConvertion );
			}
			else if( step_adc_convertion == 1)
			{
				DrvAdcStartConvertion( CONF_ADC_ACCEL_Y , CtrlAccelEndAdcConvertion );
			}
			else if( step_adc_convertion == 2 )
			{
				DrvAdcStartConvertion( CONF_ADC_ACCEL_Z , CtrlAccelEndAdcConvertion );
			}
			timeout_adc =0;
		}
		else
		{
			timeout_adc++;
		}
		
	}
}


void CtrlAccelQualibration( void ) 
{
	moy_x = ( accel_X[ 0 ] + accel_X[ 1 ] + accel_X[ 2 ] + accel_X[ 3 ] + accel_X[ 4 ] + accel_X[ 5 ] + accel_X[ 6 ] + accel_X[ 7 ] + accel_X[ 8 ] + accel_X[ 9 ] ) / 10;
	moy_y = ( accel_Y[ 0 ] + accel_Y[ 1 ] + accel_Y[ 2 ] + accel_Y[ 3 ] + accel_Y[ 4 ] + accel_Y[ 5 ] + accel_Y[ 6 ] + accel_Y[ 7 ] + accel_Y[ 8 ] + accel_Y[ 9 ] ) / 10; 
	moy_z = ( accel_Z[ 0 ] + accel_Z[ 1 ] + accel_Z[ 2 ] + accel_Z[ 3 ] + accel_Z[ 4 ] + accel_Z[ 5 ] + accel_Z[ 6 ] + accel_Z[ 7 ] + accel_Z[ 8 ] + accel_Z[ 9 ] ) / 10; 
	is_qualibre = TRUE;
}	


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CtrlAccelEndAdcConvertion( EIoPin pin_name ,Int16U adc_data )
{
	if( pin_name == CONF_ADC_ACCEL_X )
	{
		accel_X[ nb_convertion_x ] = adc_data;
		if(nb_convertion_x < 9)
		{
			nb_convertion_x++;
		}
		else
		{
			nb_convertion_x = 0;
		}
		if( is_qualibre == TRUE)
		{
			
		}
	}
	else if( pin_name == CONF_ADC_ACCEL_Y )
	{
		accel_Y[ nb_convertion_y ] = adc_data;
		if(nb_convertion_y < 9)
		{
			nb_convertion_y++;
		}
		else
		{
			nb_convertion_y = 0;
		}
		if( is_qualibre == TRUE)
		{
			
		}
	}
	else if( pin_name == CONF_ADC_ACCEL_Z )
	{
		accel_Z[ nb_convertion_z ] = adc_data;
		if(nb_convertion_z < 9)
		{
			nb_convertion_z++;
		}
		else
		{
			nb_convertion_z = 0;
		}
		if( is_qualibre == TRUE)
		{
			
		}
	}
	
	if( step_adc_convertion < 2 )
	{
		step_adc_convertion++;
	}
	else
	{
		step_adc_convertion = 0;
		CtrlAccelQualibration();
	}
	
	
	if( adc_data < SECURITY_PERIMETER )
	{
		DrvEventAddEvent( CONF_EVENT_ACCEL );	
	}
}