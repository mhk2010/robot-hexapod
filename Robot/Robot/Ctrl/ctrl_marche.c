/*
 * ctrl_marche.c
 *
 * Created: 15/11/2011 17:08:52
 *  Author: berryer
 */ 

#include "ctrl_marche.h"
#include "ctrl_patte.h"
#include "ctrl_tete.h"


#define AMPLITUDE_MAX_EPAULE	25
#define AMPLITUDE_MAX_COUDE		20
#define TIMEOUT_MIN_SPEED		10 //(100ms)



static Int8U timeout			= 0;
static Int8U step				= 0;
static Int8U move_step			= FALSE;
static EMove old_move			= E_MOVE_STOP;



/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CtrlMarcheSequence( void ) ;
static void CtrlMarcheSequenceStop( void ) ;
static void CtrlMarcheSequenceForward( void ) ;
static void CtrlMarcheSequenceBackward( void ) ;
static void CtrlMarcheSequenceLeft( void ) ;
static void CtrlMarcheSequenceRight( void ) ;


static move_t body;
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlMarche( void ) 
{
	body.move = E_MOVE_STOP;
	old_move = E_MOVE_STOP;
	body.speed = E_SPEED_0;
	
	CtrlPatte();
	CtrlMarcheSequenceStop();
}

//dispatcher
void CtrlMarcheDispatcher( Event_t event )  
{
	if ( DrvEventTestEvent(event, CONF_EVENT_TIMER_10MS ))
	{
		if( body.move != E_MOVE_STOP)
		{
			if ( timeout >= TIMEOUT_MIN_SPEED + body.speed)
			{
				CtrlMarcheSequence();
				timeout = 0;
			}
			else
			{
				timeout++;
			}	
		}
	}
	//on a attendu de faire le scan avant de faire le mouvement
	if (( DrvEventTestEvent(event, CONF_EVENT_FIND_NO_OBJECT )) || ( DrvEventTestEvent(event, CONF_EVENT_FIND_NEAR_OBJECT )) )
	{
		//sa sert a rien de scanner l'avant quand on recul et quand on veut un stop
		if( ( old_move != E_MOVE_BACKWORD ) && (old_move == E_MOVE_STOP)) 
		{
			//on valide le mouvemnt
			if( body.move == E_MOVE_FORWORD )	
			{
				old_move = E_MOVE_FORWORD;
			}	
			else if( body.move == E_MOVE_LEFT )	
			{
				old_move = E_MOVE_LEFT;
			}	
			else if( body.move == E_MOVE_RIGHT )	
			{
				old_move = E_MOVE_RIGHT;
			}			
		}
	}
}

//on recupere la structure
move_t* CtrlMarcheGetStruct( void )
{
	return &body;	
}


//deplace le robot 
void CtrlMarcheMove( EMove move, ESpeed speed ) 
{
	step = 0;
	body.move = move;
	body.speed = speed;
	move_step = FALSE;
	old_move = E_MOVE_STOP;
}

//deplace le robot d'un pas
void CtrlMarcheMoveStep( EMove move, ESpeed speed ) 
{
	step = 0;
	body.move = move;
	body.speed = speed;
	move_step = TRUE;
	old_move = E_MOVE_STOP;
}


/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//on lance les sequence de mouvements du robot
static void CtrlMarcheSequence( void )
{
	//coude gauche vers l'exterieur positif
	//coude droit vers l'exterieur negatif
	//epaule gauche vers l'arriere negatif
	//epaule droite vers l'arriere positif
	
	if( body.move == E_MOVE_STOP )
	{
		CtrlMarcheSequenceStop();
		old_move = E_MOVE_STOP;
	}	
	else if( body.move == E_MOVE_FORWORD )	
	{
		//si on ne sort pas d'un stop
		if( old_move == E_MOVE_STOP )
		{
			//on fait un scan de ce qu'il y a devant
			CtrlTeteScanProximityAngle(NEUTRE_TETE_HORIZONTAL);
		}
		else if( old_move == E_MOVE_FORWORD)
		{
			CtrlMarcheSequenceForward();
		}
	}
	else if( body.move == E_MOVE_BACKWORD )
	{
		//on ne test pas la proximite d'un objet
		CtrlMarcheSequenceBackward();
		old_move = E_MOVE_BACKWORD;
	}
	else if( body.move == E_MOVE_LEFT )
	{
		//si on ne sort pas d'un stop
		if( old_move == E_MOVE_STOP )
		{
			//on fait un scan de ce qu'il y a sur le cot� gauche
			CtrlTeteScanProximityAngle(LEFT_TETE_HORIZONTAL);
		}
		else if( old_move == E_MOVE_LEFT)
		{
			CtrlMarcheSequenceLeft();
		}
	}	
	else if( body.move == E_MOVE_RIGHT )
	{
		if( old_move == E_MOVE_STOP )
		{
			//on fait un scan de ce qu'il y a sur le cot� droit
			CtrlTeteScanProximityAngle(RIGHT_TETE_HORIZONTAL);
		}
		else if( old_move == E_MOVE_RIGHT)
		{
			CtrlMarcheSequenceRight();
		}
	}	
}

static void CtrlMarcheSequenceForward( void )
{
	if(step == 0)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE - AMPLITUDE_MAX_EPAULE,	NEUTRE_COUDE_MILIEU_DROITE - AMPLITUDE_MAX_COUDE);  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_GAUCHE + AMPLITUDE_MAX_COUDE );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE - AMPLITUDE_MAX_EPAULE,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE,NEUTRE_COUDE_ARRIERE_GAUCHE + AMPLITUDE_MAX_COUDE );
		step = 1;
	}	
	else if(step == 1)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_GAUCHE );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE - AMPLITUDE_MAX_EPAULE,	NEUTRE_COUDE_MILIEU_GAUCHE + AMPLITUDE_MAX_COUDE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE,NEUTRE_COUDE_ARRIERE_GAUCHE );
		step = 2;
	}	
	else if(step == 2)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE );
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );		
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_GAUCHE );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE + AMPLITUDE_MAX_EPAULE,	NEUTRE_COUDE_MILIEU_GAUCHE + AMPLITUDE_MAX_COUDE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE,NEUTRE_COUDE_ARRIERE_GAUCHE );
		step = 3;
	}	
	else if(step == 3)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );		
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE,	NEUTRE_COUDE_AVANT_GAUCHE + AMPLITUDE_MAX_COUDE  );		
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE + AMPLITUDE_MAX_EPAULE  ,	NEUTRE_COUDE_MILIEU_GAUCHE );	 
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE + AMPLITUDE_MAX_COUDE);
		if(move_step == FALSE)
		{
			step = 0 ;
		}
		else
		{
			step = 4 ;
		}
	}	
	else if(step == 4)
	{	
		step = 0xffU;
		CtrlMarcheSequenceStop();
	}
}	

static void CtrlMarcheSequenceLeft( void ) 
{
	if(step == 0)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE ,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE,	NEUTRE_COUDE_MILIEU_DROITE - AMPLITUDE_MAX_COUDE);  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE ,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE ,	NEUTRE_COUDE_AVANT_GAUCHE + AMPLITUDE_MAX_COUDE );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE ,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE ,	NEUTRE_COUDE_ARRIERE_GAUCHE + AMPLITUDE_MAX_COUDE );
		step++;
	}	
	else if(step == 1)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE - AMPLITUDE_MAX_COUDE);  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE + AMPLITUDE_MAX_COUDE );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE + AMPLITUDE_MAX_COUDE );
		step = 2 ;
	}
	else if(step == 2)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE );  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE  );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE + AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE  );
		step = 3;
	}
	else if(step == 3)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE );  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE  );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE + AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE  );
		step = 4 ;
	}
	else if(step == 4)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE );  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE  );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE  );
		step = 5 ;
	}
	else if(step == 5)
	{	
		if(move_step == FALSE)
		{
			CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );	
			CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE );  
			CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );
			CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE  );	
			CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE );	
			CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE  );
			step = 1 ;
		}
		else
		{
			step = 0xffU;
			CtrlMarcheSequenceStop();
		}
	}
}

static void CtrlMarcheSequenceRight( void ) 
{
	if(step == 0)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE ,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE,	NEUTRE_COUDE_MILIEU_DROITE - AMPLITUDE_MAX_COUDE);  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE ,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE ,	NEUTRE_COUDE_AVANT_GAUCHE + AMPLITUDE_MAX_COUDE );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE ,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE ,	NEUTRE_COUDE_ARRIERE_GAUCHE + AMPLITUDE_MAX_COUDE );
		step++;
	}	
	else if(step == 1)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE - AMPLITUDE_MAX_COUDE);  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE + AMPLITUDE_MAX_COUDE );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE + AMPLITUDE_MAX_COUDE );
		step = 2 ;
	}
	else if(step == 2)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE );  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE  );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE + AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE  );
		step = 3;
	}
	else if(step == 3)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE );  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE  );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE + AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE  );
		step = 4 ;
	}
	else if(step == 4)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE );  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE + AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE  );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	+ AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE  );
		step = 5 ;
	}
	else if(step == 5)
	{	
		if(move_step == FALSE)
		{
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_DROITE );  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_AVANT_GAUCHE  );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	- AMPLITUDE_MAX_EPAULE	,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE  );
			step = 1 ;
		}
		else
		{
			step = 0xffU;
			CtrlMarcheSequenceStop();
		}
	}
}

static void CtrlMarcheSequenceStop( void )
{
	CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE   ,	NEUTRE_COUDE_AVANT_GAUCHE   );		
	CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE   ,	NEUTRE_COUDE_AVANT_DROITE   );	
	CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE  ,	NEUTRE_COUDE_MILIEU_GAUCHE  );	
	CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE  ,	NEUTRE_COUDE_MILIEU_DROITE  );  
	CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE ,	NEUTRE_COUDE_ARRIERE_GAUCHE );
	CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_ARRIERE_DROITE ,	NEUTRE_COUDE_ARRIERE_DROITE );
	//on envoie l'event 
	DrvEventAddEvent( CONF_EVENT_MOVE_END );	
	
	
}	

static void CtrlMarcheSequenceBackward( void ) 
{
	if(step == 0)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE	 + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_MILIEU_DROITE  - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_MILIEU_DROITE );  
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE	 + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE	 + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_GAUCHE  );	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE	 - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_MILIEU_GAUCHE + AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE );
		step = 1;
	}	
	else if(step == 1)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_GAUCHE + AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE - AMPLITUDE_MAX_EPAULE,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE + AMPLITUDE_MAX_EPAULE,NEUTRE_COUDE_ARRIERE_GAUCHE + AMPLITUDE_MAX_COUDE );
		step = 2;
	}	
	else if(step == 2)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE  );
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);		
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE  );
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_GAUCHE + AMPLITUDE_MAX_COUDE);	
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE + AMPLITUDE_MAX_EPAULE,	NEUTRE_COUDE_MILIEU_GAUCHE );	
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE,NEUTRE_COUDE_ARRIERE_GAUCHE + AMPLITUDE_MAX_COUDE);
		step = 3;
	}	
	else if(step == 3)
	{	
		CtrlPatteMove(AVANT_DROITE,		NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);
		CtrlPatteMove(MILIEU_DROITE,	NEUTRE_EPAULE_AVANT_DROITE + AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE );
		CtrlPatteMove(ARRIERE_DROITE,	NEUTRE_EPAULE_AVANT_DROITE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_AVANT_DROITE - AMPLITUDE_MAX_COUDE);		
		CtrlPatteMove(AVANT_GAUCHE,		NEUTRE_EPAULE_AVANT_GAUCHE - AMPLITUDE_MAX_EPAULE,	NEUTRE_COUDE_AVANT_GAUCHE );		
		CtrlPatteMove(MILIEU_GAUCHE,	NEUTRE_EPAULE_MILIEU_GAUCHE + AMPLITUDE_MAX_EPAULE  ,	NEUTRE_COUDE_MILIEU_GAUCHE + AMPLITUDE_MAX_COUDE);	 
		CtrlPatteMove(ARRIERE_GAUCHE,	NEUTRE_EPAULE_ARRIERE_GAUCHE - AMPLITUDE_MAX_EPAULE ,	NEUTRE_COUDE_ARRIERE_GAUCHE);
		if(move_step == FALSE)
		{
			step = 0 ;
		}
		else
		{
			step = 4 ;
		}
	}	
	else if(step == 4)
	{	
		step = 0xffU;
		CtrlMarcheSequenceStop();
	}
}

