/*
 * mic_timer_0.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "mic_timer_0.h"



/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the COM0A1:0: Compare Match Output A Mode
Boolean micTimer0CompareMatchOutputAMode( ETimer0CompareMatchOutputAMode mode ) 
{
	Boolean o_success = TRUE;
	TCCR0A = ( TCCR0A & ~( ( 1U << COM0A1 ) | ( 1U << COM0A0 ) ) ) |
             ( mode   &  ( ( 1U << COM0A1 ) | ( 1U << COM0A0 ) ) );
	return o_success;
}

//set the COM0B1:0: Compare Match Output B Mode
Boolean micTimer0CompareMatchOutputBMode( ETimer0CompareMatchOutputBMode mode ) 
{
	Boolean o_success = TRUE;
	TCCR0B = ( TCCR0B & ~( ( 1U << COM0B1 ) | ( 1U << COM0B0 ) ) ) |
             ( mode   &  ( ( 1U << COM0B1 ) | ( 1U << COM0B0 ) ) );
	return o_success;
}

//set the WGM01:0: Waveform Generation Mode
Boolean micTimer0WaveformGenerationMode( ETimer0GeneratorMode mode ) 
{
	Boolean o_success = TRUE;
	BIT_SET(TCCR0A , WGM00,( mode & ( 1U << WGM00 ) ) );
	BIT_SET(TCCR0A , WGM01,( mode & ( 1U << WGM01 ) ) >> 1U );
	BIT_SET(TCCR0B , WGM02,( mode & ( 1U << WGM02 ) ) >> 2U );
	
	return o_success;
}

//set the FOC0A: Force Output Compare A
Boolean micTimer0ForceOutputCompareA( ETimer0ForceCompare mode ) 
{
	Boolean o_success = TRUE;
	TCCR0B |= mode & ( ( 1U << FOC0B ) | ( 1U << FOC0A ) );
	return o_success;
}

//set the CS02:0: Clock Select
void micTimer0SetClockDivision( ETimer0Clock clock_div )
{
	TCCR0B = ( TCCR0B    & ~( ( 1U << CS02 ) | ( 1U << CS01 ) | ( 1U << CS00 ) ) ) |
             ( clock_div &  ( ( 1U << CS02 ) | ( 1U << CS01 ) | ( 1U << CS00 ) ) );
}

//set the TCNT0 Timer/Counter Register
void micTimer0SetTimerCounterRegister( Int8U tcnt0 )
{
	TCNT0 = tcnt0 ;
}

//Get the TCNT0 Timer/Counter Register
Int8U micTimer0GetTimerCounterRegister( void )
{
	return TCNT0 ;
}

//set the OCR0A Output Compare Register A
void micTimer0SetOutputCompareRegisterA( Int8U ocr0a )
{
	OCR0A = ocr0a ;
}

//Get the OCR0A Output Compare Register A
Int8U micTimer0GetOutputCompareRegisterA( void )
{
	return OCR0A ;
}

//set the OCR0A Output Compare Register B
void micTimer0SetOutputCompareRegisterB( Int8U ocr0b )
{
	OCR0B = ocr0b ;
}

//Get the OCR0A Output Compare Register B
Int8U micTimer0GetOutputCompareRegisterB( void )
{
	return OCR0B ;
}

//set the TIMSK0 Timer/Counter Interrupt Mask Register
void micTimer0SetTimerCounterInterrupt( ETimer0Interrupts it )
{
	TIMSK0 |= ( it & ( ( 1U << OCIE0B ) | ( 1U << OCIE0A ) | ( 1U << TOIE0 ) ) );
}

//Clear the TIMSK0 Timer/Counter Interrupt Unmask Register
void micTimer0ClearTimerCounterInterrupt( ETimer0Interrupts it )
{
	TIMSK0 &= ~ ( it & ( ( 1U << OCIE0B ) | ( 1U << OCIE0A ) | ( 1U << TOIE0 ) ) );
}

//Clear the TIFR0 Timer/Counter 0 Interrupt Flag Register
void micTimer0ClearTimerCounterInterruptFlagRegister( ETimer0Flags flag )
{
	TIMSK0 &= ~ ( flag & ( ( 1U << OCF0B ) | ( 1U << OCF0A ) | ( 1U << TOV0 ) ) );
}