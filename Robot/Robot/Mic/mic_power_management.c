/*
 * mic_power_management.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "mic_power_management.h"




/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the SM2:0: Sleep Mode Select Bits 2, 1, and 0
Boolean micPowerMangementSleepMode ( PowerMangementStanbyMode sleep_mode ) 
{
	Boolean o_success = TRUE;
	SMCR |= sleep_mode;
	return o_success;
}

//set the SE: Sleep Enable
Boolean micPowerMangementSleepEnable ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(SMCR,SE,enable);
	return o_success;
}

//set the BODS: BOD Sleep
Boolean micPowerMangementMasterControlUnitBrownOutVoltageSleep ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(MCUCR,BODS,enable);
	return o_success;
}

//set the BODSE: BOD Sleep Enable
Boolean micPowerMangementMasterControlUnitBrownOutVoltageSleepEnable ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(MCUCR,BODSE,enable);
	return o_success;
}

//set the PRTWI: Power Reduction TWI
Boolean micPowerMangementPowerReductionTWI ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PRR0,PRTWI,enable);
	return o_success;
}

//set the PRTIM2: Power Reduction Timer/Counter2
Boolean micPowerMangementPowerReductionTimerCounter2 ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PRR0,PRTIM2,enable);
	return o_success;
}

//set the PRTIM2: Power Reduction Timer/Counter0
Boolean micPowerMangementPowerReductionTimerCounter0 ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PRR0,PRTIM0,enable);
	return o_success;
}

//set the PRUSART1: Power Reduction USART1
Boolean micPowerMangementPowerReductionUSART1 ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PRR0,PRUSART1,enable);
	return o_success;
}

//set the PRTIM2: Power Reduction Timer/Counter1
Boolean micPowerMangementPowerReductionTimerCounter1 ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PRR0,PRTIM1,enable);
	return o_success;
}

//set the PRSPI: Power Reduction Serial Peripheral Interface
Boolean micPowerMangementPowerReductionSPI ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PRR0,PRSPI,enable);
	return o_success;
}

//set the PRUSART1: Power Reduction USART0
Boolean micPowerMangementPowerReductionUSART0 ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PRR0,PRUSART0,enable);
	return o_success;
}

//set the PRADC: Power Reduction ADC
Boolean micPowerMangementPowerReductionADC ( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PRR0,PRADC,enable);
	return o_success;
}