/*
 * drv_timer.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_timer.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

//structure configuration initial des leds
typedef struct SSTimer
{
	volatile Boolean enable;
	volatile Int16U delay;
	volatile Int16U cpt_delay;
	volatile ETimerMode mode;
	ptrfct_Isr_Callback_Timer ptrfct;
} STimer ;

#define MACRO_NULL_TIMER {\
							.enable = FALSE,\
							.delay = 0,\
							.cpt_delay = 0,\
							.mode = E_TIMER_MODE_NONE,\
							.ptrfct = NULL,\
						}\

//configuration initial des leds
STimer MesTimer[ CONF_TIMER_NB ];


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
// fait tourner le timer 0 compA a 1 ms
void DrvTimerInitSystemTimer( void ) ;
//On calcule le registre OCR en fonction du temp souhaité
Int16U DrvTimerComputeOCR(Int32U us_time , ETimer0Clock *clock_div) ;
  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Timer 
void DrvTimer( void )
{
	//on configure les timers autre que le timer event
	for(Int8U loop_index = 0U; loop_index < CONF_TIMER_NB ; loop_index++ )
	{
		MesTimer[ loop_index ].enable = FALSE;
		MesTimer[ loop_index ].ptrfct = NULL;
	}		
	//on init le timer system a 1 ms
	DrvTimerInitSystemTimer();
}

	
//fct qui parametre le timer
void DrvTimerPlayTimer( Int8U index_timer, Int16U delay, ETimerMode mode, ptrfct_Isr_Callback_Timer ptrfct )
{
	MesTimer[ index_timer ].enable = TRUE;
	MesTimer[ index_timer ].delay = delay;
	MesTimer[ index_timer ].cpt_delay = 0U;
	MesTimer[ index_timer ].mode = mode;
	MesTimer[ index_timer ].ptrfct = ptrfct;
}

//fct qui met en pause le timer
void DrvTimerPauseTimer( Int8U index_timer )
{	
	MesTimer[ index_timer ].enable = FALSE;
}

//fct qui remet a zero les parametres du timer
void DrvTimerStopTimer( Int8U index_timer )
{	
	MesTimer[ index_timer ].enable    = FALSE;
	MesTimer[ index_timer ].delay     = 0U ;
	MesTimer[ index_timer ].cpt_delay = 0U;
	MesTimer[ index_timer ].mode      = E_TIMER_MODE_NONE;
	MesTimer[ index_timer ].ptrfct    = NULL;
}

//fct qui reseter le timer
void DrvTimerResetTimer( Int8U index_timer )
{
	MesTimer[ index_timer ].cpt_delay = 0U;	
}


//fct qui fixe un delay au timer
void DrvTimerDelayTimer( Int8U index_timer , Int16U delay)
{
	MesTimer[ index_timer ].cpt_delay = 0U;	
	MesTimer[ index_timer ].delay	  = delay;
}


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
// fait tourner le timer 0 compA a 1 ms
void DrvTimerInitSystemTimer( void )
{
	//timer system a la ms
	ETimer0Clock clock_div;
	Int8U ocr = DrvTimerComputeOCR( 1000U , &clock_div );
	micTimer0SetOutputCompareRegisterA( ocr );
    micTimer0SetClockDivision( clock_div ) ;
	micTimer0WaveformGenerationMode( TIMER_0_CLEAR_ON_COMPARE ); 
	micTimer0ClearTimerCounterInterruptFlagRegister( TIMER_0_COMPARE_A_FLAG );
	micTimer0SetTimerCounterInterrupt( TIMER_0_COMPARE_A_INTERRUPT );
	
}

//On calcule le registre OCR en fonction du temp souhaité
Int16U DrvTimerComputeOCR(Int32U us_time , ETimer0Clock *clock_div)
{  
	Int16U div;
	Int32U ocr;
	Int16U min_div;
	min_div = ( ( ( (CONF_FOSC_HZ / 1000UL ) * us_time ) + 255999UL ) / 256000UL );
	if(min_div >= 256)
	{
		div = 1024;
		*clock_div = TIMER_0_CLK_DIV_1024;
	}
	else if(min_div >= 128)
	{
		div = 256;
		*clock_div = TIMER_0_CLK_DIV_256;
	}
	else if(min_div >= 8)
	{
		div = 64;
		*clock_div = TIMER_0_CLK_DIV_64;
	}
	else if(min_div > 1)
	{
		div = 8;
		*clock_div = TIMER_0_CLK_DIV_8;
	}
	else
	{
		div = 1;
		*clock_div = TIMER_0_CLK_DIV_1;
	}
  
	ocr =  ( CONF_FOSC_HZ / (2 * div * ( 1000000 / us_time ) ) ) - 1;
	ocr *= 2;
	ocr += 2;
  
  return ocr;
 
}



/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//ISR timer system 1 ms
volatile Int8U timeout_ms =0;
volatile Int8U timeout_s =0;
volatile Int8U timeout_5s =0;
volatile Int8U timeout_10s =0;
ISR(TIMER0_COMPA_vect)
{
	//on gere l'evenement 100 ms
	timeout_ms++;
	if(timeout_ms == 100)
	{
		timeout_ms =0;
		DrvEventAddEvent( CONF_EVENT_TIMER_100MS );	
		//on gere l'evenement 1 s
		timeout_s++;
		if(timeout_s == 10)
		{
			timeout_s = 0;
			timeout_5s++;
			DrvEventAddEvent( CONF_EVENT_TIMER_1S );	
		}
		if(timeout_5s == 5)
		{
			timeout_5s = 0;
			timeout_10s++;
			DrvEventAddEvent( CONF_EVENT_TIMER_5S );	
		}
		if(timeout_10s == 2)
		{
			timeout_10s = 0;
			DrvEventAddEvent( CONF_EVENT_TIMER_10S );	
		}
	}
	else if( ( timeout_ms % 10 ) == 0)
	{
		DrvEventAddEvent( CONF_EVENT_TIMER_10MS );	
	}
	
	for(Int8U loop_index = 0U; loop_index < CONF_TIMER_NB ; loop_index++ )
	{
		//si le timer est activé
		if( MesTimer[ loop_index ].enable == TRUE )
		{
			//on incremente le compteur
			MesTimer[ loop_index ].cpt_delay++;
			
			//on test par rapport a la valeur utilisateur
			if(MesTimer[ loop_index ].cpt_delay == MesTimer[ loop_index ].delay )
			{
				if( MesTimer[ loop_index ].mode != E_TIMER_MODE_NONE )
				{
					//on remet a zero le compteur
					MesTimer[ loop_index ].cpt_delay = 0U;
					
					//on appelle la fonction
					if( MesTimer[ loop_index ].ptrfct != NULL )
					{
						MesTimer[ loop_index ].ptrfct();
					}
					//si on est en mode ONE SHOT 
					//on vient d'excecuter la fct
					if (MesTimer[ loop_index ].mode == E_TIMER_MODE_ONE_SHOT)
					{
						//on reinit le timer
						DrvTimerStopTimer( loop_index );
					}
				}
			}
		}			
	}
}