/*
 * drv_led.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef DRV_TIMER_H_
#define DRV_TIMER_H_

#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"

#include "Drv/drv_event.h"

#include "Mic/mic_timer_0.h"
#include "Mic/mic_io_ports.h"



//////////////////////////////////////////PUBLIC PTR FCTS//////////////////////////////////////////
typedef void (*ptrfct_Isr_Callback_Timer)( void);

////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////
//mode fonctionnement du timer
typedef enum
{
  E_TIMER_MODE_ONE_SHOT,
  E_TIMER_MODE_PERIODIC,
  E_TIMER_MODE_NONE,
}ETimerMode;

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Timer 
void DrvTimer( void ) ;

//fct qui parametre le timer
void DrvTimerPlayTimer( Int8U index_timer, Int16U delay, ETimerMode mode, ptrfct_Isr_Callback_Timer ptrfct ) ;

//fct qui met en pause le timer
void DrvTimerPauseTimer( Int8U index_timer ) ;

//fct qui remet a zero les parametres du timer
void DrvTimerStopTimer( Int8U index_timer ) ;

//fct qui reseter le timer
void DrvTimerResetTimer( Int8U index_timer ) ;

//fct qui fixe un delay au timer
void DrvTimerDelayTimer( Int8U index_timer , Int16U delay) ;

#endif /* DRV_TIMER_H_ */