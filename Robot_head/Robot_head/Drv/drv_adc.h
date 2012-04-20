/*
 * drv_adc.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef DRV_ADC_H_
#define DRV_ADC_H_

#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"

#include "Mic/mic_io_ports.h"
#include "Mic/mic_adc.h"



////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////

//////////////////////////////////////////PUBLIC PTR FCTS//////////////////////////////////////////

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Adc 
void DrvAdc( void ) ;


//************************************
// Method:    DrvAdcReadChannel
// FullName:  DrvAdcReadChannel
// Access:    public 
// Returns:   value of ADC
// Qualifier: fait une convertion immediate sur un canal de l'adc
// Parameter: EAdcChannelSelection channel		
//************************************
Int16U DrvAdcReadChannel( EAdcChannelSelection channel )  ;


#endif /* DRV_ADC_H_ */