/*
 * ctrl_light.c
 *
 * Created: 12/12/2011 19:26:48
 *  Author: louis
 */ 

#include "Ctrl/ctrl_light.h"
#include "Drv/drv_adc.h"
#include "Drv/drv_uart.h"

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

Int16U mesure_ldr_gauche = 0U;
Int16U mesure_ldr_droite = 0U;
Int16U mesure_ldr_gauche_moy = 0U;
Int16U mesure_ldr_droite_moy = 0U;
Int16U nb_ldr_mesures =0U;
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlLight( void ) 
{
	nb_ldr_mesures = 0U;
	mesure_ldr_gauche = 0U;
	mesure_ldr_droite = 0U;
	mesure_ldr_gauche_moy = 0U;
	mesure_ldr_droite_moy = 0U;
}

//dispatcher
void CtrlLightDispatcher( Event_t event )  
{
	if ( DrvEventTestEvent( event, CONF_EVENT_TIMER_100MS ))
	{	
		//on lance la convertion 
		mesure_ldr_gauche += DrvAdcReadChannel( CONF_ADC_LDR_GAUCHE );
		//on lance la convertion 
		mesure_ldr_droite += DrvAdcReadChannel( CONF_ADC_LDR_DROITE );			
		
		nb_ldr_mesures++;
		if(nb_ldr_mesures == 8)
		{
			nb_ldr_mesures = 0;
			//on divise par 8
			mesure_ldr_gauche_moy = mesure_ldr_gauche >> 3;
			mesure_ldr_droite_moy = mesure_ldr_droite >> 3;
			mesure_ldr_gauche = 0;
			mesure_ldr_droite = 0;
			//CtrlLightSendUartLightMesure();			
		}
	}		
}


//permet d'envoyer sur l'uart 
void CtrlLightSendUartLightMesure( void ) 
{
	Char buffer[9U];
	
	buffer[0U] = '*';
	buffer[1U] = E_PROTOCOLE_HEAD;
	buffer[2U] = E_PROTOCOLE_WHO_LIGHT;
	buffer[3U] = mesure_ldr_gauche_moy>>8U;
	buffer[4U] = mesure_ldr_gauche_moy;
	buffer[5U] = mesure_ldr_droite_moy>>8U;
	buffer[6U] = mesure_ldr_droite_moy;
	buffer[7U] = '#';
	buffer[8U] = '#';
	DrvUartDirectSendBytes(CONF_UART_0_INDEX,(Int8U*)buffer,9U);
}