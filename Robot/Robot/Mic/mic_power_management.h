/*
 * mic_power_management.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef MIC_POWER_MANAGEMENT_H_
#define MIC_POWER_MANAGEMENT_H_

#include "Tools/tools_typedefs.h"

/////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////
typedef enum
{
  SMCR_MODE_IDLE        = (0U << SM2) | (0U << SM1) | (0U << SM0),
  SMCR_MODE_ADC_NOISE   = (0U << SM2) | (0U << SM1) | (1U << SM0),
  SMCR_MODE_POWER_DOWN  = (0U << SM2) | (1U << SM1) | (0U << SM0),
  SMCR_MODE_POWER_SAVE  = (0U << SM2) | (1U << SM1) | (1U << SM0),
  SMCR_MODE_STANDBY     = (1U << SM2) | (1U << SM1) | (0U << SM0),
  SMCR_MODE_EXT_STANDBY = (1U << SM2) | (1U << SM1) | (1U << SM0),
}PowerMangementStanbyMode;



/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the SM2:0: Sleep Mode Select Bits 2, 1, and 0
Boolean micPowerMangementSleepMode ( PowerMangementStanbyMode sleep_mode )  ;

//set the SE: Sleep Enable
Boolean micPowerMangementSleepEnable ( Boolean enable ) ;

//set the BODS: BOD Sleep
Boolean micPowerMangementMasterControlUnitBrownOutVoltageSleep ( Boolean enable ) ;

//set the BODSE: BOD Sleep Enable
Boolean micPowerMangementMasterControlUnitBrownOutVoltageSleepEnable ( Boolean enable ) ;

//set the PRTWI: Power Reduction TWI
Boolean micPowerMangementPowerReductionTWI ( Boolean enable ) ;

//set the PRTIM2: Power Reduction Timer/Counter2
Boolean micPowerMangementPowerReductionTimerCounter2 ( Boolean enable ) ;

//set the PRTIM2: Power Reduction Timer/Counter0
Boolean micPowerMangementPowerReductionTimerCounter0 ( Boolean enable ) ;

//set the PRUSART1: Power Reduction USART1
Boolean micPowerMangementPowerReductionUSART1 ( Boolean enable ) ;

//set the PRTIM2: Power Reduction Timer/Counter1
Boolean micPowerMangementPowerReductionTimerCounter1 ( Boolean enable ) ;

//set the PRSPI: Power Reduction Serial Peripheral Interface
Boolean micPowerMangementPowerReductionSPI ( Boolean enable ) ;

//set the PRUSART1: Power Reduction USART0
Boolean micPowerMangementPowerReductionUSART0 ( Boolean enable ) ;

//set the PRADC: Power Reduction ADC
Boolean micPowerMangementPowerReductionADC ( Boolean enable ) ;





#endif /* MIC_POWER_MANAGEMENT_H_ */