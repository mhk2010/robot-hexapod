/*
 * seq_light.c
 *
 * Created: 29/11/2011 15:48:27
 *  Author: berryer
 */ 
#include "seq_light.h"

/////////////////////////////////////////PRIVATE DEFINE//////////////////////////////////////////
#define OFFSET_DEPLACEMENT	10//1sec

/////////////////////////////////////////PRIVATE TYPEDEF//////////////////////////////////////////
typedef enum EESequencementLight
{
  E_SEQUENCE_LIGHT_FACE_LUMIERE,
  E_SEQUENCE_LIGHT_FOLLOW_LIGHT,
  E_SEQUENCE_LIGHT_NONE,
}ESequencementLight;

///////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
static ESequencementLight step_sequencement_lumiere = E_SEQUENCE_LIGHT_NONE;
static tete_t *tete_light;
static Boolean face_lumiere = FALSE;
static Boolean timeout_seq_light = 0;
static Int16U old_position = 0;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void SeqLight( void ) 
{
	step_sequencement_lumiere = E_SEQUENCE_LIGHT_NONE;
	old_position = 0;
	timeout_seq_light = 0;
	face_lumiere = FALSE;
	tete_light = CtrlTeteGetStruct();
}

//on reagit aux evenements
void SeqLightDispatcher ( Event_t event )
{
	//event 1s
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
		//on est face a la lumiere
		if( step_sequencement_lumiere == E_SEQUENCE_LIGHT_FACE_LUMIERE )
		{
			if(face_lumiere != FALSE)
			{
				timeout_seq_light++;
				if(timeout_seq_light == 2)
				{
					//on envoie l'event 
					DrvEventAddEvent( CONF_EVENT_SEQ_LIGHT_END );	
					face_lumiere = FALSE;
					timeout_seq_light = 0;
				}
			}
		}
		//la lumiere ne bouge plus
		else if( step_sequencement_lumiere == E_SEQUENCE_LIGHT_FOLLOW_LIGHT )
		{
			if( tete_light->position.angle_h == old_position )
			{
				//on envoie l'event 
				DrvEventAddEvent( CONF_EVENT_SEQ_LIGHT_END );	
			}
			else
			{
				old_position = tete_light->position.angle_h;
			}
		}
	}
	
	//event lumiere maximum trouv�
	if ( DrvEventTestEvent(event, CONF_EVENT_FIND_MAX_LIGHT ))
	{
		if( step_sequencement_lumiere == E_SEQUENCE_LIGHT_FACE_LUMIERE )
		{
			Boolean success = FALSE;
			//on passe directement a l'etape de scan de proximit�
			if( tete_light->light_angle < NEUTRE_TETE_HORIZONTAL )
			{
				//on test si on fait un mouvement de plus
				if(( NEUTRE_TETE_HORIZONTAL - tete_light->light_angle ) > OFFSET_DEPLACEMENT )
				{				
					CtrlMarcheMoveStep( E_MOVE_RIGHT, E_SPEED_3 ) ;
				}
				else
				{
					success = TRUE;
				}	
			}
			else
			{	
				//on test si on fait un mouvement de plus
				if(( tete_light->light_angle - NEUTRE_TETE_HORIZONTAL ) > OFFSET_DEPLACEMENT )
				{				
					CtrlMarcheMoveStep( E_MOVE_LEFT, E_SPEED_3 ) ;
				}
				else
				{
					success = TRUE;
				}	
			}
			//on est face a la lumiere
			if( success == TRUE )
			{
				//on avance
				CtrlMarcheMoveStep( E_MOVE_FORWORD, E_SPEED_3 ) ;
				face_lumiere = TRUE;
			}
		}		
	}
	//quand le mouvement est fini
	if ( DrvEventTestEvent(event ,CONF_EVENT_MOVE_END ))
	{
		if(step_sequencement_lumiere == E_SEQUENCE_LIGHT_FACE_LUMIERE)
		{
			CtrlTeteStartScanLight();
		}
	}	
}


//on lance la sequence de mouvement de la lumiere
void SeqLightStartFollowLight( void ) 
{
	//on lance le scan de la lumiere
	CtrlTeteStartFollowLight();
	step_sequencement_lumiere = E_SEQUENCE_LIGHT_FOLLOW_LIGHT;
}

//on lance la sequence de mouvement de la lumiere
void SeqLightStartScan( void ) 
{
	//on lance le scan de la lumiere
	CtrlTeteStartScanLight();
	step_sequencement_lumiere = E_SEQUENCE_LIGHT_FACE_LUMIERE;
}

//on stop la sequence de mouvement de la lumiere
void SeqLightStop( void ) 
{
	step_sequencement_lumiere = E_SEQUENCE_LIGHT_NONE;
}