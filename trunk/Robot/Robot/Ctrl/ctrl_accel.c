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

Int8U nb_convertion = 0;
Int16U moy_x = 0;
Int16U accel_X[ 10 ];

Int16U moy_y = 0;
Int16U accel_Y[ 10 ];

Int16U moy_z = 0;
Int16U accel_Z[ 10 ];

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
		if( step_adc_convertion == 0 )
		{
			accel_X[ nb_convertion ] = DrvAdcReadChannel( CONF_ADC_ACCEL_X ) ;
		}
		else if( step_adc_convertion == 1)
		{
			accel_Y[ nb_convertion ] = DrvAdcReadChannel( CONF_ADC_ACCEL_Y );
		}
		else if( step_adc_convertion == 2 )
		{
			accel_Z[ nb_convertion ] = DrvAdcReadChannel( CONF_ADC_ACCEL_Z );
			if(++nb_convertion == 9)
			{
				nb_convertion = 0;
			}
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
