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

#include "Hum/hum_curious.h"

////////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//lancement du debut de vie du robot
Boolean RobotLifeInit(void) ;

void RobotLife ( Event_t event ) ;



#endif /* APP_ROBOT_H_ */