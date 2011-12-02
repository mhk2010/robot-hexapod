/*
 * seq_proximity.c
 *
 * Created: 29/11/2011 16:10:55
 *  Author: berryer
 */ 
#include "seq_proximity.h"

/////////////////////////////////////////PRIVATE DEFINE//////////////////////////////////////////
#define OFFSET_DEPLACEMENT	10//1sec

/////////////////////////////////////////PRIVATE TYPEDEF//////////////////////////////////////////
typedef enum EESequencementObject
{
  E_SEQUENCE_FACE_OBJECT,
  E_SEQUENCE_FACE_OBJECT_IN_PROGRESS,
  E_SEQUENCE_FACE_OBJECT_NONE,
}ESequencementObject;

///////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
static ESequencementObject step_sequencement_object = E_SEQUENCE_FACE_OBJECT_NONE;
static tete_t *tete_object;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void SeqProximity( void ) 
{
	step_sequencement_object = E_SEQUENCE_FACE_OBJECT_NONE;
	tete_object = CtrlTeteGetStruct();
}

//on reagit aux evenements
void SeqProximityDispatcher ( Event_t event )
{
	//event 1 sec
		
	if ( DrvEventTestEvent(event, CONF_EVENT_FIND_NEAR_OBJECT ))
	{
		//on passe directement a l'etape de scan de proximité
		if( tete_object->position.angle_h < NEUTRE_TETE_HORIZONTAL )
		{
			//on test si on fait un mouvement de plus
			if( ( NEUTRE_TETE_HORIZONTAL - tete_object->position.angle_h ) > OFFSET_DEPLACEMENT )
			{				
				CtrlMarcheMoveStep( E_MOVE_RIGHT, E_SPEED_5 ) ;
			}
			else
			{
				step_sequencement_object = E_SEQUENCE_FACE_OBJECT_NONE;
				DrvEventAddEvent( CONF_EVENT_FRONT_OF_OBJECT );
			}	
		}
		else
		{	
			//on test si on fait un mouvement de plus
			if( ( tete_object->position.angle_h - NEUTRE_TETE_HORIZONTAL ) > OFFSET_DEPLACEMENT )
			{				
				CtrlMarcheMoveStep( E_MOVE_LEFT, E_SPEED_5 ) ;
			}
			else
			{
				//sinon on a fini
				step_sequencement_object = E_SEQUENCE_FACE_OBJECT_NONE;
				DrvEventAddEvent( CONF_EVENT_FRONT_OF_OBJECT );
			}	
		}
	}
	//quand le mouvement est fini
	if ( DrvEventTestEvent(event ,CONF_EVENT_MOVE_END ))
	{
		if(step_sequencement_object == E_SEQUENCE_FACE_OBJECT_IN_PROGRESS)
		{
			CtrlTeteStartScanProximity();
		}
	}	
}


//on lance la sequence de mouvement vers l'object
void SeqProximityStartScan( void ) 
{
	//on lance le scan de la lumiere
	CtrlTeteStartScanProximity();
	step_sequencement_object = E_SEQUENCE_FACE_OBJECT_IN_PROGRESS;
}

//on stop la sequence de mouvement vers l'object
void SeqProximityStopScan( void ) 
{
	step_sequencement_object = E_SEQUENCE_FACE_OBJECT_NONE;
}