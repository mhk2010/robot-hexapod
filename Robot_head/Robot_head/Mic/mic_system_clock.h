/*
 * mic_system_clock.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef MIC_SYSTEM_CLOCK_H_
#define MIC_SYSTEM_CLOCK_H_

#include "Tools/tools_typedefs.h"


/////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////
typedef enum
{
  // No division:
  CLKPR_DIV_1 = (0U << CLKPS3) | (0U << CLKPS2) | (0U << CLKPS1) | (0U << CLKPS0),
  // Division by 2:
  CLKPR_DIV_2 = (0U << CLKPS3) | (0U << CLKPS2) | (0U << CLKPS1) | (1U << CLKPS0),
  // Division by 4:
  CLKPR_DIV_4 = (0U << CLKPS3) | (0U << CLKPS2) | (1U << CLKPS1) | (0U << CLKPS0),
  // Division by 8:
  CLKPR_DIV_8 = (0U << CLKPS3) | (0U << CLKPS2) | (1U << CLKPS1) | (1U << CLKPS0),
  // Division by 16:
  CLKPR_DIV_16 = (0U << CLKPS3) | (1U << CLKPS2) | (0U << CLKPS1) | (0U << CLKPS0),
  // Division by 32:
  CLKPR_DIV_32 = (0U << CLKPS3) | (1U << CLKPS2) | (0U << CLKPS1) | (1U << CLKPS0),
  // Division by 64:
  CLKPR_DIV_64 = (0U << CLKPS3) | (1U << CLKPS2) | (1U << CLKPS1) | (0U << CLKPS0),
  // Division by 128:
  CLKPR_DIV_128 = (0U << CLKPS3) | (1U << CLKPS2) | (1U << CLKPS1) | (1U << CLKPS0),
  // Division by 256:
  CLKPR_DIV_256 = (1U << CLKPS3) | (0U << CLKPS2) | (0U << CLKPS1) | (0U << CLKPS0)
}SystemClockPrescaler;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the CAL7:0: Oscillator Calibration Value
Boolean micSystemClockOscillatorCalibrationValue( Int8U osccal_value ) ;

//set the CLKPCE: Clock Prescaler Change Enable
Boolean micSystemClockPrescalerChangeEnable( Boolean enable ) ;

//set the CLKPS3:0: Clock Prescaler Select Bits 3 - 0
Boolean micSystemClockPrescalerSelectBits( SystemClockPrescaler prescaler_value ) ;


#endif /* MIC_SYSTEM_CLOCK_H_ */