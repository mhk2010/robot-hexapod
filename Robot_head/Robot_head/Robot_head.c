/*
 * Robot_head.c
 *
 * Created: 28/06/2011 15:41:28
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "Drv/drv_event.h"
#include "Drv/drv_timer.h"
#include "Drv/drv_interrupt.h"
#include "Drv/drv_adc.h"
#include "Drv/drv_i2c.h"
#include "Drv/drv_timer.h"

#include "Ctrl/ctrl_uart_protocole.h"
#include "Ctrl/ctrl_microphone.h"
#include "Ctrl/ctrl_eye.h"
#include "Ctrl/ctrl_ultrason.h"
#include "Ctrl/ctrl_camera.h"
#include "Ctrl/ctrl_light.h"



////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//init du main
static Boolean MainInitSystemDrivers( void ) ;
//lancement des control du robot
static Boolean MainInitSystemControl(void) ;
//excecution du dispatcher d'evenement des controls
static void MainSystemControlDispatcher() ;
//event main
static Event_t main_event_flags = 0;

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

	//on a fini l'init 
	CtrlEyeBlink(3);
	
	//on boucle
    while( TRUE )
    {
		//on prend les events 
		main_event_flags = DrvEventGetEvent();
		
		//excecution du dispatcher d'evenements
		MainSystemControlDispatcher( );
				
		//on kill les events
		DrvEventKillEvent( main_event_flags );	
    }
}


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//init des drivers du main
static Boolean MainInitSystemDrivers(void)
{
	Boolean o_success = TRUE;
	
	//init des drivers
	DrvUart();
	DrvTimer();
	DrvEvent();
	DrvAdc();
	DrvI2C();
		
	//on active la pin d'alim du control des LDR et des yeux
	micIoPortsConfigureOutput(CONF_CMD_ALIM_LDR);
	micIoPortsConfigureToLowLevel(CONF_CMD_ALIM_LDR);
	
	//on active la pin d'alim du control de l'ultrason
	micIoPortsConfigureOutput(CONF_CMD_ALIM_ULTRASON);
	micIoPortsConfigureToLowLevel(CONF_CMD_ALIM_ULTRASON);
	
	return o_success;
}	

//lancement des controles du robot
static Boolean MainInitSystemControl( void ) 
{
	Boolean o_success = TRUE;
	
	//init des controls
	CtrlUartProtocole();
	CtrlUltraSon();
	//CtrlMicrophone();
	CtrlEye();
	CtrlLight();
	CtrlCamera();
	return o_success;
}



//excecution du dispatcher d'evenement
static void MainSystemControlDispatcher( void )
{
	//get next event
	if(main_event_flags > 0)
	{
		//on dispatch l'event 
		CtrlUartProtocoleDispatcher( main_event_flags );
		CtrlUltraSonDispatcher( main_event_flags );
		CtrlLightDispatcher( main_event_flags );
		CtrlCameraDispatcher( main_event_flags );
	}	
	//quand il n'y pas d'events
	//CtrlMicrophoneDispatcher( main_event_flags );
}	
	