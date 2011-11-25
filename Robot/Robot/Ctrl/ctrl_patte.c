/*
 * ctrl_patte.c
 *
 * Created: 10/11/2011 11:29:20
 *  Author: berryer
 */ 

#include "ctrl_patte.h"

#define SPEED_PATTES			1 //(100ms)

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
conf_patte_t ConfPatte [ NB_PATTES ] = 
{
	{
		{ CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE,		NEUTRE_EPAULE_AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE,		FALSE, 0 },
		{ CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE,		NEUTRE_COUDE_AVANT_GAUCHE,		NEUTRE_COUDE_AVANT_GAUCHE,		FALSE, 0 },
	},	
	{
		{ CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE,	NEUTRE_EPAULE_MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE,	FALSE, 0 },
		{ CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE,		NEUTRE_COUDE_MILIEU_GAUCHE,		NEUTRE_COUDE_MILIEU_GAUCHE,		FALSE, 0 },
	},	
	{
		{ CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE,	NEUTRE_EPAULE_ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE,	FALSE, 0 },
		{ CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE,	NEUTRE_COUDE_ARRIERE_GAUCHE,	NEUTRE_COUDE_ARRIERE_GAUCHE,	FALSE, 0 },
	},	
	
	{
		{ CONF_SERVO_PATTE_AVANT_DROITE_EPAULE,		NEUTRE_EPAULE_AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE,		FALSE, 0 },
		{ CONF_SERVO_PATTE_AVANT_DROITE_COUDE,		NEUTRE_COUDE_AVANT_DROITE,		NEUTRE_COUDE_AVANT_DROITE,		FALSE, 0 },
	},	
	{
		{ CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE,	NEUTRE_EPAULE_MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE,	FALSE, 0 },
		{ CONF_SERVO_PATTE_MILIEU_DROITE_COUDE,		NEUTRE_COUDE_MILIEU_DROITE,		NEUTRE_COUDE_MILIEU_DROITE,		FALSE, 0 },
	},	
	{
		{ CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE,	NEUTRE_EPAULE_ARRIERE_DROITE,	NEUTRE_EPAULE_ARRIERE_DROITE,	FALSE, 0 },
		{ CONF_SERVO_PATTE_ARRIERE_DROITE_COUDE,	NEUTRE_COUDE_ARRIERE_DROITE,	NEUTRE_COUDE_ARRIERE_DROITE,	FALSE, 0 },
	},
	
};

static patte_t MesPattes[ NB_PATTES ];


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//on bouge les pattes
static void CtrlPatteDispatcherMove( void ) ;
 
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//init
void CtrlPatte( void ) 
{
	Int8U loop ;
	for( loop =0; loop < NB_PATTES ; loop++ )
	{
		MesPattes[ loop ].epaule.pin_servo = ConfPatte[ loop ].epaule.pin_servo;
		MesPattes[ loop ].epaule.angle = ConfPatte [ loop ].epaule.angle;
		MesPattes[ loop ].epaule.angle_consigne = ConfPatte[ loop ].epaule.angle_consigne;
		MesPattes[ loop ].epaule.move = FALSE;
		
		MesPattes[ loop ].coude.pin_servo = ConfPatte[ loop ].coude.pin_servo;
		MesPattes[ loop ].coude.angle = ConfPatte [ loop ].coude.angle;
		MesPattes[ loop ].coude.angle_consigne = ConfPatte[ loop ].coude.angle_consigne;
		MesPattes[ loop ].coude.move = FALSE;
		
		MesPattes[ loop ].speed = 0;
		
		DrvAddServo( MesPattes[ loop ].coude.pin_servo , MesPattes[ loop ].coude.angle );
		DrvAddServo( MesPattes[ loop ].epaule.pin_servo , MesPattes[ loop ].epaule.angle );
	}	
}

//dispatcher
void CtrlPatteDispatcher( Event_t event ) 
{
	if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_100MS ))
	{
		CtrlPatteDispatcherMove();
	}
}

//on bouge une patte
void CtrlPatteMove( Int8U index, Int8U angle_epaule, Int8U angle_coude )
{
	MesPattes[ index ].epaule.angle_consigne = angle_epaule;
	MesPattes[ index ].epaule.move = TRUE ;
	MesPattes[ index ].coude.angle_consigne = angle_coude;
	MesPattes[ index ].coude.move = TRUE ;
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////



//on bouge les pattes
static void CtrlPatteDispatcherMove( void )
{
	for( Int8U loop = 0; loop < NB_PATTES ; loop++)
	{
		//si la patte est en mouvement bouge
		if ( ( MesPattes[ loop ].coude.move == TRUE ) || ( MesPattes[ loop ].epaule.move == TRUE ) )
		{
			//si on a atteind la limite de temps pour le servo
			if( MesPattes[ loop ].speed  >= SPEED_PATTES )
			{
				if ( MesPattes[ loop ].coude.move == TRUE )
				{
					DrvServoMoveToPosition( MesPattes[ loop ].coude.pin_servo, MesPattes[ loop ].coude.angle_consigne );
					MesPattes[ loop ].coude.move = FALSE ;
					MesPattes[ loop ].speed = 0;
				}
				if ( MesPattes[ loop ].epaule.move == TRUE )
				{
					DrvServoMoveToPosition( MesPattes[ loop ].epaule.pin_servo, MesPattes[ loop ].epaule.angle_consigne );
					MesPattes[ loop ].epaule.move = FALSE ;
					MesPattes[ loop ].speed = 0;
				}
			}
			else
			{
				MesPattes[ loop ].speed++;
			}
		}	
	}
}	



