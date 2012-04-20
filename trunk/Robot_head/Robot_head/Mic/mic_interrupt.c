/*
 * mic_interrupt.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "mic_interrupt.h"



/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the IVSEL: Interrupt Vector Select
Boolean micInterruptMasterControlUnitInterruptVectorSelect( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(MCUCR,IVSEL,enable);
	return o_success;
}

//set the IVCE: Interrupt Vector Change Enable
Boolean micInterruptMasterControlUnitInterruptVectorChangeEnable( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(MCUCR,IVCE,enable);
	return o_success;
}

//set the ISC21, ISC20 – ISC00, ISC00: External Interrupt 2 - 0 Sense Control Bits
Boolean micInterruptSenseControlBits0( EInterruptTrigger_0  trigger ) 
{
	Boolean o_success = TRUE;
	EICRA |= trigger;
	return o_success;
}

//set the ISC21, ISC20 – ISC00, ISC00: External Interrupt 2 - 0 Sense Control Bits
Boolean micInterruptSenseControlBits1( EInterruptTrigger_1  trigger ) 
{
	Boolean o_success = TRUE;
	EICRA |= trigger;
	return o_success;
}

//set the ISC21, ISC20 – ISC00, ISC00: External Interrupt 2 - 0 Sense Control Bits
Boolean micInterruptSenseControlBits2( EInterruptTrigger_2  trigger ) 
{
	Boolean o_success = TRUE;
	EICRA |= trigger;
	return o_success;
}

//set the INT2:0: External Interrupt Request 2 - 0 Enable
Boolean micInterruptExternalInterruptRequestEnable0( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(EIMSK,INT0,enable);
	return o_success;
}

//set the INT2:0: External Interrupt Request 2 - 0 Enable
Boolean micInterruptExternalInterruptRequestEnable1( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(EIMSK,INT1,enable);
	return o_success;
}

//set the INT2:0: External Interrupt Request 2 - 0 Enable
Boolean micInterruptExternalInterruptRequestEnable2( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(EIMSK,INT2,enable);
	return o_success;
}

//set the INTF2:0: External Interrupt Flags 2 - 0
Boolean micInterruptExternalInterruptFlags0( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(EIFR,INTF0,enable);
	return o_success;
}

//set the INTF2:0: External Interrupt Flags 2 - 0
Boolean micInterruptExternalInterruptFlags1( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(EIFR,INTF1,enable);
	return o_success;
}

//set the INTF2:0: External Interrupt Flags 2 - 0
Boolean micInterruptExternalInterruptFlags2( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(EIFR,INTF2,enable);
	return o_success;
}

//set the PCIE0: Pin Change Interrupt Enable 0
Boolean micInterruptPinChangeInterruptEnable0( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PCICR,PCIE0,enable);
	return o_success;
}

//set the PCIE1: Pin Change Interrupt Enable 1
Boolean micInterruptPinChangeInterruptEnable1( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PCICR,PCIE1,enable);
	return o_success;
}

//set the PCIE2: Pin Change Interrupt Enable 2
Boolean micInterruptPinChangeInterruptEnable2( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PCICR,PCIE2,enable);
	return o_success;
}

//set the PCIE2: Pin Change Interrupt Enable 3
Boolean micInterruptPinChangeInterruptEnable3( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PCICR,PCIE3,enable);
	return o_success;
}

//set the PCIF0: Pin Change Interrupt Flag 0
Boolean micInterruptPinChangeInterruptFlag0( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PCIFR,PCIF0,enable);
	return o_success;
}

//set the PCIF1: Pin Change Interrupt Flag 1
Boolean micInterruptPinChangeInterruptFlag1( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PCIFR,PCIF1,enable);
	return o_success;
}

//set the PCIF2: Pin Change Interrupt Flag 2
Boolean micInterruptPinChangeInterruptFlag2( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PCIFR,PCIF2,enable);
	return o_success;
}

//set the PCIF3: Pin Change Interrupt Flag 3
Boolean micInterruptPinChangeInterruptFlag3( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PCIFR,PCIF3,enable);
	return o_success;
}

//set the PCINT31:24: Pin Change Enable Mask 31:24
Boolean micInterruptPinChangeEnableMask3( Int8U val ) 
{
	Boolean o_success = TRUE;
	PCMSK3 |= val;
	return o_success;
}

//set the PCINT23:16: Pin Change Enable Mask 23..16
Boolean micInterruptPinChangeEnableMask2( Int8U val ) 
{
	Boolean o_success = TRUE;
	PCMSK2 |= val;
	return o_success;
}

//set the PCINT15:8: Pin Change Enable Mask 15..8
Boolean micInterruptPinChangeEnableMask1( Int8U val ) 
{
	Boolean o_success = TRUE;
	PCMSK1 |= val;
	return o_success;
}

//set the PCINT7:0: Pin Change Enable Mask 7..0
Boolean micInterruptPinChangeEnableMask0( Int8U val ) 
{
	Boolean o_success = TRUE;
	PCMSK0 |= val;
	return o_success;
}