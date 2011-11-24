/*
 * mic_system_control.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef MIC_SYSTEM_CONTROL_H_
#define MIC_SYSTEM_CONTROL_H_

#include "Tools/tools_typedefs.h"


/////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////
typedef enum
{
  WDTCSR_DIV_2K_CYCLES        = (0U << WDP3) | (0U << WDP2) | (0U << WDP1) | (0U << WDP0),
  WDTCSR_DIV_4K_CYCLES        = (0U << WDP3) | (0U << WDP2) | (0U << WDP1) | (1U << WDP0),
  WDTCSR_DIV_8K_CYCLES        = (0U << WDP3) | (0U << WDP2) | (1U << WDP1) | (0U << WDP0),
  WDTCSR_DIV_16K_CYCLES       = (0U << WDP3) | (0U << WDP2) | (1U << WDP1) | (1U << WDP0),
  WDTCSR_DIV_32_CYCLES        = (0U << WDP3) | (1U << WDP2) | (0U << WDP1) | (0U << WDP0),
  WDTCSR_DIV_64K_CYCLES       = (0U << WDP3) | (1U << WDP2) | (0U << WDP1) | (1U << WDP0),
  WDTCSR_DIV_128K_CYCLES      = (0U << WDP3) | (1U << WDP2) | (1U << WDP1) | (0U << WDP0),
  WDTCSR_DIV_256K_CYCLES      = (0U << WDP3) | (1U << WDP2) | (1U << WDP1) | (1U << WDP0),
  WDTCSR_DIV_512K_CYCLES      = (1U << WDP3) | (0U << WDP2) | (0U << WDP1) | (0U << WDP0),
  WDTCSR_DIV_1024K_CYCLES     = (1U << WDP3) | (0U << WDP2) | (0U << WDP1) | (1U << WDP0),
}ESystemWatchdogPrescaler;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//get the JTRF: JTAG Reset Flag
Boolean micSystemControlMasterControlUnitJtagResetFlag( void ) ;

//get the WDRF: Watchdog Reset Flag
Boolean micSystemControlMasterControlUnitWatchdogResetFlag( void ) ;

//get the BORF: Brown-out Reset Flag
Boolean micSystemControlMasterControlUnitBrownOutResetFlag( void ) ;

//get the EXTRF: External Reset Flag
Boolean micSystemControlMasterControlUnitExternalResetFlag( void ) ;

//get the PORF: Power-on Reset Flag
Boolean micSystemControlMasterControlUnitPowerOnResetFlag( void ) ;

//set the WDIF: Watchdog Interrupt Flag
Boolean micSystemControlWatchdogTimerControlWatchdogFlag( void ) ;

//get the WDIE: Watchdog Interrupt Enable
Boolean micSystemControlWatchdogTimerControlWatchdogInterruptEnable( Boolean enable ) ;

//get the WDCE: Watchdog Change Enable
Boolean micSystemControlWatchdogTimerControlWatchdogChangeEnable( void ) ;

//set the WDE: Watchdog System Reset Enable
Boolean micSystemControlWatchdogTimerControlWatchdogSystemResetEnable( Boolean enable ) ;

//set the WDP3:0: Watchdog Timer Prescaler 3, 2, 1 and 0
Boolean micSystemControlWatchdogTimerControlWatchdogTimerPrescaler( ESystemWatchdogPrescaler prescaler_value ) ;


#endif /* MIC_SYSTEM_CONTROL_H_ */