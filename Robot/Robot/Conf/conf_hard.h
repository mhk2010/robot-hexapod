/*
 * conf_hard.h
 *
 * Created: 12/07/2011 18:18:08
 *  Author: berryer
 */ 


#ifndef CONF_HARD_H_
#define CONF_HARD_H_

//////////////////////////////////////PUBLIC ROBOT DEFINES/////////////////////////////////////////
#define		SECURITY_PERIMETER			30//30cm
//-----------------------------------------------------------------------------------------------//

////////////////////////////////////////PUBLIC FREQUENCE OSC///////////////////////////////////////
#define		CONF_FOSC_HZ				16000000U
//-----------------------------------------------------------------------------------------------//


////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_10MS		0U
#define		CONF_EVENT_TIMER_100MS		CONF_EVENT_TIMER_10MS	+ 1U
#define		CONF_EVENT_TIMER_1S			CONF_EVENT_TIMER_100MS	+ 1U
#define		CONF_EVENT_TIMER_5S			CONF_EVENT_TIMER_1S		+ 1U
#define		CONF_EVENT_TIMER_10S		CONF_EVENT_TIMER_5S		+ 1U
#define		CONF_EVENT_DIGI_MSG_RCV		CONF_EVENT_TIMER_10S	+ 1U
#define		CONF_EVENT_HEAD_MSG_RCV		CONF_EVENT_DIGI_MSG_RCV + 1U
#define		CONF_EVENT_ALERT_US_PROX	CONF_EVENT_HEAD_MSG_RCV + 1U
#define		CONF_EVENT_ALERT_LIGHT		CONF_EVENT_ALERT_US_PROX + 1U


//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC SERVO////////////////////////////////////////////
#define		CONF_SERVO_TETE_H							E_PORTB_PIN0_IO
#define		CONF_SERVO_TETE_V							E_PORTB_PIN1_IO

#define		CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE		E_PORTB_PIN2_IO
#define		CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE			E_PORTB_PIN3_IO

#define		CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE		E_PORTB_PIN5_IO
#define		CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE		E_PORTB_PIN4_IO

#define		CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE		E_PORTB_PIN7_IO
#define		CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE		E_PORTB_PIN6_IO

#define		CONF_SERVO_PATTE_AVANT_DROITE_EPAULE		E_PORTC_PIN6_IO
#define		CONF_SERVO_PATTE_AVANT_DROITE_COUDE			E_PORTC_PIN7_IO

#define		CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE		E_PORTD_PIN6_IO
#define		CONF_SERVO_PATTE_MILIEU_DROITE_COUDE		E_PORTD_PIN7_IO

#define		CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE		E_PORTD_PIN4_IO
#define		CONF_SERVO_PATTE_ARRIERE_DROITE_COUDE		E_PORTD_PIN5_IO

#define		CONF_SERVO_TETE_H_INDEX																			0U
#define		CONF_SERVO_TETE_V_INDEX							CONF_SERVO_TETE_H_INDEX							+ 1U
#define		CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE_INDEX		CONF_SERVO_TETE_V_INDEX							+ 1U
#define		CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE_INDEX		CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE_INDEX		CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE_INDEX		CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE_INDEX	CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE_INDEX		CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE_INDEX	+ 1U
#define		CONF_SERVO_PATTE_AVANT_DROITE_EPAULE_INDEX		CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_AVANT_DROITE_COUDE_INDEX		CONF_SERVO_PATTE_AVANT_DROITE_EPAULE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE_INDEX		CONF_SERVO_PATTE_AVANT_DROITE_COUDE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_MILIEU_DROITE_COUDE_INDEX		CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE_INDEX	CONF_SERVO_PATTE_MILIEU_DROITE_COUDE_INDEX		+ 1U
#define		CONF_SERVO_PATTE_ARRIERE_DROITE_COUDE_INDEX		CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE_INDEX	+ 1U


//------------
#define		CONF_SERVO_NB			14U
//----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC LEDS///////////////////////////////////////////
#define		CONF_LED_ACTIVITY		0U
#define		CONF_LED_HEARTBEAT		CONF_LED_ACTIVITY	+ 1U
#define		CONF_LED_RX_HEAD		CONF_LED_HEARTBEAT	+ 1U
#define		CONF_LED_RX_DIGI		CONF_LED_RX_HEAD	+ 1U

#define		CONF_LED_0_INDEX		E_PORTA_PIN7_IO 
#define		CONF_LED_1_INDEX		E_PORTA_PIN6_IO 
#define		CONF_LED_2_INDEX		E_PORTC_PIN0_IO 
#define		CONF_LED_3_INDEX		E_PORTC_PIN1_IO 
//------------
#define		CONF_LED_NB				4U
//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC TIMER///////////////////////////////////////////
#define		CONF_TIMER_ADC				0U//TIMER_ADC
#define		CONF_TIMER_LED				1U//TIMER_LED
//------------	
#define		CONF_TIMER_NB				0U
//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC UART///////////////////////////////////////////
#define		CONF_UART_0_INDEX		0U//E_USART_0
#define		CONF_UART_0_RX_PIN		E_PORTD_PIN0_IO
#define		CONF_UART_0_TX_PIN		E_PORTD_PIN1_IO
#define		CONF_UART_1_INDEX		1U//E_USART_1
#define		CONF_UART_1_RX_PIN		E_PORTD_PIN2_IO
#define		CONF_UART_1_TX_PIN		E_PORTD_PIN3_IO
//------------
#define		CONF_UART_NB			2U
//-----------------------------------------------------------------------------------------------//







#endif /* CONF_HARD_H_ */