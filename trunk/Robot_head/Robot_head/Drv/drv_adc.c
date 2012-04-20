/*
 * drv_adc.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "avr/io.h"
#include "drv_adc.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Adc 
void DrvAdc( void )
{		
	//on fixe la ref
	micAdcSetReferenceSelectionBits(E_ADC_REF_AVCC_WITH_CAPA_AREF);
	//on active l'adc
	micAdcSetAdcEnable();
}


//fait une convertion immediate sur un canal de l'adc
Int16U DrvAdcReadChannel( EAdcChannelSelection channel ) 
{
	Int16U o_adc_value = 0xffff;
	micAdcSetAnalogChannelandGainSelectionBits( channel );
	micAdcSetStartConversion();	
	while(_SFR_BYTE(ADCSRA) & _BV(ADSC) ) ;
	o_adc_value = micAdcReadData16();
	return o_adc_value;	
}



/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
