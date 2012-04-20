/*
 * ctrl_microphone.c
 *
 * Created: 16/11/2011 12:07:43
 *  Author: berryer
 */ 

#include "ctrl_microphone.h"


///////////////////////////////////////////PRIVATE DEFINES/////////////////////////////////////////
#define NB_SAMPLES 10000U

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
// variables definissant le niveau sonore
static Int32U nb_samples = 0;
static Int16U left_sound_level = 0x0000U;
static Int16U right_sound_level = 0x0000U;
static Int32U left_level ;
static Int32U right_level;


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlMicrophone( void ) 
{	
	//on active les deux canaux adc
	DrvAdcEnableAdc(CONF_ADC_MICRO_LEFT);
	DrvAdcEnableAdc(CONF_ADC_MICRO_RIGHT);	
}


//dispatcher
void CtrlMicrophoneDispatcher( Event_t event ) 
{
	//si on a un message valide
	if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_1S ))
	{	
		//CtrlMicrophoneSendUartMesureLevelSide();
		
	}
	else
	{	
		left_sound_level = DrvAdcReadChannel(CONF_ADC_MICRO_LEFT) ;
		right_sound_level =  DrvAdcReadChannel(CONF_ADC_MICRO_RIGHT);
		//on sample boucle main
		if( nb_samples < NB_SAMPLES) 
		{
			left_level += left_sound_level - 3 ;
			right_level += right_sound_level + 3 ;
			nb_samples++;
		}
		else
		{	
			nb_samples = 0U;
			right_level /= 10000;
			left_level /= 10000;
			//on regarde le cote qui a le plus decouvert des sons
			/*if (right_level > left_level)
			{
				CtrlEyeRightBlink(1);
			}
			else
			{
				CtrlEyeLeftBlink(1);
			}*/
			//CtrlMicrophoneSendUartMesureLevelSide();
			//on raz les vars
			right_level = 0;
			left_level = 0;
		}	
	}		
}



//retourne sur l'uart la mesure la plus forte
Int8U CtrlMicrophoneSendUartMesureLevelSide( void ) 
{
	Int8U buffer[30];
	Int8U nb_char=0;
	//Int8U bufferright [30];
	//Int8U nb_charright;
	nb_char=sprintf (buffer, "*0*1#%d#*2#%d##", (Int16U)left_level,(Int16U)right_level);

	DrvUartDirectSendBytes(CONF_UART_0_INDEX,(const Int8U*)buffer,nb_char);
	//DrvUartDirectSendBytes(CONF_UART_0_INDEX,(const Int8U*)buffer,nb_char);
}


