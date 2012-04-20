/*
 * drv_led.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef DRV_LED_H_
#define DRV_LED_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"




////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////
//enum de config des leds
typedef enum
{
  STATE_LED_ON,
  STATE_LED_OFF,
}ELedState;

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

void DrvLed( void );


//************************************
// Method:    DrvLedOn
// FullName:  DrvLedOn
// Access:    public 
// Returns:   void
// Qualifier: Allume la led
// Parameter: Int8U led_name : LED defined in conf_hard.h
//************************************
void DrvLedOn ( Int8U led_name );


//************************************
// Method:    DrvLedOff
// FullName:  DrvLedOff
// Access:    public 
// Returns:   void
// Qualifier: Etiends la led
// Parameter: Int8U led_name : LED defined in conf_hard.h
//************************************
void DrvLedOff ( Int8U led_name );


//************************************
// Method:    DrvLedToggle
// FullName:  DrvLedToggle
// Access:    public 
// Returns:   void
// Qualifier: Toggle la led
// Parameter: Int8U led_name : LED defined in conf_hard.h
//************************************
void DrvLedToggle ( Int8U led_name );


//************************************
// Method:    DrvLedFlash
// FullName:  DrvLedFlash
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Int8U led_name : LED defined in conf_hard.h
// Parameter: Int8U nb_flash : nb de flash avant son extinction
// Parameter: Int16U time_on : temps a l'etat ON
// Parameter: Int16U time_off: temps a l'etat OFF
//************************************
void DrvLedFlash ( Int8U led_name, Int8U nb_flash, Int16U time_on, Int16U time_off ) ;



//************************************
// Method:    DrvLedFlash
// FullName:  DrvLedFlash
// Access:    public 
// Returns:   void
// Qualifier: Flash direct de la led
// Parameter: Int8U led_name : LED defined in conf_hard.h
// Parameter: Int8U nb_flash : nb de flash avant son extinction
// Parameter: Int16U time_on : temps a l'etat ON
// Parameter: Int16U time_off: temps a l'etat OFF
//************************************
void DrvLedDirectFlash ( Int8U led_name, Int8U nb_flash, Int16U time_on, Int16U time_off ) ;
#endif /* DRV_LED_H_ */