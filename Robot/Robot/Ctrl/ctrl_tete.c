/*
 * ctrl_tete.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_tete.h"


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static head_member_t MaTete;

#define NB_SCAN_POSTION			11U
Int8U scan_position[ NB_SCAN_POSTION ] = {	NEUTRE_TETE_HORIZONTAL ,
											MIN_TETE_HORIZONTAL ,
											MIN_TETE_HORIZONTAL ,
											MIN_TETE_HORIZONTAL ,
											NEUTRE_TETE_HORIZONTAL ,
											NEUTRE_TETE_HORIZONTAL ,
											NEUTRE_TETE_HORIZONTAL ,
											MAX_TETE_HORIZONTAL ,
											MAX_TETE_HORIZONTAL ,
											MAX_TETE_HORIZONTAL ,
											NEUTRE_TETE_HORIZONTAL
										   };
Int8U index_scan_position = 0U;	




/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlTete( void ) 
{ 
	//on fixe les variables
	MaTete.is_scaning = FALSE;
	index_scan_position = 0U;
		
	//on ajoute les 2 servo a la tete
	MaTete.angle_h = NEUTRE_TETE_HORIZONTAL;
	MaTete.angle_v = NEUTRE_TETE_VERTICAL;
	DrvAddServo( CONF_SERVO_TETE_H , MaTete.angle_h );
	DrvAddServo( CONF_SERVO_TETE_V , MaTete.angle_v );
}

//dispatacher d'event
void CtrlTeteDispatcher( Event_t event )  
{
	if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_1S ))
	{	
		//si le scan est activé
		if( MaTete.is_scaning == TRUE )	
		{
			//on fait un balayage horizontal de la tete
			if (DrvServoMoveToPosition( CONF_SERVO_TETE_H_INDEX, scan_position[index_scan_position], E_SERVO_VITESSE_5) == TRUE)
			{
				index_scan_position++;
			}
			if(index_scan_position == NB_SCAN_POSTION)
			{
				//on a fini de scanner
				index_scan_position = 0U;
				MaTete.is_scaning = FALSE;
			}
		}
	}				
}	

//on start le scan de la tete
void CtrlTeteStartScan( void )
{
	index_scan_position = 0U;	
	MaTete.is_scaning = TRUE;
}

//on stop le scan de la tete
void CtrlTeteStopScan( void )
{
	MaTete.is_scaning = FALSE;
}	

//on recupere la structure
head_member_t* CtrlTeteGetStruct( void )
{
	return &MaTete;	
}

//on bouge la tete
void CtrlTeteMove( Int8U angle_tete_hor, Int8U angle_tete_ver, Int8U vitesse )
{
	MaTete.angle_h = angle_tete_hor;
	MaTete.angle_v = angle_tete_ver;
	DrvServoMoveToPosition( CONF_SERVO_TETE_H_INDEX, MaTete.angle_h, vitesse);		
	DrvServoMoveToPosition( CONF_SERVO_TETE_V_INDEX, MaTete.angle_v, vitesse);
}
	