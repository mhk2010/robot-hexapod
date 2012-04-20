/*
 * mic_system_control.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "mic_system_control.h"



/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//get the JTRF: JTAG Reset Flag
Boolean micSystemControlMasterControlUnitJtagResetFlag( void ) 
{
	Boolean o_success;
	o_success = (MCUSR & JTRF) >> JTRF;
	return o_success;
}

//get the WDRF: Watchdog Reset Flag
Boolean micSystemControlMasterControlUnitWatchdogResetFlag( void ) 
{
	Boolean o_success;
	o_success = (MCUSR & WDRF) >> WDRF;
	return o_success;
}

//get the BORF: Brown-out Reset Flag
Boolean micSystemControlMasterControlUnitBrownOutResetFlag( void ) 
{
	Boolean o_success;
	o_success = (MCUSR & BORF) >> BORF;
	return o_success;
}

//get the EXTRF: External Reset Flag
Boolean micSystemControlMasterControlUnitExternalResetFlag( void ) 
{
	Boolean o_success;
	o_success = (MCUSR & JTRF) >> JTRF;
	return o_success;
}

//get the PORF: Power-on Reset Flag
Boolean micSystemControlMasterControlUnitPowerOnResetFlag( void ) 
{
	Boolean o_success;
	o_success = (MCUSR & PORF) >> PORF;
	return o_success;
}

//get the WDIF: Watchdog Interrupt Flag
Boolean micSystemControlWatchdogTimerControlWatchdogFlag( void ) 
{
	Boolean o_success;
	o_success = (WDTCSR & WDIF) >> WDIF;
	return o_success;
}

//set the WDIE: Watchdog Interrupt Enable
Boolean micSystemControlWatchdogTimerControlWatchdogInterruptEnable( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(WDTCSR,WDIE,enable);
	return o_success;
}

//get the WDCE: Watchdog Change Enable
Boolean micSystemControlWatchdogTimerControlWatchdogChangeEnable( void ) 
{
	Boolean o_success;
	o_success = (WDTCSR & WDCE) >> WDCE;
	return o_success;
}

//set the WDE: Watchdog System Reset Enable
Boolean micSystemControlWatchdogTimerControlWatchdogSystemResetEnable( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(WDTCSR,WDE,enable);
	return o_success;
}

//set the WDP3:0: Watchdog Timer Prescaler 3, 2, 1 and 0
Boolean micSystemControlWatchdogTimerControlWatchdogTimerPrescaler( ESystemWatchdogPrescaler prescaler_value ) 
{
	Boolean o_success = TRUE;
	WDTCSR |= prescaler_value;
	return o_success;
}