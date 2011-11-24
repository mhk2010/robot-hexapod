/*
 * mic_system_clock.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "mic_system_clock.h"



/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the CAL7:0: Oscillator Calibration Value
Boolean micSystemClockOscillatorCalibrationValue( Int8U osccal_value ) 
{
	Boolean o_success = TRUE;
	
	OSCCAL = osccal_value;
	return o_success;
}

//set the CLKPCE: Clock Prescaler Change Enable
Boolean micSystemClockPrescalerChangeEnable( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(CLKPR,CLKPCE,enable);
	return o_success;
}

//set the CLKPS3:0: Clock Prescaler Select Bits 3 - 0
Boolean micSystemClockPrescalerSelectBits( SystemClockPrescaler prescaler_value ) 
{
	Boolean o_success = TRUE;
	CLKPR |= (prescaler_value & 0x0F);
	return o_success;
}
