/*
 * seq_light.h
 *
 * Created: 29/11/2011 15:48:34
 *  Author: berryer
 */ 


#ifndef SEQ_LIGHT_H_
#define SEQ_LIGHT_H_


#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"

#include "Drv/drv_event.h"

#include "Ctrl/ctrl_tete.h"
#include "Ctrl/ctrl_marche.h"
#include "Ctrl/ctrl_patte.h"

#include "Seq/seq_light.h"
#include "Seq/seq_proximity.h"

//init
void SeqLight( void ) ;

//on reagit aux evenements
void SeqLightDispatcher ( Event_t event ) ;

//on lance la sequence de mouvement de la lumiere
void SeqLightStartScan( void ) ;

//on lance la sequence de mouvement de la lumiere
void SeqLightStartFollowLight( void ) ;

//on stop la sequence de mouvement de la lumiere
void SeqLightStop( void ) ;

#endif /* SEQ_LIGHT_H_ */