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
  E_SEQUENCE_FACE_LUMIERE,
  E_SEQUENCE_FACE_LUMIERE_IN_PROGRESS,
  E_SEQUENCE_FACE_LUMIERE_NONE,
}ESequencementLight;

///////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
static ESequencementLight step_sequencement_lumiere = E_SEQUENCE_FACE_LUMIERE_NONE;
static tete_t *tete_light;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void SeqLight( void ) 
{
	step_sequencement_lumiere = E_SEQUENCE_FACE_LUMIERE_NONE;
	tete_light = CtrlTeteGetStruct();
}

//on reagit aux evenements
void SeqLightDispatcher ( Event_t event )
{
	//event 1 sec
	if ( DrvEventTestEvent(event, CONF_EVENT_FIND_MAX_LIGHT ))
	{
		//on passe directement a l'etape de scan de proximité
		if( tete_light->light_angle < NEUTRE_TETE_HORIZONTAL )
		{
			//on test si on fait un mouvement de plus
			if(( NEUTRE_TETE_HORIZONTAL - tete_light->light_angle ) > OFFSET_DEPLACEMENT )
			{				
				CtrlMarcheMoveStep( E_MOVE_RIGHT, E_SPEED_3 ) ;
			}
			else
			{
				step_sequencement_lumiere = E_SEQUENCE_FACE_LUMIERE_NONE;
				DrvEventAddEvent( CONF_EVENT_FRONT_OF_LIGHT );
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
				//sinon on a fini
				step_sequencement_lumiere = E_SEQUENCE_FACE_LUMIERE_NONE;
				DrvEventAddEvent( CONF_EVENT_FRONT_OF_LIGHT );
			}	
		}
	}
	//quand le mouvement est fini
	if ( DrvEventTestEvent(event ,CONF_EVENT_MOVE_END ))
	{
		if(step_sequencement_lumiere == E_SEQUENCE_FACE_LUMIERE_IN_PROGRESS)
		{
			CtrlTeteStartScanLight();
		}
	}	
}


//on lance la sequence de mouvement de la lumiere
void SeqLightStartScan( void ) 
{
	//on lance le scan de la lumiere
	CtrlTeteStartScanLight();
	step_sequencement_lumiere = E_SEQUENCE_FACE_LUMIERE_IN_PROGRESS;
}

//on stop la sequence de mouvement de la lumiere
void SeqLightStopScan( void ) 
{
	step_sequencement_lumiere = E_SEQUENCE_FACE_LUMIERE_NONE;
}