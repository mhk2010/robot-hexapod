/*
 * conf_hard.h
 *
 * Created: 12/07/2011 18:18:08
 *  Author: berryer
 */ 


#ifndef CONF_HARD_H_
#define CONF_HARD_H_

#include "stdio.h"

//////////////////////////////////////PUBLIC ROBOT DEFINES/////////////////////////////////////////
#define		SECURITY_PERIMETER			30//15cm

#define		NONE			0U
#define		LEFT			1U
#define		RIGHT			2U
#define		FORWARD			3U
#define		BACKWARD		4U

//-----------------------------------------------------------------------------------------------//

////////////////////////////////////////PUBLIC FREQUENCE OSC///////////////////////////////////////
#define		CONF_FOSC_HZ				16000000U
//-----------------------------------------------------------------------------------------------//

////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_100MS		1U
#define		CONF_EVENT_TIMER_1S			2U
#define		CONF_EVENT_UART_MSG_RCV		4U
#define		CONF_EVENT_US_ALARM_PROX	8U

/////////////////////////////////////////////PUBLIC ADC///////////////////////////////////////////
#define		CONF_ADC_LDR_GAUCHE		ADC_CHANNEL_2
#define		CONF_ADC_LDR_DROITE		ADC_CHANNEL_3

//----------------------------------------------------------------------------------------------//

/////////////////////////////////////////PUBLIC POWER MODULE//////////////////////////////////////
#define		CONF_CMD_ALIM_CAMERA	E_PORTB_PIN0_IO
#define		CONF_CMD_ALIM_ULTRASON	E_PORTB_PIN1_IO
#define		CONF_CMD_ALIM_LDR		E_PORTB_PIN2_IO
//----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC I2C///////////////////////////////////////////
#define		CONF_I2C_SCL			E_PORTC_PIN0_IO
#define		CONF_I2C_SDA			E_PORTC_PIN1_IO

#define		CONF_I2C_ULTRASON		0U
//------------
#define		CONF_I2C_NB				1U
//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC LEDS///////////////////////////////////////////
#define		CONF_INDEX_EYE_LEFT		0
#define		CONF_INDEX_EYE_RIGHT	1
#define		CONF_EYE_LEFT			E_PORTD_PIN4_IO
#define		CONF_EYE_RIGHT			E_PORTD_PIN5_IO
//------------
#define		CONF_LED_NB				2U
//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC TIMER///////////////////////////////////////////
#define		CONF_TIMER_LED			0U//TIMER_LED
#define		CONF_TIMER_US			1U//TIMER_ULTRASON
//------------	
#define		CONF_TIMER_NB			2U
//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC UART///////////////////////////////////////////
#define		CONF_UART_0_INDEX		0U//E_USART_0
//#define		CONF_UART_1_INDEX		1U//E_USART_1
//------------
#define		CONF_UART_NB			1U
//-----------------------------------------------------------------------------------------------//

#define E_PROTOCOLE_HEAD					0U

#define E_PROTOCOLE_WHO_US					0U
#define E_PROTOCOLE_WHO_CAMERA				1U
#define E_PROTOCOLE_WHO_LIGHT				2U
#define E_PROTOCOLE_WHO_EYES				3U

//E_PROTOCOLE_WHO_EYES
#define E_PROTOCOLE_CMD_LEFT_EYE_TOGGLE		1U
#define E_PROTOCOLE_CMD_RIGHT_EYE_TOGGLE	2U
#define E_PROTOCOLE_CMD_EYES_ON				3U
#define E_PROTOCOLE_CMD_EYES_OFF			4U
#define E_PROTOCOLE_CMD_EYES_TOGGLE			5U
#define E_PROTOCOLE_CMD_EYES_HEARBEAT		6U
#define E_PROTOCOLE_CMD_EYES_STATE			7U

//E_PROTOCOLE_WHO_US

//E_PROTOCOLE_WHO_CAMERA

//E_PROTOCOLE_WHO_LIGHT
#define E_PROTOCOLE_CMD_LEFT_LDR			0U
#define E_PROTOCOLE_CMD_RIGHT_LDR			1U

#endif /* CONF_HARD_H_ */

