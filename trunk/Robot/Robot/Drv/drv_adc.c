/*
 * drv_adc.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_adc.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//structure adc
typedef struct SSAdc
{
	EIoPin pin_name;
	EAdcChannelSelection channel;
	ptrfct_Isr_Callback_Adc ptrfct;
}SAdc;

//configuration initial des uarts
SAdc MesAdc[ CONF_ADC_NB ] ;

Int8U nb_use_adc = 0 ;

volatile Boolean use_adc = FALSE ;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static Int8U DrvAdcPinConvertToIndex( EIoPin pin_name );
static Int8U DrvAdcChannelConvertToIndex( EAdcChannelSelection channel );

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Adc 
void DrvAdc( void )
{		
	micAdcSetInterrupt();
	micAdcSetAdcEnable();
}

//active l'adc
void DrvAdcEnableAdc( EIoPin pin_name )
{
	micIoPortsConfigureInput( pin_name , PORT_NO_PULL_UP );
	MesAdc[nb_use_adc].pin_name = pin_name ;
	MesAdc[nb_use_adc].channel = pin_name ;
	nb_use_adc++;
}

//desactive l'adc
void DrvAdcDisableAdc( EIoPin pin_name )
{
	MesAdc[nb_use_adc].pin_name = 0xFF ;
	nb_use_adc--;
}

//Commence la convertion sur l'adc
Boolean DrvAdcStartConvertion( EIoPin pin_name , ptrfct_Isr_Callback_Adc ptrfct)
{
	Boolean o_success = FALSE;
	if( use_adc == FALSE )
	{
		use_adc = TRUE ;
		Int8U index_adc = DrvAdcPinConvertToIndex( pin_name );
		micAdcSetAnalogChannelandGainSelectionBits( MesAdc[index_adc].channel );
		micAdcSetStartConversion();	
		MesAdc[index_adc].ptrfct = ptrfct ;
		o_success = TRUE;
	}
	
	
	return o_success;
}





////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static Int8U DrvAdcPinConvertToIndex( EIoPin pin_name )
{
	Int8U find_index = 0;
	for(Int8U loop_config = 0; loop_config < nb_use_adc ; loop_config++ )
	{
		if( pin_name == MesAdc[loop_config].pin_name )
		{
			find_index = loop_config;
		}
	}	
	return find_index;
}

static Int8U DrvAdcChannelConvertToIndex( EAdcChannelSelection channel )
{
	for(Int8U loop_config = 0; loop_config < nb_use_adc ; loop_config++ )
	{
		if( channel == MesAdc[loop_config].channel )
		{
			return loop_config;
		}
	}	
	return 0xff;
}

/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//ISR adc complete
ISR(ADC_vect)
{
	use_adc = FALSE ;
	Int8U index_adc = DrvAdcChannelConvertToIndex( micAdcGetAnalogChannelandGainSelectionBits() );
	if( MesAdc[index_adc].ptrfct != NULL )
	{
		MesAdc[index_adc].ptrfct( MesAdc[index_adc].pin_name ,micAdcReadData16() );
	}		
}