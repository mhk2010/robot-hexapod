/*
 * drv_servo.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef DRV_SERVO_H_
#define DRV_SERVO_H_

#include "Tools/tools_typedefs.h"

#include "Mic/mic_io_ports.h"

#include "Conf/conf_hard.h"

#include "drv_timer.h"

////////////////////////////////////////////PUBLIC DEFINES///////////////////////////////////////////
#define MIN_ANGLE				0U      
#define MAX_ANGLE				180U 

#define MIN_PULSE_WIDTH			400U //us  
#define MAX_PULSE_WIDTH			2300U   //us  
 
#define DEFAULT_PULSE_WIDTH		1200U
#define REFRESH_INTERVAL		20000U

#define OFFSET_TIMER			7U
	
#define MAX_SERVOS				14U

#define INVALID_SERVO			0xFFU

////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////
typedef enum EEServoVitesse
{
  E_SERVO_VITESSE_0	= 100U,
  E_SERVO_VITESSE_1	= 80U,
  E_SERVO_VITESSE_2	= 60U,
  E_SERVO_VITESSE_3	= 40U,
  E_SERVO_VITESSE_4	= 20U,
  E_SERVO_VITESSE_5	= 0U,
}EServoVitesse;

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct {
	EIoPin pin;
	uint16_t ticks;
	uint16_t ticks_consigne;
	EServoVitesse vitesse;
	uint16_t increment;
	Boolean moving;
	Boolean active;
} servo_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Servo 
void DrvServo( void ) ;

// Ajout d'un Drv Servo 
void DrvAddServo( EIoPin pin , Int16U angle )  ;

// Ajout d'un Drv Servo 
void DrvDeleteServo( EIoPin pin ) ;

// si le servo a une consigne ne cours
Boolean DrvServoMoving( Int8U index ) ;

// bouge le servo a la position voulu en angle
Boolean DrvServoMoveToPosition( Int8U index, Int16U angle, EServoVitesse vitesse) ;

// bouge le servo a la position voulu en angle sans savoir si il été deja en mouvement
Boolean DrvServoDirectMoveToPosition( Int8U index, Int16U angle, EServoVitesse vitesse) ;

// donne la position du servo en angle
Int16U DrvServoGetPosition( Int8U index) ;

// envoie la position de tout les servo sur l'UART
void DrvServoSendUartPosition( void ) ;


#endif /* DRV_SERVO_H_ */