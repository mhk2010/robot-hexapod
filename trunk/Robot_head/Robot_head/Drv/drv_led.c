/*
 * drv_led.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_led.h"
#include "drv_timer.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//structure privee des leds
typedef struct SSled
{
	EIoPin pin_name;
	EIoLevel active_level;
	ELedState init_state;
	ELedState actual_state;
	Boolean flash_active;
	Int16U time_on;
	Int16U cpt_time_on;
	Int16U time_off;
	Int16U cpt_time_off;
	Int8U  nb_flash;
	Int8U  cpt_nb_flash;
} SLed ;

//configuration initial des leds
SLed MesLeds[ CONF_LED_NB ];

//Pin name
EIoPin led_pin_name[ CONF_LED_NB ] = {CONF_EYE_LEFT, CONF_EYE_RIGHT};
	
  
//ISR de flash de la led
static void DrvLedFlash_ISR( void );

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv LED 
void DrvLed ( void )
{
	//on met le timer pour la fonction flash des leds
	DrvTimerPlayTimer( CONF_TIMER_LED, 1, E_TIMER_MODE_PERIODIC, DrvLedFlash_ISR );
	//on configure chaque LED
	for (Int8U loop_led = 0 ; loop_led < CONF_LED_NB ; loop_led++)
	{
		MesLeds[ loop_led ].pin_name		= led_pin_name[ loop_led ];
		MesLeds[ loop_led ].active_level	= IO_LEVEL_VCC;
		MesLeds[ loop_led ].init_state		= STATE_LED_OFF;
		MesLeds[ loop_led ].actual_state	= STATE_LED_OFF;
		MesLeds[ loop_led ].flash_active	= FALSE;
		MesLeds[ loop_led ].time_on			= 0U;
		MesLeds[ loop_led ].cpt_time_on		= 0U;
		MesLeds[ loop_led ].time_off		= 0U;
		MesLeds[ loop_led ].cpt_time_off	= 0U;
		MesLeds[ loop_led ].nb_flash		= 0U;
		MesLeds[ loop_led ].cpt_nb_flash	= 0U;
		
		//on configure l'IO en sortie
		micIoPortsConfigureOutput(MesLeds[ loop_led ].pin_name);
		//on init l'etat initial de la led
		if( MesLeds[ loop_led ].init_state == STATE_LED_ON )
		{
			DrvLedOn( loop_led );
		}
		else
		{
			DrvLedOff( loop_led );
		}
	}
	
}

// Allume la led
void DrvLedOn ( Int8U led_name )
{
	if( MesLeds[ led_name ].active_level == IO_LEVEL_VCC )
	{
		micIoPortsConfigureToHighLevel(MesLeds[ led_name ].pin_name);
	}
	else
	{
		micIoPortsConfigureToLowLevel(MesLeds[ led_name ].pin_name);
	}	
}

// Etiends la led
void DrvLedOff ( Int8U led_name )
{
	if( MesLeds[ led_name ].active_level == IO_LEVEL_VCC )
	{
		micIoPortsConfigureToLowLevel(MesLeds[ led_name ].pin_name);
	}
	else
	{
		micIoPortsConfigureToHighLevel(MesLeds[ led_name ].pin_name);
	}	
}

// Toggle la led
void DrvLedToggle ( Int8U led_name )
{
	micIoPortsConfigureToToggleLevel(MesLeds[ led_name ].pin_name);
}

// Flash la led
void DrvLedFlash ( Int8U led_name, Int8U nb_flash, Int16U time_on, Int16U time_off )
{
	if(MesLeds[ led_name ].flash_active	!= TRUE)
	{
		MesLeds[ led_name ].time_on			= time_on;
		MesLeds[ led_name ].cpt_time_on		= 0U;
		MesLeds[ led_name ].time_off		= time_off;
		MesLeds[ led_name ].cpt_time_off	= 0U;
		MesLeds[ led_name ].nb_flash		= nb_flash;
		MesLeds[ led_name ].cpt_nb_flash	= 0U;
		MesLeds[ led_name ].flash_active	= TRUE;
	}
}

// Flash direct de la led
void DrvLedDirectFlash ( Int8U led_name, Int8U nb_flash, Int16U time_on, Int16U time_off )
{
	MesLeds[ led_name ].time_on			= time_on;
	MesLeds[ led_name ].cpt_time_on		= 0U;
	MesLeds[ led_name ].time_off		= time_off;
	MesLeds[ led_name ].cpt_time_off	= 0U;
	MesLeds[ led_name ].nb_flash		= nb_flash;
	MesLeds[ led_name ].cpt_nb_flash	= 0U;
	MesLeds[ led_name ].flash_active	= TRUE;
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////



/////////////////////////////////////ISR PUBLIC FUNCTIONS////////////////////////////////////////
//ISR de flash de la led
static void DrvLedFlash_ISR( void )
{
	for (Int8U loop_index = 0U ; loop_index < CONF_LED_NB ; loop_index++ )
	{
		if( MesLeds[ loop_index ].flash_active == TRUE )
		{
			if(MesLeds[ loop_index ].cpt_nb_flash < MesLeds[ loop_index ].nb_flash)
			{
				//paire on allume
				if( MesLeds[ loop_index ].actual_state == STATE_LED_OFF )
				{
					MesLeds[ loop_index ].cpt_time_off++;
					if( MesLeds[ loop_index ].cpt_time_off == MesLeds[ loop_index ].time_off )
					{
						//fin de period de OFF on met a ON	
						DrvLedOn( loop_index );
						MesLeds[ loop_index ].actual_state = STATE_LED_ON;
						MesLeds[ loop_index ].cpt_time_off = 0;		
					}			
				}	
				//impaire on eteinds
				else
				{
					MesLeds[ loop_index ].cpt_time_on++;
					if( MesLeds[ loop_index ].cpt_time_on == MesLeds[ loop_index ].time_on )
					{
						//fin de period de ON on met a OFF	
						DrvLedOff( loop_index );
						MesLeds[ loop_index ].actual_state = STATE_LED_OFF;
						MesLeds[ loop_index ].cpt_time_on = 0;	
						//on incremente le nombre de flash a chaque passage a off
						MesLeds[ loop_index ].cpt_nb_flash++;
					}
				}
			}	
			//plus de flash a faire
			else
			{
				MesLeds[ loop_index ].flash_active	= FALSE;
				MesLeds[ loop_index ].time_on		= 0U;
				MesLeds[ loop_index ].cpt_time_on	= 0U;
				MesLeds[ loop_index ].time_off		= 0U;
				MesLeds[ loop_index ].cpt_time_off	= 0U;
				MesLeds[ loop_index ].nb_flash		= 0U;
				MesLeds[ loop_index ].cpt_nb_flash	= 0U;
			}
		}
	}
}