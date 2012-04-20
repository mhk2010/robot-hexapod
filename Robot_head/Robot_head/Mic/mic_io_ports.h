/*
 * mic_io_ports.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef MIC_IO_PORTS_H_
#define MIC_IO_PORTS_H_

#include "Tools/tools_typedefs.h"

/*
	DDxn	PORTxn	PUD I/O		Pull-up		Comment
	0		0		X	Input	No			Tri-state (Hi-Z)
	0		1		0	Input	Yes			Pxn will source current if ext. pulled low.
	0		1		1	Input	No			Tri-state (Hi-Z)
	1		0		X	Output	No			Output Low (Sink)
	1		1		X	Output	No			Output High (Source)
*/


////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////
//definit les constantes IOs
#define DEF_IO(port,pin) E_PORT##port##_PIN##pin##_IO

//definit tout les types de port
typedef enum EEIoPort
{
	E_PORT_A ,
	E_PORT_B ,
	E_PORT_C ,
	E_PORT_D ,
	//--------
	E_NB_PORT ,
}EIoPort;

//definit tout les types de pins de port
typedef enum EEIoPortPin
{
	E_PIN_0 ,
	E_PIN_1 ,
	E_PIN_2 ,
	E_PIN_3 ,
	E_PIN_4 ,
	E_PIN_5 ,
	E_PIN_6 ,
	E_PIN_7 ,
	//--------
	E_NB_PIN ,
}EIoPortPin;
	

//definit tout les types d'IO
typedef enum EEIoPin
{
  DEF_IO(A,0),
  DEF_IO(A,1),
  DEF_IO(A,2),
  DEF_IO(A,3),
  DEF_IO(A,4),
  DEF_IO(A,5),
  DEF_IO(A,6),
  DEF_IO(A,7),
  
  DEF_IO(B,0),
  DEF_IO(B,1),
  DEF_IO(B,2),
  DEF_IO(B,3),
  DEF_IO(B,4),
  DEF_IO(B,5),
  DEF_IO(B,6),
  DEF_IO(B,7),	
  
  DEF_IO(C,0),
  DEF_IO(C,1),
  DEF_IO(C,2),
  DEF_IO(C,3),
  DEF_IO(C,4),
  DEF_IO(C,5),
  DEF_IO(C,6),
  DEF_IO(C,7),
  
  DEF_IO(D,0),
  DEF_IO(D,1),
  DEF_IO(D,2),
  DEF_IO(D,3),
  DEF_IO(D,4),
  DEF_IO(D,5),
  DEF_IO(D,6),
  DEF_IO(D,7),
}EIoPin;

//definit le type de direction d'une IO
typedef enum EEPortDirection
{
  PORT_INPUT,
  PORT_OUTPUT
} EPortDirection;

//definit le type de niveau d'une IO
typedef enum EEIoLevel
{
  IO_LEVEL_GND,
  IO_LEVEL_VCC,
  IO_LEVEL_HIGH_Z,
} EIoLevel;

//definit le type de pull up d'une IO
typedef enum EEInputPullUp
{
  PORT_NO_PULL_UP,
  PORT_PULL_UP
} EInputPullUp;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//Set io pin as output 
Boolean micIoPortsConfigureInput( EIoPin io, EInputPullUp pull_up_enable );
//Set io pin as output 
Boolean micIoPortsConfigureOutput( EIoPin io_pin );
//Set io pin as Low Level 
Boolean micIoPortsConfigureToLowLevel( EIoPin io_pin );
//Set io pin as High Level 
Boolean micIoPortsConfigureToHighLevel( EIoPin io_pin );
//Toggle IO pin
Boolean micIoPortsConfigureToToggleLevel( EIoPin io_pin );

#endif /* MIC_IO_PORTS_H_ */