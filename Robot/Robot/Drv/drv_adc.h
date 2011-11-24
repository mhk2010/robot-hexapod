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
typedef void (*ptrfct_Isr_Callback_Adc)( EIoPin pin_name ,Int16U adc_data );

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
// Parameter: Int8U index_adc					//index adc sur lequel on converti
//************************************
void DrvAdcEnableAdc( EIoPin pin_name ) ;


//************************************
// Method:    DrvAdcDisableAdc
// FullName:  DrvAdcDisableAdc
// Access:    public 
// Returns:   void
// Qualifier: desactive l'adc
// Parameter: Int8U index_adc					//index adc sur lequel on converti
//************************************
void DrvAdcDisableAdc( EIoPin pin_name ) ;


//************************************
// Method:    DrvAdcStartConvertion
// FullName:  DrvAdcStartConvertion
// Access:    public 
// Returns:   void
// Qualifier: Commence la convertion sur l'adc
// Parameter: Int8U index_adc					//index adc sur lequel on converti
//************************************
Boolean DrvAdcStartConvertion( EIoPin pin_name , ptrfct_Isr_Callback_Adc ptrfct) ;





#endif /* DRV_ADC_H_ */