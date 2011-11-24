/*
 * mic_timer_0.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef MIC_TIMER_0_H_
#define MIC_TIMER_0_H_

#include "Tools/tools_typedefs.h"


/////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////
typedef enum EETimer0CompareMatchOutputAMode
{
  TIMER_0_OUTPUT_A_DISCONNECTED = ( (0U << COM0A1) | (0U << COM0A0) ),
  TIMER_0_OUTPUT_A_TOGGLE		= ( (0U << COM0A1) | (1U << COM0A0) ),
  TIMER_0_OUTPUT_A_CLEAR		= ( (1U << COM0A1) | (0U << COM0A0) ),
  TIMER_0_OUTPUT_A_SET			= ( (1U << COM0A1) | (1U << COM0A0) )
}ETimer0CompareMatchOutputAMode;

typedef enum EETimer0CompareMatchOutputBMode
{
  TIMER_0_OUTPUT_B_DISCONNECTED = ( (0U << COM0B1) | (0U << COM0B0) ),
  TIMER_0_OUTPUT_B_TOGGLE		= ( (0U << COM0B1) | (1U << COM0B0) ),
  TIMER_0_OUTPUT_B_CLEAR		= ( (1U << COM0B1) | (0U << COM0B0) ),
  TIMER_0_OUTPUT_B_SET			= ( (1U << COM0B1) | (1U << COM0B0) )
}ETimer0CompareMatchOutputBMode;

typedef enum EETimer0GeneratorMode
{
  TIMER_0_NORMAL_COMPARE		= ( (0U << WGM02) | (0U << WGM01) | (0U << WGM00) ),
  TIMER_0_PHASE_PWM_TOP_255		= ( (0U << WGM02) | (0U << WGM01) | (1U << WGM00) ),
  TIMER_0_CLEAR_ON_COMPARE		= ( (0U << WGM02) | (1U << WGM01) | (0U << WGM00) ),
  TIMER_0_FAST_PWM_TOP_255		= ( (0U << WGM02) | (1U << WGM01) | (1U << WGM00) ),
  TIMER_0_PHASE_PWM_TOP_OCRA	= ( (1U << WGM02) | (0U << WGM01) | (1U << WGM00) ),
  TIMER_0_FAST_PWM_TOP_OCRA		= ( (1U << WGM02) | (1U << WGM01) | (1U << WGM00) )
}ETimer0GeneratorMode;

typedef enum EETimer0ForceCompare
{
  TIMER_0_FORCE_COMPARE_A = ( 1U << FOC0A ),
  TIMER_0_FORCE_COMPARE_B = ( 1U << FOC0B )
}ETimer0ForceCompare;

typedef enum EETimer0Clock
{
  // Timer clock = stopped
  TIMER_0_NO_CLOCK			= ( (0U << CS02) | (0U << CS01) | (0U << CS00) ),
  TIMER_0_CLK_DIV_1			= ( (0U << CS02) | (0U << CS01) | (1U << CS00) ),
  TIMER_0_CLK_DIV_8			= ( (0U << CS02) | (1U << CS01) | (0U << CS00) ),
  TIMER_0_CLK_DIV_64		= ( (0U << CS02) | (1U << CS01) | (1U << CS00) ),
  TIMER_0_CLK_DIV_256		= ( (1U << CS02) | (0U << CS01) | (0U << CS00) ),
  TIMER_0_CLK_DIV_1024		= ( (1U << CS02) | (0U << CS01) | (1U << CS00) ),
  TIMER_0_CLK_T0_FALLING	= ( (1U << CS02) | (1U << CS01) | (0U << CS00) ),
  TIMER_0_CLK_T0_RISING		= ( (1U << CS02) | (1U << CS01) | (1U << CS00) )
}ETimer0Clock;

typedef enum EETimer0Interrupts
{
  TIMER_0_COMPARE_A_INTERRUPT = (1U << OCIE0A),
  TIMER_0_COMPARE_B_INTERRUPT = (1U << OCIE0B),
  TIMER_0_OVERFLOW_INTERRUPT  = (1U << TOIE0)
}ETimer0Interrupts;

typedef enum EETimer0Flags
{
  TIMER_0_COMPARE_A_FLAG = (1U << OCF0A),
  TIMER_0_COMPARE_B_FLAG = (1U << OCF0B),
  TIMER_0_OVERFLOW_FLAG  = (1U << TOV0)
}ETimer0Flags;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the COM0A1:0: Compare Match Output A Mode
Boolean micTimer0CompareMatchOutputAMode( ETimer0CompareMatchOutputAMode mode )  ;
//set the COM0B1:0: Compare Match Output B Mode
Boolean micTimer0CompareMatchOutputBMode( ETimer0CompareMatchOutputBMode mode )  ;
//set the WGM01:0: Waveform Generation Mode
Boolean micTimer0WaveformGenerationMode( ETimer0GeneratorMode mode )  ;
//set the FOC0A: Force Output Compare A
Boolean micTimer0ForceOutputCompareA( ETimer0ForceCompare mode )  ;
//set the CS02:0: Clock Select
void micTimer0SetClockDivision( ETimer0Clock clock_div ) ;
//set the TCNT0 Timer/Counter Register
void micTimer0SetTimerCounterRegister( Int8U tcnt0 ) ;
//Get the TCNT0 Timer/Counter Register
Int8U micTimer0GetTimerCounterRegister( void ) ;
//set the OCR0A Output Compare Register A
void micTimer0SetOutputCompareRegisterA( Int8U ocr0a ) ;
//Get the OCR0A Output Compare Register A
Int8U micTimer0GetOutputCompareRegisterA( void ) ;
//set the OCR0A Output Compare Register B
void micTimer0SetOutputCompareRegisterB( Int8U ocr0b ) ;
//Get the OCR0A Output Compare Register B
Int8U micTimer0GetOutputCompareRegisterB( void ) ;
//set the TIMSK0 Timer/Counter Interrupt Mask Register
void micTimer0SetTimerCounterInterrupt( ETimer0Interrupts it ) ;
//Clear the TIMSK0 Timer/Counter Interrupt Unmask Register
void micTimer0ClearTimerCounterInterrupt( ETimer0Interrupts it ) ;
//Clear the TIFR0 Timer/Counter 0 Interrupt Flag Register
void micTimer0ClearTimerCounterInterruptFlagRegister( ETimer0Flags flag ) ;

#endif /* MIC_TIMER_0_H_ */