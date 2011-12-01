/*
 * hum_curious.h
 *
 * Created: 01/12/2011 19:01:07
 *  Author: louis
 */ 

#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"

#include "Ctrl/ctrl_uart_protocole.h"
#include "Ctrl/ctrl_tete.h"
#include "Ctrl/ctrl_marche.h"
#include "Ctrl/ctrl_patte.h"
#include "Ctrl/ctrl_ultrason.h"
#include "Ctrl/ctrl_boussole.h"
#include "Ctrl/ctrl_accel.h"

#include "Seq/seq_light.h"
#include "Seq/seq_proximity.h"

#ifndef HUM_CURIOUS_H_
#define HUM_CURIOUS_H_




////////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
void HumCuriousInit(Boolean repeat )  ;

void HumCuriousDispatcher ( Event_t event ) ;


#endif /* HUM_CURIOUS_H_ */