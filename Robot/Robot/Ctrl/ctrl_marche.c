/*
 * ctrl_marche.c
 *
 * Created: 15/11/2011 17:08:52
 *  Author: berryer
 */ 

#include "ctrl_marche.h"
#include "ctrl_patte.h"
#include "ctrl_tete.h"


//variable du step actuel dans la sequence
static Int8U step = 0U;

//on lance la sequence propre au mouvement
static EMove old_move = E_MOVE_NONE;

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CtrlMarcheSequence( void ) ;
static void CtrlMarcheSequenceForward( void ) ;
static void CtrlMarcheSequenceBackward( void ) ;
static void CtrlMarcheSequenceLeft( void ) ;
static void CtrlMarcheSequenceRight( void ) ;

static Boolean CtrlMarcheSequenceSitDown( void ) ;
static Boolean CtrlMarcheSequenceStop( void ) ;
static Boolean CtrlMarcheSequenceStar( void ) ;
static move_t body;
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlMarche( void ) 
{
	body.move = E_MOVE_STOP;
	body.speed = E_SERVO_VITESSE_5;
	//on ajoute les pattes
	CtrlPatte();
	//on nenvoie la sequence d'arret
	CtrlMarcheSequenceStop();
}

//dispatcher
void CtrlMarcheDispatcher( Event_t event )  
{
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_100MS ))
	{
		//on envoie vers la machine d'etat de la marche
		CtrlMarcheSequence();
	}
	
	//on envoie la position des servo tte les sec quand on est en stop
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_1S ))
	{
		if( body.move == E_MOVE_STOP )
		{
			DrvServoSendUartPosition();
		}			
	}
}

//on recupere la structure
move_t* CtrlMarcheGetStruct( void )
{
	return &body;	
}


//deplace le robot 
void CtrlMarcheMove( EMove move, EServoVitesse speed ) 
{
	step = 0U;
	body.move = move;
	body.speed = speed;
}

//deplace le robot d'un pas
void CtrlMarcheMoveStep( EMove move, EServoVitesse speed ) 
{
	step = 0U;
	body.move = move;
	body.speed = speed;
}

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


//on lance les sequence de mouvements du robot
static void CtrlMarcheSequence( void )
{
	if( body.move == E_MOVE_STOP )
	{
		//on attend que la sequence soit terminer pour ne plus l'entretenir
		if(body.move != old_move)
		{
			if( TRUE == CtrlMarcheSequenceStop())
			{
				old_move = body.move;
				DrvServoSendUartPosition();
			}
		}		
	}			
	else if( body.move == E_MOVE_SIT_DOWN )
	{
		//on attend que la sequence soit terminer pour ne plus l'entretenir
		if(body.move != old_move)
		{
			if( TRUE == CtrlMarcheSequenceSitDown())
			{
				old_move = body.move;
				DrvServoSendUartPosition();
			}
		}
	}			
	else if( body.move == E_MOVE_STAR )
	{
		//on attend que la sequence soit terminer pour ne plus l'entretenir
		if(body.move != old_move)
		{
			if( TRUE == CtrlMarcheSequenceStar())
			{
				old_move = body.move;
				DrvServoSendUartPosition();
			}
		}
	}
	else if( body.move == E_MOVE_FORWARD )	
	{
		//on passe par la sequence de stop avant d'enchainer sur le mouvement
		if( old_move != E_MOVE_FORWARD )
		{
			if( TRUE == CtrlMarcheSequenceStop())
			{
				old_move = body.move;
				DrvServoSendUartPosition();
			}
		}
		else
		{
			CtrlMarcheSequenceForward();
			old_move = body.move;
			DrvServoSendUartPosition();
		}
	}
	else if( body.move == E_MOVE_BACKWARD )
	{
		//on passe par la sequence de stop avant d'enchainer sur le mouvement
		if( old_move != E_MOVE_BACKWARD )
		{
			if( TRUE == CtrlMarcheSequenceStop())
			{
				old_move = body.move;
				DrvServoSendUartPosition();
			}
		}
		else
		{
			CtrlMarcheSequenceBackward();
			old_move = body.move;
			DrvServoSendUartPosition();
		}
	}
	else if( body.move == E_MOVE_LEFT )
	{
		//on passe par la sequence de stop avant d'enchainer sur le mouvement
		if( old_move != E_MOVE_LEFT )
		{
			if( TRUE == CtrlMarcheSequenceStop())
			{
				old_move = body.move;
				DrvServoSendUartPosition();
			}
		}
		else
		{
			CtrlMarcheSequenceLeft();
			old_move = body.move;
			DrvServoSendUartPosition();
		}
	}	
	else if( body.move == E_MOVE_RIGHT )
	{
		//on passe par la sequence de stop avant d'enchainer sur le mouvement
		if( old_move != E_MOVE_RIGHT )
		{
			if( TRUE == CtrlMarcheSequenceStop())
			{
				old_move = body.move;
				DrvServoSendUartPosition();
			}
		}
		else
		{
			CtrlMarcheSequenceRight();
			old_move = body.move;
			DrvServoSendUartPosition();
		}
	}	
}


static Boolean CtrlMarcheSequenceStar( void )
{
	Int8U ret = 0x00;
	//on repli les pattes vers l'interieur
	/*
		-\| |/-			mid min |  | max mid
		--| |--	step 0	mid mid |  | mid mid
		-/| |\-			mid max |  | min mid
	*/
	if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<0U);
	}	
	if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<1U);
	}	
	if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<2U);
	}	
	if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<3U);
	}	
	if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<4U);
	}	
	if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<5U);
	}	
	//quand on est arrivé a la bonne position on change de step	
	if( ret == 0x3FU )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}			

static Boolean CtrlMarcheSequenceSitDown( void )
{
	Int8U ret = 0x00;
	//on repli les pattes vers l'interieur
	/*
		-/-| |-\-			max mid |  | mid min
		-/-| |-\-	step 0	max mid |  | mid min
		-/-| |-\-			max mid |  | mid min
	*/
	if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MAX_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<0U);
	}	
	if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MAX_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<1U);
	}	
	if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MID_EPAULE	,	ANGLE_MAX_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<2U);
	}	
	if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MIN_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<3U);
	}	
	if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MIN_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<4U);
	}	
	if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MID_EPAULE	,	ANGLE_MIN_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<5U);
	}	
	//quand on est arrivé a la bonne position on change de step	
	if( ret == 0x3FU )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}			

static Boolean CtrlMarcheSequenceStop( void )
{
	Int8U ret = 0x00;
	/*
		/-| |-\				mid mid |  | mid mid
		/-| |-\		step 0	mid mid |  | mid mid
		/-| |-\				mid mid |  | mid mid
	*/
	//on mets les pattes aux neutre
	if( CtrlPatteDirectMove(AVANT_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<0U);
	}	
	if( CtrlPatteDirectMove(MILIEU_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<1U);
	}	
	if( CtrlPatteDirectMove(ARRIERE_GAUCHE	,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<2U);
	}	
	if( CtrlPatteDirectMove(AVANT_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<3U);
	}	
	if( CtrlPatteDirectMove(MILIEU_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<4U);
	}	
	if( CtrlPatteDirectMove(ARRIERE_DROITE	,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	E_SERVO_VITESSE_5 ) == TRUE )
	{
		ret |= (1U<<5U);
	}	
	//quand on est arrivé a la bonne position on change de step	
	if( ret == 0x3FU )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	

static void CtrlMarcheSequenceBackward( void ) 
{
	Int8U ret = 0x00;
	if(step == 0)
	{
		/*
			/-| |-/				mid mid |  | mid max
			\-| |-\		step 0	min mid |  | mid mid
			/-| |-/				mid mid |  | mid max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MIN_EPAULE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MAX_EPAULE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MID_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 1U;
		}
	}
	else if(step == 1U)
	{
		/*
			/\| |\/				mid min |  | min max
			\/| |/\		step 1	min max |  | max mid
			/\| |\/				mid min |  | min max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}		
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 2U;
		}
	}
	else if(step == 2U)
	{
		/*
			\\| |\\				min min |  | min mid
			//| |//		step 2	mid max |  | max max
			\\| |\\				min min |  | min mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}		
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 3U;
		}
	}
	else if(step == 3U)
	{
		/*
			\/| |/\				min max |  | max mid
			/\| |\/		step 3	mid min |  | min max
			\/| |/\				min max |  | max mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}		
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 4U;
		}
	}
	else if(step == 4U)
	{
		/*
			//| |//				mid max |  | max max
			\\| |\\		step 4	min min |  | min mid
			//| |//				mid max |  | max max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}		
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 1U;
		}
	}
}

static void CtrlMarcheSequenceForward( void )
{
	Int8U ret = 0x00;
	if(step == 0)
	{
		/*
			/-| |-/				mid mid |  | mid max
			\-| |-\		step 0	min mid |  | mid mid
			/-| |-/				mid mid |  | mid max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MID_EPAULE	,	ANGLE_MIN_COUDE,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MID_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MID_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 1U;
		}
	}
	else if(step == 1U)
	{
		/*
			\/| |/\				min max |  | max mid
			/\| |\/		step 1	mid min |  | min max
			\/| |/\				min max |  | max mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}		
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 2U;
		}
	}
	else if(step == 2U)
	{
		/*
			\\| |\\				min min |  | min mid
			//| |//		step 2	mid max |  | max max
			\\| |\\				min min |  | min mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}		
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 3U;
		}
	}
	else if(step == 3U)
	{
		/*
			/\| |\/				mid min |  | min max
			\/| |/\		step 3	min max |  | max mid
			/\| |\/				mid min |  | min max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}		
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 4U;
		}
	}
	else if(step == 4U)
	{
		/*
			//| |//				mid max |  | max max
			\\| |\\		step 4	min min |  | min mid
			//| |//				mid max |  | max max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}		
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 1U;
		}
	}
}	

static void CtrlMarcheSequenceRight( void ) 
{
	Int8U ret = 0x00U;
	if(step == 0U)
	{
		/*
			//| |/\				mid max |  | max mid
			//| |/\		step 0	mid max |  | max mid
			//| |/\				mid max |  | max mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 1U;
		}
	}
	else if(step == 1U)
	{
		/*
			//| |//				mid max |  | max max
			\/| |/\		step 1	min max |  | max mid
			//| |//				mid max |  | max max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 2U;
		}
	}
	else if(step == 2U)
	{
		/*
			//| |\/				mid max |  | min max
			\\| |/\		step 2	min min |  | max mid
			//| |\/				mid max |  | min max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 3U;
		}
	}
	else if(step == 3U)
	{
		/*
			\/| |\\				min max |  | min mid
			/\| |//		step 3	mid min |  | max max
			\/| |\\				min max |  | min mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 4U;
		}
	}
	else if(step == 4U)
	{
		/*
			\\| |\\				min min |  | min mid
			/\| |\/		step 4	mid min |  | min max
			\\| |\\				min min |  | min mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 5U;
		}
	}	
	else if(step == 5U)
	{
		/*
			/\| |\\				mid min |  | min mid
			/\| |\\		step 5	mid min |  | min mid
			/\| |\\				mid min |  | min mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 0U;
		}
	}	
}

static void CtrlMarcheSequenceLeft( void ) 
{
	Int8U ret = 0x00U;
	if(step == 0U)
	{
		/*
			/\| |\\				mid min |  | min mid
			/\| |\\		step 0	mid min |  | min mid
			/\| |\\				mid min |  | min mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 1U;
		}
	}
	else if(step == 1U)
	{
		/*
			/\| |\/				mid min |  | min max
			\\| |\\		step 1	min min |  | min mid
			/\| |\/				mid min |  | min max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 2U;
		}
	}
	else if(step == 2U)
	{
		/*
			/\| |//				mid min |  | max max
			\/| |\\		step 2	min max |  | min mid
			/\| |//				mid min |  | max max
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 3U;
		}
	}
	else if(step == 3U)
	{
		/*
			\\| |/\				min min |  | max mid
			//| |\/		step 3	mid max |  | min max
			\\| |/\				min min |  | max mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MIN_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MIN_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 4U;
		}
	}
	else if(step == 4U)
	{
		/*
			\/| |/\				min max |  | max mid
			//| |//		step 4	mid max |  | max max
			\/| |/\				min max |  | max mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MIN_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MAX_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 5U;
		}
	}	
	else if(step == 5U)
	{
		/*
			//| |/\				mid max |  | max mid
			//| |/\		step 5	mid max |  | max mid
			//| |/\				mid max |  | max mid
		*/
		if( CtrlPatteMove(AVANT_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<0U);
		}	
		if( CtrlPatteMove(MILIEU_GAUCHE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<1U);
		}	
		if( CtrlPatteMove(ARRIERE_GAUCHE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<2U);
		}	
		if( CtrlPatteMove(AVANT_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<3U);
		}	
		if( CtrlPatteMove(MILIEU_DROITE		,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<4U);
		}	
		if( CtrlPatteMove(ARRIERE_DROITE	,	ANGLE_MAX_EPAULE	,	ANGLE_MID_COUDE	,	body.speed ) == TRUE )
		{
			ret |= (1U<<5U);
		}	
		//quand on est arrivé a la bonne position on change de step	
		if( ret == 0x3FU )
		{
			step = 0U;
		}
	}	
}


