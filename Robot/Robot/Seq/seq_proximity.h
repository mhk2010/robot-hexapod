/*
 * seq_proximity.h
 *
 * Created: 29/11/2011 16:10:47
 *  Author: berryer
 */ 


#ifndef SEQ_PROXIMITY_H_
#define SEQ_PROXIMITY_H_



#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"

#include "Drv/drv_event.h"

#include "Ctrl/ctrl_tete.h"
#include "Ctrl/ctrl_marche.h"

//init
void SeqProximity( void ) ;

//on reagit aux evenements
void SeqProximityDispatcher ( Event_t event ) ;

//on lance la sequence de mouvement vers l'object
void SeqProximityStartScan( void ) ;

//on stop la sequence de mouvement vers l'object
void SeqProximityStopScan( void ) ;


#endif /* SEQ_PROXIMITY_H_ */