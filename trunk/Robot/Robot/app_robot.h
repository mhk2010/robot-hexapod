/*
 * app_robot.h
 *
 * Created: 22/11/2011 15:43:19
 *  Author: berryer
 */ 


#ifndef APP_ROBOT_H_
#define APP_ROBOT_H_


#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"

#include "Drv/drv_event.h"

#include "Ctrl/ctrl_uart_protocole.h"
#include "Ctrl/ctrl_marche.h"
#include "Ctrl/ctrl_tete.h"



////////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
Boolean RobotLifeInit(void) ;

//fait vivre le robot
void RobotLife ( Event_t event ) ;



#endif /* APP_ROBOT_H_ */