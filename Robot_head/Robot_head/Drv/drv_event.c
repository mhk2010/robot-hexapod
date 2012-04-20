/*
 * drv_event.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_event.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


static Event_t event_flags = 0;
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Event 
void DrvEvent( void )
{
	event_flags = 0;
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

//
void DrvEventKillEvent(Event_t in_event) 
{
	ATOMIC(
		event_flags = ~(in_event | ~event_flags);
	)
}

//
Event_t DrvEventGetEvent(void)
{
  return event_flags;
}

//
Boolean DrvEventTestEvent(Event_t in_event,Int8U conf_event ) 
{
	if (( in_event & conf_event) > 0 )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//
Boolean DrvEventAddEvent(Event_t event)
{
	Boolean o_success = FALSE;
	ATOMIC(
		event_flags |= event ;
		o_success = TRUE;
	)
	
	return o_success;
}


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////