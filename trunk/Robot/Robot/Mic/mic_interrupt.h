/*
 * mic_interrupt.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef MIC_INTERRUPT_H_
#define MIC_INTERRUPT_H_

#include "Tools/tools_typedefs.h"


/////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////


typedef enum
{
  EICRA_ISC0_INT_LOW_LEVEL        =  (0U << ISC01) | (0U << ISC00),
  EICRA_ISC0_INT_ANY_EDGES        =  (0U << ISC01) | (1U << ISC00),
  EICRA_ISC0_INT_FALLING_EDGES    =  (1U << ISC01) | (0U << ISC00),
  EICRA_ISC0_INT_RISING_EDGES     =  (1U << ISC01) | (1U << ISC00),
}EInterruptTrigger_0;

typedef enum
{
  EICRA_ISC1_INT_LOW_LEVEL        =  (0U << ISC11) | (0U << ISC10),
  EICRA_ISC1_INT_ANY_EDGES        =  (0U << ISC11) | (1U << ISC10),
  EICRA_ISC1_INT_FALLING_EDGES    =  (1U << ISC11) | (0U << ISC10),
  EICRA_ISC1_INT_RISING_EDGES     =  (1U << ISC11) | (1U << ISC10),
}EInterruptTrigger_1;

typedef enum
{
  EICRA_ISC2_INT_LOW_LEVEL        =  (0U << ISC21) | (0U << ISC20),
  EICRA_ISC2_INT_ANY_EDGES        =  (0U << ISC21) | (1U << ISC20),
  EICRA_ISC2_INT_FALLING_EDGES    =  (1U << ISC21) | (0U << ISC20),
  EICRA_ISC2_INT_RISING_EDGES     =  (1U << ISC21) | (1U << ISC20),
}EInterruptTrigger_2;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the IVSEL: Interrupt Vector Select
Boolean micInterruptMasterControlUnitInterruptVectorSelect( Boolean enable ) ;

//set the IVCE: Interrupt Vector Change Enable
Boolean micInterruptMasterControlUnitInterruptVectorChangeEnable( Boolean enable ) ;

//set the ISC21, ISC20 – ISC00, ISC00: External Interrupt 2 - 0 Sense Control Bits
Boolean micInterruptSenseControlBits0( EInterruptTrigger_0  trigger ) ;

//set the ISC21, ISC20 – ISC00, ISC00: External Interrupt 2 - 0 Sense Control Bits
Boolean micInterruptSenseControlBits1( EInterruptTrigger_1  trigger ) ;

//set the ISC21, ISC20 – ISC00, ISC00: External Interrupt 2 - 0 Sense Control Bits
Boolean micInterruptSenseControlBits2( EInterruptTrigger_2  trigger ) ;

//set the INT2:0: External Interrupt Request 2 - 0 Enable
Boolean micInterruptExternalInterruptRequestEnable0( Boolean enable ) ;

//set the INT2:0: External Interrupt Request 2 - 0 Enable
Boolean micInterruptExternalInterruptRequestEnable1( Boolean enable ) ;

//set the INT2:0: External Interrupt Request 2 - 0 Enable
Boolean micInterruptExternalInterruptRequestEnable2( Boolean enable ) ;

//set the INTF2:0: External Interrupt Flags 2 - 0
Boolean micInterruptExternalInterruptFlags0( Boolean enable ) ;

//set the INTF2:0: External Interrupt Flags 2 - 0
Boolean micInterruptExternalInterruptFlags1( Boolean enable ) ;

//set the INTF2:0: External Interrupt Flags 2 - 0
Boolean micInterruptExternalInterruptFlags2( Boolean enable ) ;

//set the PCIE0: Pin Change Interrupt Enable 0
Boolean micInterruptPinChangeInterruptEnable0( Boolean enable ) ;

//set the PCIE1: Pin Change Interrupt Enable 1
Boolean micInterruptPinChangeInterruptEnable1( Boolean enable ) ;

//set the PCIE2: Pin Change Interrupt Enable 2
Boolean micInterruptPinChangeInterruptEnable2( Boolean enable ) ;

//set the PCIE2: Pin Change Interrupt Enable 3
Boolean micInterruptPinChangeInterruptEnable3( Boolean enable ) ;

//set the PCIF0: Pin Change Interrupt Flag 0
Boolean micInterruptPinChangeInterruptFlag0( Boolean enable ) ;

//set the PCIF1: Pin Change Interrupt Flag 1
Boolean micInterruptPinChangeInterruptFlag1( Boolean enable ) ;

//set the PCIF2: Pin Change Interrupt Flag 2
Boolean micInterruptPinChangeInterruptFlag2( Boolean enable ) ;

//set the PCIF3: Pin Change Interrupt Flag 3
Boolean micInterruptPinChangeInterruptFlag3( Boolean enable ) ;

//set the PCINT31:24: Pin Change Enable Mask 31:24
Boolean micInterruptPinChangeEnableMask3( Int8U val ) ;

//set the PCINT23:16: Pin Change Enable Mask 23..16
Boolean micInterruptPinChangeEnableMask2( Int8U val ) ;

//set the PCINT15:8: Pin Change Enable Mask 15..8
Boolean micInterruptPinChangeEnableMask1( Int8U val ) ;

//set the PCINT7:0: Pin Change Enable Mask 7..0
Boolean micInterruptPinChangeEnableMask0( Int8U val ) ;

#endif /* MIC_INTERRUPT_H_ */