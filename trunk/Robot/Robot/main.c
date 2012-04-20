/*
 * Show_IR.c
 *
 * Created: 28/06/2011 15:41:28
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "Drv/drv_event.h"
#include "Drv/drv_timer.h"
#include "Drv/drv_led.h"
#include "Drv/drv_interrupt.h"
#include "Drv/drv_servo.h"

#include "Ctrl/ctrl_uart_protocole.h"
#include "Ctrl/ctrl_marche.h"
#include "Ctrl/ctrl_patte.h"
#include "Ctrl/ctrl_tete.h"

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//init du main
static Boolean MainInitSystemDrivers( void ) ;
//lancement des control du robot
static Boolean MainInitSystemControl(void) ;
//excecution du dispatcher d'evenement des controls
static void MainSystemControlDispatcher( void ) ;
//excecution du heartbeat
static void MainSystemControlHearbeat( void );
//event main
volatile Event_t main_event_flags = 0;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//start here
int main(void)
{	
	//init du system
	MainInitSystemDrivers();
	
	//on lance nos controles
	MainInitSystemControl();
	
	//lance les its
	DrvInterruptSetAllInterrupts();
	
	//on boucle à l'infini
    while( TRUE )
    {
		//on prend les events 
		main_event_flags = DrvEventGetEvent();

		//excecution du dispatcher d'evenements
		MainSystemControlDispatcher();
		
		//on kill les events
		DrvEventKillEvent( main_event_flags );	
		
		//on toggle la led activity
		//elle permet de controler que l'on passe souvent dans la boucle infini du main
		DrvLedToggle ( CONF_LED_ACTIVITY );
    }
}


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//init des drivers du main
static Boolean MainInitSystemDrivers(void)
{
	Boolean o_success = TRUE;
	
	//init des drivers
 	DrvTimer();
	DrvEvent();
	DrvLed();
	DrvUart();
	DrvServo();
				
	return o_success;
}	

//lancement des controles du robot
static Boolean MainInitSystemControl( void ) 
{
	Boolean o_success = TRUE;
	
	//init des controls
	CtrlUartProtocole();
	CtrlTete();
	CtrlMarche();
	
	return o_success;
}



//excecution du dispatcher d'evenement
static void MainSystemControlDispatcher( void )
{
	//get next event
	if( main_event_flags > 0 )
	{
		//on dispatch l'event sur les different services
		CtrlUartProtocoleDispatcher( main_event_flags );
		CtrlMarcheDispatcher( main_event_flags );
		CtrlTeteDispatcher( main_event_flags );
		
		//hearbeat
		MainSystemControlHearbeat();			
	}	
}	

//excecution du heartbeat
static void MainSystemControlHearbeat( void )
{
	if ( DrvEventTestEvent(main_event_flags, CONF_EVENT_TIMER_1S ))
	{
		DrvLedToggle ( CONF_LED_HEARTBEAT );
	}	
}		