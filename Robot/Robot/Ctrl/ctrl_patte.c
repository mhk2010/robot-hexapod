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
		{ CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE,		NEUTRE_EPAULE_AVANT_GAUCHE },
		{ CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE,		NEUTRE_COUDE_AVANT_GAUCHE },
	},	
	{
		{ CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE,	NEUTRE_EPAULE_MILIEU_GAUCHE},
		{ CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE,		NEUTRE_COUDE_MILIEU_GAUCHE },
	},	
	{
		{ CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE,	NEUTRE_EPAULE_ARRIERE_GAUCHE },
		{ CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE,	NEUTRE_COUDE_ARRIERE_GAUCHE },
	},	
	
	{
		{ CONF_SERVO_PATTE_AVANT_DROITE_EPAULE,		NEUTRE_EPAULE_AVANT_DROITE},
		{ CONF_SERVO_PATTE_AVANT_DROITE_COUDE,		NEUTRE_COUDE_AVANT_DROITE},
	},	
	{
		{ CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE,	NEUTRE_EPAULE_MILIEU_DROITE },
		{ CONF_SERVO_PATTE_MILIEU_DROITE_COUDE,		NEUTRE_COUDE_MILIEU_DROITE },
	},	
	{
		{ CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE,	NEUTRE_EPAULE_ARRIERE_DROITE },
		{ CONF_SERVO_PATTE_ARRIERE_DROITE_COUDE,	NEUTRE_COUDE_ARRIERE_DROITE },
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
		
		MesPattes[ loop ].coude.pin_servo = ConfPatte[ loop ].coude.pin_servo;
		MesPattes[ loop ].coude.angle = ConfPatte [ loop ].coude.angle;
		
		MesPattes[ loop ].speed = 0;
		
		DrvAddServo( MesPattes[ loop ].coude.pin_servo , MesPattes[ loop ].coude.angle );
		DrvAddServo( MesPattes[ loop ].epaule.pin_servo , MesPattes[ loop ].epaule.angle );
	}	
}



//on bouge une patte
void CtrlPatteMove( Int8U index, Int8U angle_epaule, Int8U angle_coude )
{
	MesPattes[ index ].epaule.angle = angle_epaule;
	MesPattes[ index ].coude.angle = angle_coude;
	DrvServoMoveToPosition( MesPattes[ index ].epaule.pin_servo, MesPattes[ index ].epaule.angle );		
	DrvServoMoveToPosition( MesPattes[ index ].coude.pin_servo, MesPattes[ index ].coude.angle);
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////



