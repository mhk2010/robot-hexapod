/*
 * uart_protocole.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef CTRL_UART_PROTOCOLE_H_
#define CTRL_UART_PROTOCOLE_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Drv/drv_uart.h"
#include "Drv/drv_timer.h"
#include "Drv/drv_event.h"

#include "Conf/conf_hard.h"



///////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////
#define E_PROTOCOLE_PARAMETER_SERVO		0U
#define E_PROTOCOLE_PARAMETER_PATTE		1U

#define E_PROTOCOLE_PARAMETER_SERVO_POSITION		0U

#define E_PROTOCOLE_PARAMETER_ADC		1U
/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlUartProtocole( void ) ;
//dispatcher 
void CtrlUartProtocoleDispatcher( Event_t event ) ;
#endif /* CTRL_UART_PROTOCOLE_H_ */