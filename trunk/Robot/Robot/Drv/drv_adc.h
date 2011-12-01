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
// Method:    DrvAdcEnableAdc
// FullName:  DrvAdcEnableAdc
// Access:    public 
// Returns:   void
// Qualifier: active l'adc
// Parameter: EIoPin pin_name					//pin adc sur lequel on converti
//************************************
void DrvAdcEnableAdc( EIoPin pin_name ) ;


//************************************
// Method:    DrvAdcDisableAdc
// FullName:  DrvAdcDisableAdc
// Access:    public 
// Returns:   void
// Qualifier: desactive l'adc
// Parameter: EIoPin pin_name					//pin adc sur lequel on converti
//************************************
void DrvAdcDisableAdc( EIoPin pin_name ) ;


//************************************
// Method:    DrvAdcReadChannel
// FullName:  DrvAdcReadChannel
// Access:    public 
// Returns:   value of ADC
// Qualifier: fait une convertion immediate sur un canal de l'adc
// Parameter: EIoPin pin_name					//pin adc sur lequel on converti
//************************************
Int16U DrvAdcReadChannel( EIoPin pin_name ) ;


#endif /* DRV_ADC_H_ */