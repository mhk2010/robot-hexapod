/*
 * mic_adc.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "mic_adc.h"


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//Set the REFS1:0: Reference Selection Bits
Boolean micAdcSetReferenceSelectionBits( EAdcReferenceSelectionBits mode ) 
{
	Boolean o_success = TRUE;
	ADMUX = ( ADMUX & ~( ( 1U << REFS1 ) | ( 1U << REFS0 ) ) ) |\
             ( mode   &  ( ( 1U << REFS1 ) | ( 1U << REFS0 ) ) );
	return o_success;
}

//Set the ADLAR: ADC Left Adjust Result
Boolean micAdcSetLeftAdjustResult( void ) 
{
	Boolean o_success = TRUE;
	BIT_SET(ADMUX,ADLAR,TRUE);
	return o_success;
}

//Get the ADLAR: ADC Left Adjust Result
Boolean micAdcGetLeftAdjustResult( void ) 
{
	return (Boolean)(ADMUX & ( 1 << ADLAR) >> ADLAR);
}

//Clear the ADLAR: ADC Left Adjust Result
Boolean micAdcClearLeftAdjustResult( void ) 
{
	Boolean o_success = TRUE;
	BIT_SET(ADMUX,ADLAR,FALSE);
	return o_success;
}

//Set the MUX4:0: Analog Channel and Gain Selection Bits
Boolean micAdcSetAnalogChannelandGainSelectionBits( EAdcChannelSelection adc_channel ) 
{
	Boolean o_success = TRUE;
	ADMUX = (ADMUX & ~( (1U << MUX4) | (1U << MUX3) | (1U << MUX2) | (1U << MUX1) | (1U << MUX0) )) |
	         (adc_channel & ( (1U << MUX4) | (1U << MUX3) | (1U << MUX2) | (1U << MUX1) | (1U << MUX0) ) );
	return o_success;
}

//Get the MUX4:0: Analog Channel and Gain Selection Bits
EAdcChannelSelection micAdcGetAnalogChannelandGainSelectionBits( void ) 
{
	return (EAdcChannelSelection)( ADMUX & ( (1U << MUX4) | (1U << MUX3) | (1U << MUX2) | (1U << MUX1) | (1U << MUX0) ) );
}


//Set the ADEN: ADC Enable
Boolean micAdcSetAdcEnable( void ) 
{
	Boolean o_success = TRUE;
	BIT_SET(ADCSRA,ADEN,TRUE);
	return o_success;
}

//Set the ADEN: ADC Disable
Boolean micAdcSetAdcDisable( void ) 
{
	Boolean o_success = TRUE;
	BIT_SET(ADCSRA,ADEN,FALSE);
	return o_success;
}

//Set the ADSC: ADC Start Conversion
Boolean micAdcSetStartConversion( void ) 
{
	Boolean o_success = TRUE;
	BIT_SET(ADCSRA,ADSC,TRUE);
	return o_success;
}

//Set the ADATE: ADC Auto Trigger Enable
Boolean micAdcSetAutoTriggerEnable( void ) 
{
	Boolean o_success = TRUE;
	BIT_SET(ADCSRA,ADATE,TRUE);
	return o_success;
}

//Set the ADATE: ADC Auto Trigger Disable
Boolean micAdcSetAutoTriggerDisable( void ) 
{
	Boolean o_success = TRUE;
	BIT_SET(ADCSRA,ADATE,FALSE);
	return o_success;
}

//Clear the ADIF: ADC Interrupt Flag
Boolean micAdcClearConversionCompletedFlag(void) 
{
	Boolean o_success = TRUE;
	// To avoid to restart a conversion when clearing ADIF
	ADCSRA = ( ADCSRA & ~( 1U << ADSC ) ) | ( 1U<< ADIF );
	return o_success;
}

//Set the ADIE: ADC Interrupt Enable
Boolean micAdcSetInterrupt(void)
{
	Boolean o_success = TRUE;
	BIT_SET(ADCSRA,ADIE,TRUE);
	return o_success;
}

//Set the ADIE: ADC Interrupt Disable
Boolean micAdcClearInterrupt(void)
{
	Boolean o_success = TRUE;
	BIT_SET(ADCSRA,ADIE,FALSE);
	return o_success;
}

//Set the ADPS2:0: ADC Prescaler Select Bits
Boolean micAdcSetPrescalerSelectBits( EAdcClock adc_clock )
{
	Boolean o_success = TRUE;
	ADCSRA = (ADCSRA & ~((1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0))) |\
			 (adc_clock & ((1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0)));
	return o_success;
}

//Set the ADTS2:0: ADC Auto Trigger Source
Boolean micAdcSetAutoTriggerSource( EAdcTrigger adc_trigger_source )
{
	Boolean o_success = TRUE;
    ADCSRB = (ADCSRB &  ~((1U << ADTS2) | (1U << ADTS1) | (1U << ADTS0))) |\
             (adc_trigger_source &  ((1U << ADTS2) | (1U << ADTS1) | (1U << ADTS0)));
	return o_success;
}

//Get the ADC Conversion Result
Int8U micAdcReadData8( void )
{
	if(micAdcGetLeftAdjustResult() == TRUE)
	{	
		return ADCH;	
	}
	else
	{
		return ADCL;	
	}
}

//Get the ADC Conversion Result
Int16U micAdcReadData16( void )
{
	return ADC;	
}



