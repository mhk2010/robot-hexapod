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
#define MIN_ANGLE				0      
#define MAX_ANGLE				180  
#define MIN_PULSE_WIDTH			400     
#define MAX_PULSE_WIDTH			2400   
#define DEFAULT_PULSE_WIDTH		1200
#define REFRESH_INTERVAL		20000

#define OFFSET_TIMER			7
	
#define MAX_SERVOS				14

#define INVALID_SERVO			0xFF
////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////


/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct {
	EIoPin pin;
	uint16_t ticks;
	uint16_t ticks_consigne;
	Boolean moving;
	Boolean active;
} servo_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Servo 
void DrvServo( void ) ;

// Ajout d'un Drv Servo 
void DrvAddServo( EIoPin pin , Int8U angle ) ;

// Ajout d'un Drv Servo 
void DrvDeleteServo( EIoPin pin ) ;

// bouge le servo a la position voulu en angle
void DrvServoMoveToPosition( EIoPin pin, Int8U angle ) ;
// bouge le servo a la position voulu en angle
void DrvServoIndexMoveToPosition( Int8U index_servo, Int8U angle );

// donne la position du servo en angle
Int8U DrvServoGetPosition( EIoPin pin) ;


#endif /* DRV_SERVO_H_ */