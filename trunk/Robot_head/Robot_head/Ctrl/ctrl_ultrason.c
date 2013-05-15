/*
 * ctrl_ultrason.c
 *
 * Created: 16/11/2011 12:07:43
 *  Author: berryer
 */ 

#include "ctrl_ultrason.h"

#include "Drv/drv_uart.h"

#define SRF08_SLAVE_ADDRESS		0xE0U	//addresse du module SRF08

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//ISR de flash de la led
static void DrvUltrason_ISR( void );

//permet de lire la valeur mesuré en cm par le dernier pulse envoyé
static void CtrlUltraSonReadSensorMesure( void ) ;
//permet d'envoyé un pulse 
static void CtrlUltraSonSendPulse( void ) ;

/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
Int16U us_mesure = 0U;


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlUltraSon( void ) 
{
	DrvI2CUltraSon();
	us_mesure = 0;
	DrvTimerPlayTimer( CONF_TIMER_US, 70U, E_TIMER_MODE_PERIODIC, DrvUltrason_ISR );
	CtrlUltraSonSendPulse();
}


//retourne la mesure 
Int16U CtrlUltraSonReadMesure( void ) 
{
	return us_mesure;
}


/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//permet de lire la valeur mesuré en cm par le dernier pulse envoyé
static void CtrlUltraSonReadSensorMesure( void ) 
{
	Int16U us_mesure_tab_echo[16U];
	//calcul de distance
	for( Int8U loop_echo = 0 ; loop_echo < 16U ; loop_echo++)
	{
		//on prend la vaeur de l'echo
		us_mesure_tab_echo[ loop_echo ] = DrvI2CUltraSonRead(SRF08_SLAVE_ADDRESS,(loop_echo *2)  + 2) << 8;
		us_mesure_tab_echo[ loop_echo ] |= DrvI2CUltraSonRead(SRF08_SLAVE_ADDRESS,(loop_echo *2) + 3);
		//on la div par le nb d'Alle Retour
		us_mesure_tab_echo[ loop_echo ] /= (loop_echo + 1);
		us_mesure += us_mesure_tab_echo[ loop_echo ];
	}
	
	//on fait la moyenne
	us_mesure /= 16U;		
	
	if (us_mesure_tab_echo[0] < SECURITY_PERIMETER)
	{
		us_mesure = us_mesure_tab_echo[0];
		//si inf à 5cm on laisse 5 cm
		if(us_mesure_tab_echo[0] < 5 )
		{
			us_mesure_tab_echo[0] = 5;
		}
		us_mesure = us_mesure_tab_echo[0];
		//on envoie l'event
		DrvEventAddEvent( CONF_EVENT_US_ALARM_PROX );
	}	
}

//permet d'envoyé un pulse 
static void CtrlUltraSonSendPulse( void ) 
{
	DrvI2CUltraSonTransmit(SRF08_SLAVE_ADDRESS, 0x00, 0x51);
}	


//permet d'envoyer sur l'uart un objet proche
void CtrlUltraSendUartProximity( void ) 
{
	Char buffer[7U];
	
	buffer[0U] = '*';
	buffer[1U] = E_PROTOCOLE_HEAD;
	buffer[2U] = E_PROTOCOLE_WHO_US;
	buffer[3U] = us_mesure >> 8U;
	buffer[4U] = us_mesure;
	buffer[5U] = '#';
	buffer[6U] = '#';
	DrvUartDirectSendBytes(CONF_UART_0_INDEX,(Int8U*)buffer,7U);
}


/////////////////////////////////////ISR PUBLIC FUNCTIONS////////////////////////////////////////
//ISR de flash de la led
static void DrvUltrason_ISR( void )
{
	CtrlUltraSonReadSensorMesure();
	CtrlUltraSendUartProximity();
}	