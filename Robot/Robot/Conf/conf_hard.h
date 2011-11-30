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
#define		CONF_FOSC_HZ				8000000U
//-----------------------------------------------------------------------------------------------//


////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_10MS		0U
#define		CONF_EVENT_TIMER_100MS		1U
#define		CONF_EVENT_TIMER_1S			2U
#define		CONF_EVENT_UART_MSG_RCV		3U
#define		CONF_EVENT_MOVE_END			4U
#define		CONF_EVENT_FIND_MAX_LIGHT	5U
#define		CONF_EVENT_FRONT_OF_LIGHT	6U
#define		CONF_EVENT_FIND_NEAR_OBJECT	7U
#define		CONF_EVENT_FIND_NO_OBJECT	8U
#define		CONF_EVENT_FRONT_OF_OBJECT	9U
#define		CONF_EVENT_ACCEL			10U
#define		CONF_EVENT_BOUSSOLE_SENSOR	11U


//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC SERVO////////////////////////////////////////////
#define		CONF_SERVO_TETE_H							E_PORTB_PIN0_IO
#define		CONF_SERVO_TETE_V							E_PORTB_PIN1_IO

#define		CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE		E_PORTB_PIN2_IO
#define		CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE			E_PORTB_PIN3_IO

#define		CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE		E_PORTB_PIN4_IO
#define		CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE		E_PORTB_PIN5_IO

#define		CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE		E_PORTB_PIN6_IO
#define		CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE		E_PORTB_PIN7_IO

#define		CONF_SERVO_PATTE_AVANT_DROITE_EPAULE		E_PORTD_PIN2_IO
#define		CONF_SERVO_PATTE_AVANT_DROITE_COUDE			E_PORTD_PIN3_IO

#define		CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE		E_PORTD_PIN4_IO
#define		CONF_SERVO_PATTE_MILIEU_DROITE_COUDE		E_PORTD_PIN5_IO

#define		CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE		E_PORTD_PIN6_IO
#define		CONF_SERVO_PATTE_ARRIERE_DROITE_COUDE		E_PORTD_PIN7_IO

//------------
#define		CONF_SERVO_NB			14U
#define		CONF_SERVO_PATTES_NB	12U
#define		CONF_SERVO_TETE_NB		2U
//----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC ADC///////////////////////////////////////////
#define		CONF_ADC_IR				E_PORTA_PIN0_IO
#define		CONF_ADC_ACCEL_X		E_PORTA_PIN1_IO
#define		CONF_ADC_ACCEL_Y		E_PORTA_PIN2_IO
#define		CONF_ADC_ACCEL_Z		E_PORTA_PIN3_IO
#define		CONF_ADC_LDR_GAUCHE		E_PORTA_PIN4_IO
#define		CONF_ADC_LDR_DROITE		E_PORTA_PIN5_IO
//------------
#define		CONF_ADC_NB				6U
//----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC I2C///////////////////////////////////////////
#define		CONF_I2C_SCL				E_PORTC_PIN0_IO
#define		CONF_I2C_SDA				E_PORTC_PIN1_IO

#define		CONF_I2C_ULTRASON			0U
//------------
#define		CONF_I2C_NB					1U
//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC LEDS///////////////////////////////////////////
#define		CONF_LED_0_INDEX		0U
#define		CONF_LED_1_INDEX		1U
//------------	
#define		CONF_LED_NB				2U
//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC TIMER///////////////////////////////////////////
#define		CONF_TIMER_ADC				0U//TIMER_ADC
#define		CONF_TIMER_LED				1U//TIMER_LED
//------------	
#define		CONF_TIMER_NB				0U
//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////////////PUBLIC UART///////////////////////////////////////////
#define		CONF_UART_0_INDEX		0U//E_USART_0
//------------
#define		CONF_UART_NB			1U
//-----------------------------------------------------------------------------------------------//







#endif /* CONF_HARD_H_ */