/*
 * drv_adc.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "avr/io.h"
#include "drv_adc.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//structure adc
typedef struct SSAdc
{
	EIoPin pin_name;
	EAdcChannelSelection channel;
}SAdc;

//configuration initial des uarts
SAdc MesAdc[ CONF_ADC_NB ] ;

Int8U nb_use_adc = 0 ;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static Int8U DrvAdcPinConvertToIndex( EIoPin pin_name );
static Int8U DrvAdcChannelConvertToIndex( EAdcChannelSelection channel );

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Adc 
void DrvAdc( void )
{		
	micAdcSetAdcEnable();
	micAdcSetInterrupt();
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

//fait une convertion immediate sur un canal de l'adc
Int16U DrvAdcReadChannel( EIoPin pin_name ) 
{
	Int16U o_adc_value = 0xff;
	Int8U index_adc = DrvAdcPinConvertToIndex( pin_name );
	micAdcSetAnalogChannelandGainSelectionBits( MesAdc[index_adc].channel );
	micAdcClearInterrupt();
	micAdcSetStartConversion();	
	while(_SFR_BYTE(ADCSRA) & _BV(ADSC) ) ;
	o_adc_value = micAdcReadData16();
	micAdcSetInterrupt();
	return o_adc_value;	
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

/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
