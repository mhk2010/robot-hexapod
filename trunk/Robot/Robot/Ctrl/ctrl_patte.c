/*
 * ctrl_patte.c
 *
 * Created: 10/11/2011 11:29:20
 *  Author: berryer
 */ 

#include "ctrl_patte.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


static patte_t MesPattes[ NB_PATTES ];
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

 
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//init
void CtrlPatte( void ) 
{
	//on ajoute les servos pour chaques patte
	
	//avant gauche
	MesPattes[ AVANT_GAUCHE ].epaule.pin = CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE;
	MesPattes[ AVANT_GAUCHE ].epaule.index = CONF_SERVO_PATTE_AVANT_GAUCHE_EPAULE_INDEX;
	MesPattes[ AVANT_GAUCHE ].epaule.angle = NEUTRE_EPAULE_AVANT_GAUCHE;
	DrvAddServo( MesPattes[ AVANT_GAUCHE ].epaule.pin, MesPattes[ AVANT_GAUCHE ].epaule.angle );
		
	MesPattes[ AVANT_GAUCHE ].coude.pin = CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE;
	MesPattes[ AVANT_GAUCHE ].coude.index = CONF_SERVO_PATTE_AVANT_GAUCHE_COUDE_INDEX;
	MesPattes[ AVANT_GAUCHE ].coude.angle = NEUTRE_COUDE_AVANT_GAUCHE;
	DrvAddServo( MesPattes[ AVANT_GAUCHE ].coude.pin ,MesPattes[ AVANT_GAUCHE ].coude.angle );
					
	//milieu gauche
	MesPattes[ MILIEU_GAUCHE ].epaule.pin = CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE;
	MesPattes[ MILIEU_GAUCHE ].epaule.index = CONF_SERVO_PATTE_MILIEU_GAUCHE_EPAULE_INDEX;
	MesPattes[ MILIEU_GAUCHE ].epaule.angle = NEUTRE_EPAULE_MILIEU_GAUCHE;
	DrvAddServo( MesPattes[ MILIEU_GAUCHE ].epaule.pin ,MesPattes[ MILIEU_GAUCHE ].epaule.angle );
		
	MesPattes[ MILIEU_GAUCHE ].coude.pin = CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE;
	MesPattes[ MILIEU_GAUCHE ].coude.index = CONF_SERVO_PATTE_MILIEU_GAUCHE_COUDE_INDEX;
	MesPattes[ MILIEU_GAUCHE ].coude.angle = NEUTRE_COUDE_MILIEU_GAUCHE;
	DrvAddServo( MesPattes[ MILIEU_GAUCHE ].coude.pin ,MesPattes[ MILIEU_GAUCHE ].coude.angle );
	
	//arriere gauche
	MesPattes[ ARRIERE_GAUCHE ].epaule.pin = CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE;
	MesPattes[ ARRIERE_GAUCHE ].epaule.index = CONF_SERVO_PATTE_ARRIERE_GAUCHE_EPAULE_INDEX;
	MesPattes[ ARRIERE_GAUCHE ].epaule.angle = NEUTRE_EPAULE_MILIEU_GAUCHE;
	DrvAddServo( MesPattes[ ARRIERE_GAUCHE ].epaule.pin ,MesPattes[ ARRIERE_GAUCHE ].epaule.angle );
		
	MesPattes[ ARRIERE_GAUCHE ].coude.pin = CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE;
	MesPattes[ ARRIERE_GAUCHE ].coude.index = CONF_SERVO_PATTE_ARRIERE_GAUCHE_COUDE_INDEX;
	MesPattes[ ARRIERE_GAUCHE ].coude.angle = NEUTRE_COUDE_ARRIERE_GAUCHE;
	DrvAddServo( MesPattes[ ARRIERE_GAUCHE ].coude.pin ,MesPattes[ ARRIERE_GAUCHE ].coude.angle);
					
	//avant droite
	MesPattes[ AVANT_DROITE ].epaule.pin = CONF_SERVO_PATTE_AVANT_DROITE_EPAULE;
	MesPattes[ AVANT_DROITE ].epaule.index = CONF_SERVO_PATTE_AVANT_DROITE_EPAULE_INDEX;
	MesPattes[ AVANT_DROITE ].epaule.angle = NEUTRE_EPAULE_AVANT_DROITE;
	DrvAddServo( MesPattes[ AVANT_DROITE ].epaule.pin ,MesPattes[ AVANT_DROITE ].epaule.angle);
		
	MesPattes[ AVANT_DROITE ].coude.pin = CONF_SERVO_PATTE_AVANT_DROITE_COUDE;
	MesPattes[ AVANT_DROITE ].coude.index = CONF_SERVO_PATTE_AVANT_DROITE_COUDE_INDEX;
	MesPattes[ AVANT_DROITE ].coude.angle = NEUTRE_COUDE_AVANT_DROITE;
	DrvAddServo( MesPattes[ AVANT_DROITE ].coude.pin ,MesPattes[ AVANT_DROITE ].coude.angle );
					
	//milieu droite
	MesPattes[ MILIEU_DROITE ].epaule.pin = CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE;
	MesPattes[ MILIEU_DROITE ].epaule.index = CONF_SERVO_PATTE_MILIEU_DROITE_EPAULE_INDEX;
	MesPattes[ MILIEU_DROITE ].epaule.angle = NEUTRE_EPAULE_MILIEU_DROITE;
	DrvAddServo( MesPattes[ MILIEU_DROITE ].epaule.pin ,MesPattes[ MILIEU_DROITE ].epaule.angle );
		
	MesPattes[ MILIEU_DROITE ].coude.pin = CONF_SERVO_PATTE_MILIEU_DROITE_COUDE;
	MesPattes[ MILIEU_DROITE ].coude.index = CONF_SERVO_PATTE_MILIEU_DROITE_COUDE_INDEX;
	MesPattes[ MILIEU_DROITE ].coude.angle = NEUTRE_COUDE_MILIEU_DROITE;
	DrvAddServo( MesPattes[ MILIEU_DROITE ].coude.pin ,MesPattes[ MILIEU_DROITE ].coude.angle );
					
	//arriere droite
	MesPattes[ ARRIERE_DROITE ].epaule.pin = CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE;
	MesPattes[ ARRIERE_DROITE ].epaule.index = CONF_SERVO_PATTE_ARRIERE_DROITE_EPAULE_INDEX;
	MesPattes[ ARRIERE_DROITE ].epaule.angle = NEUTRE_EPAULE_MILIEU_DROITE;
	DrvAddServo( MesPattes[ ARRIERE_DROITE ].epaule.pin ,MesPattes[ ARRIERE_DROITE ].epaule.angle );
		
	MesPattes[ ARRIERE_DROITE ].coude.pin = CONF_SERVO_PATTE_ARRIERE_DROITE_COUDE;
	MesPattes[ ARRIERE_DROITE ].coude.index = CONF_SERVO_PATTE_ARRIERE_DROITE_COUDE_INDEX;
	MesPattes[ ARRIERE_DROITE ].coude.angle = NEUTRE_COUDE_ARRIERE_DROITE;
	DrvAddServo( MesPattes[ ARRIERE_DROITE ].coude.pin ,MesPattes[ ARRIERE_DROITE ].coude.angle );
		
}

//on bouge une patte
Boolean CtrlPatteMove( Int8U index, Int8U angle_epaule, Int8U angle_coude, EServoVitesse vitesse )
{
	Int8U ret = 0x00;
	MesPattes[ index ].epaule.angle = angle_epaule;
	MesPattes[ index ].coude.angle = angle_coude;
	
	if ( DrvServoMoveToPosition( MesPattes[ index ].epaule.index, MesPattes[ index ].epaule.angle, vitesse ) == TRUE )	
	{
		//si on a atteind la position
		ret = (1U << 0U);
	}
	//on deplace tjrs le coude a sa vitesse max
	if ( DrvServoMoveToPosition( MesPattes[ index ].coude.index, MesPattes[ index ].coude.angle, E_SERVO_VITESSE_5 ) == TRUE )	
	{
		//si on a atteind la position
		ret |= (1U << 1U);
	}
	
	if(ret == 0x03)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

//on bouge une patte direct sans attendre quel finisse son mouvement
Boolean CtrlPatteDirectMove( Int8U index, Int8U angle_epaule, Int8U angle_coude, EServoVitesse vitesse )
{
	Int8U ret = 0x00;
	MesPattes[ index ].epaule.angle = angle_epaule;
	MesPattes[ index ].coude.angle = angle_coude;
	
	if ( DrvServoDirectMoveToPosition( MesPattes[ index ].epaule.index, MesPattes[ index ].epaule.angle, vitesse ) == TRUE )	
	{
		//si on a atteind la position
		ret = (1U << 0U);
	}
	//on deplace tjrs le coude a sa vitesse max
	if ( DrvServoDirectMoveToPosition( MesPattes[ index ].coude.index, MesPattes[ index ].coude.angle, E_SERVO_VITESSE_5 ) == TRUE )	
	{
		//si on a atteind la position
		ret |= (1U << 1U);
	}
	
	if(ret == 0x03)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////



