/*
 * mic_adc.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef MIC_ADC_H_
#define MIC_ADC_H_

#include "Tools/tools_typedefs.h"



/////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////
typedef enum EEAdcReferenceSelectionBits
{
  E_ADC_REF_INTERNAL_TURN_OFF	= ( (0U << REFS1) | (0U << REFS0) ),
  E_ADC_REF_AVCC_WITH_CAPA_AREF = ( (0U << REFS1) | (1U << REFS0) ),
  E_ADC_REF_INTERNAL_1_1_V		= ( (1U << REFS1) | (0U << REFS0) ),
  E_ADC_REF_INTERNAL_2_56_V		= ( (1U << REFS1) | (1U << REFS0) ),
}EAdcReferenceSelectionBits;

typedef enum EEAdcChannelSelection
{
  ADC_CHANNEL_0 			= 0U,
  ADC_CHANNEL_1 			= 1U,
  ADC_CHANNEL_2 			= 2U,
  ADC_CHANNEL_3 			= 3U,
  ADC_CHANNEL_4 			= 4U,
  ADC_CHANNEL_5 			= 5U,
  ADC_CHANNEL_6 			= 6U,
  ADC_CHANNEL_7				= 7U,
  ADC_DIFF_CHANNEL_00_10X	= 8U,
  ADC_DIFF_CHANNEL_10_10X	= 9U,
  ADC_DIFF_CHANNEL_10_200X	= 11U,
  ADC_DIFF_CHANNEL_22_10X	= 12U,
  ADC_DIFF_CHANNEL_32_10X	= 13U,
  ADC_DIFF_CHANNEL_22_200X	= 14U,
  ADC_DIFF_CHANNEL_32_200X	= 15U,
  ADC_DIFF_CHANNEL_01_1X	= 16U,
  ADC_DIFF_CHANNEL_11_1X	= 17U,
  ADC_DIFF_CHANNEL_21_1X	= 18U,
  ADC_DIFF_CHANNEL_31_1X	= 19U,
  ADC_DIFF_CHANNEL_41_1X	= 20U,
  ADC_DIFF_CHANNEL_51_1X	= 21U,
  ADC_DIFF_CHANNEL_61_1X	= 22U,
  ADC_DIFF_CHANNEL_71_1X	= 23U,
  ADC_DIFF_CHANNEL_02_1X	= 24U,
  ADC_DIFF_CHANNEL_12_1X	= 25U,
  ADC_DIFF_CHANNEL_22_1X	= 26U,
  ADC_DIFF_CHANNEL_32_1X	= 27U,
  ADC_DIFF_CHANNEL_42_1X	= 28U,
  ADC_DIFF_CHANNEL_52_1X	= 29U,
  ADC_CHANNEL_BANDGAP_REF	= 30U,
  ADC_CHANNEL_GND			= 31U
}EAdcChannelSelection;

typedef enum EEAdcClock
{
  ADC_CLK_DIV_2   = (0U << ADPS2) | (0U << ADPS1) | (1U << ADPS0),
  ADC_CLK_DIV_4   = (0U << ADPS2) | (1U << ADPS1) | (0U << ADPS0),
  ADC_CLK_DIV_8   = (0U << ADPS2) | (1U << ADPS1) | (1U << ADPS0),
  ADC_CLK_DIV_16  = (1U << ADPS2) | (0U << ADPS1) | (0U << ADPS0),
  ADC_CLK_DIV_32  = (1U << ADPS2) | (0U << ADPS1) | (1U << ADPS0),
  ADC_CLK_DIV_64  = (1U << ADPS2) | (1U << ADPS1) | (0U << ADPS0),
  ADC_CLK_DIV_128 = (1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0)
}EAdcClock;

typedef enum EAdcTrigger
{
  ADC_TRIG_FREE_RUNNING		= (0U << ADTS2) | (0U << ADTS1) | (0U << ADTS0),
  ADC_TRIG_ANALOG_COMP		= (0U << ADTS2) | (0U << ADTS1) | (1U << ADTS0),
  ADC_TRIG_INT0				= (0U << ADTS2) | (1U << ADTS1) | (0U << ADTS0),
  ADC_TRIG_TIMER0_COMPARE	= (0U << ADTS2) | (1U << ADTS1) | (1U << ADTS0),
  ADC_TRIG_TIMER0_OVERFLOW	= (1U << ADTS2) | (0U << ADTS1) | (0U << ADTS0),
  ADC_TRIG_TIMER1_COMPARE	= (1U << ADTS2) | (0U << ADTS1) | (1U << ADTS0),
  ADC_TRIG_TIMER1_OVERFLOW	= (1U << ADTS2) | (1U << ADTS1) | (0U << ADTS0),
  ADC_TRIG_TIMER1_CAPTURE	= (1U << ADTS2) | (1U << ADTS1) | (1U << ADTS0)
}EAdcTrigger;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the REFS1:0: Reference Selection Bits
Boolean micAdcSetReferenceSelectionBits( EAdcReferenceSelectionBits mode ) ;

//set the ADLAR: ADC Left Adjust Result
Boolean micAdcSetLeftAdjustResult( void ) ;
//Get the ADLAR: ADC Left Adjust Result
Boolean micAdcGetLeftAdjustResult( void ) ;
//Clear the ADLAR: ADC Left Adjust Result
Boolean micAdcClearLeftAdjustResult( void ) ;

//set the MUX4:0: Analog Channel and Gain Selection Bits
Boolean micAdcSetAnalogChannelandGainSelectionBits( EAdcChannelSelection adc_channel ) ;

//Get the MUX4:0: Analog Channel and Gain Selection Bits
EAdcChannelSelection micAdcGetAnalogChannelandGainSelectionBits( void ) ;

//set the ADEN: ADC Enable
Boolean micAdcSetAdcEnable( void ) ;

//set the ADEN: ADC Disable
Boolean micAdcSetAdcDisable( void ) ;

//set the ADSC: ADC Start Conversion
Boolean micAdcSetStartConversion( void ) ;

//set the ADATE: ADC Auto Trigger Enable
Boolean micAdcSetAutoTriggerEnable( void ) ;

//set the ADATE: ADC Auto Trigger Disable
Boolean micAdcSetAutoTriggerDisable( void ) ;

//Clear the ADIF: ADC Interrupt Flag
Boolean micAdcClearConversionCompletedFlag(void) ;

//set the ADIE: ADC Interrupt Enable
Boolean micAdcSetInterrupt(void) ;

//set the ADIE: ADC Interrupt Disable
Boolean micAdcClearInterrupt(void) ;

//Set the ADPS2:0: ADC Prescaler Select Bits
Boolean micAdcSetPrescalerSelectBits( EAdcClock adc_clock ) ;

//Set the ADTS2:0: ADC Auto Trigger Source
Boolean micAdcSetAutoTriggerSource( EAdcTrigger adc_trigger_source ) ;

//Get the ADC Conversion Result
Int8U micAdcReadData8( void ) ;

//Get the ADC Conversion Result
Int16U micAdcReadData16( void ) ;




#endif /* MIC_ADC_H_ */