/*
 * Show_IR.c
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
#include "Drv/drv_servo.h"

#include "Ctrl/ctrl_uart_protocole.h"
#include "Ctrl/ctrl_tete.h"
#include "Ctrl/ctrl_marche.h"
#include "Ctrl/ctrl_patte.h"
#include "Ctrl/ctrl_ultrason.h"
#include "Ctrl/ctrl_boussole.h"
#include "Ctrl/ctrl_accel.h"

#include "Ctrl/ctrl_proximity.h"
#include "Ctrl/ctrl_light.h"

#include "App/app_robot.h"


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
	
	//on active la vie du robot
	//RobotLifeInit();
	CtrlLightLaunchFollowLight();
	//on boucle
    while( TRUE )
    {
		//on prend les events 
		main_event_flags = DrvEventGetEvent();
		
		//excecution du dispatcher d'evenements
		MainSystemControlDispatcher( );
		
		
		//on fait vivre le robot
		//RobotLife( main_event_flags );
		
		//on kill les events
		DrvEventKillEvent( main_event_flags );	
    }
}


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//init du main
static Boolean MainInitSystemDrivers(void)
{
	Boolean o_success = TRUE;
	
	DrvEvent();
	
	DrvAdc();
	DrvI2C();
	DrvTimer();
	
	return o_success;
}	

//lancement des controles du robot
static Boolean MainInitSystemControl( void ) 
{
	Boolean o_success = TRUE;
	
	//init des controls
	CtrlUartProtocole();
	CtrlUltraSon();
	CtrlBoussole();
	CtrlAccel();
	CtrlTete();
	CtrlMarche();
	
	CtrlProximity();
	CtrlLight();
	
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
		CtrlAccelDispatcher( main_event_flags );
		//CtrlBoussoleDispatcher( main_event_flags );
		CtrlUltraSonDispatcher( main_event_flags );
		//CtrlMarcheDispatcher( main_event_flags );
		//CtrlTeteDispatcher( main_event_flags );
		CtrlProximityDispatcher(main_event_flags);
		CtrlLightDispatcher(main_event_flags);
	}	
}	
	