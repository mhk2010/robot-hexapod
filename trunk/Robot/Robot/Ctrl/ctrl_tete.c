/*
 * ctrl_tete.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_tete.h"


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlTete( void ) 
{ 
	//on ajoute les ADCs
	DrvAdcEnableAdc( CONF_ADC_LDR_GAUCHE );
	DrvAdcEnableAdc( CONF_ADC_LDR_DROITE );
	DrvAddServo( CONF_SERVO_TETE_H , NEUTRE_TETE_HORIZONTAL );
	DrvAddServo( CONF_SERVO_TETE_V , NEUTRE_TETE_VERTICAL );
	
}
