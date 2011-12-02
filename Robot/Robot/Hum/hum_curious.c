/*
 * hum_curious.c
 *
 * Created: 01/12/2011 19:00:58
 *  Author: louis
 */ 
#include "hum_curious.h"


/////////////////////////////////////////PRIVATES TYPEDEF/////////////////////////////////////////
typedef enum EESeqRobot
{
  E_SEQUENCE_ROBOT_PROXIMITY,
  E_SEQUENCE_ROBOT_GO_TO_FRONT_OF_LIGHT,
  E_SEQUENCE_ROBOT_HEAD_FOLLOW_LIGHT,
  E_SEQUENCE_ROBOT_NONE,
}ESeqRobot;

/////////////////////////////////////////PRIVATES VARIABLES/////////////////////////////////////////
//sequence dans l'humeur
static ESeqRobot seq;
//sequence dans l'humeur
static Boolean repeat_seq;
//timeout
static Int8U timeout_hum_using = 0;

/////////////////////////////////////////PRIVATES FUNCTIONS/////////////////////////////////////////
//choisi une sequence aleatoire
static void HumCuriousLaunchRandomSeq( void );

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
void HumCuriousInit( Boolean repeat ) 
{
	repeat_seq = repeat;
	HumCuriousLaunchRandomSeq();
	timeout_hum_using = 0;
}

///////////////////////////////////////////////////////////////////////////////
void HumCuriousDispatcher ( Event_t event ) 
{
	
	//dispatcher de sequnces
	if(( seq == E_SEQUENCE_ROBOT_GO_TO_FRONT_OF_LIGHT ) ||
		( seq == E_SEQUENCE_ROBOT_HEAD_FOLLOW_LIGHT))
	{
		SeqLightDispatcher(event);
	}
	else if( seq == E_SEQUENCE_ROBOT_PROXIMITY )
	{
		SeqProximityDispatcher(event);
	}
	
	
	//fin seq front of light
	//fin seq proximity
	if	(
			( DrvEventTestEvent(event, CONF_EVENT_SEQ_LIGHT_END )) ||
			( DrvEventTestEvent(event, CONF_EVENT_FRONT_OF_OBJECT ))
		)
	{
		//si on repete ou non la sequence
		if( repeat_seq == FALSE )
		{
			seq = E_SEQUENCE_ROBOT_NONE;
		}
		else
		{
			CtrlMarcheMove( E_MOVE_STOP, E_SPEED_0 );
			CtrlTeteScanProximityAngle(NEUTRE_TETE_HORIZONTAL);
			HumCuriousLaunchRandomSeq();
		}
	}
	
		
	
	
	
	
	
}

/////////////////////////////////////////PRIVATES FUNCTIONS/////////////////////////////////////////
//choisi une sequence aleatoire
static void HumCuriousLaunchRandomSeq( void )
{
	seq = (ESeqRobot)(RAND() % E_SEQUENCE_ROBOT_NONE);
	if(seq == E_SEQUENCE_ROBOT_GO_TO_FRONT_OF_LIGHT )
	{
		SeqLightStartScan();
	}
	else if(seq == E_SEQUENCE_ROBOT_HEAD_FOLLOW_LIGHT )
	{
		SeqLightStartFollowLight();
	}
	else if(seq == E_SEQUENCE_ROBOT_PROXIMITY )
	{
		SeqProximityStartScan();
	}
}