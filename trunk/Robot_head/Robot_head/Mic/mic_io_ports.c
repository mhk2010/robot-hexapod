/*
 * mic_io_ports.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "mic_io_ports.h"




/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//set the PUD: PUD: Pull-up Disable
Boolean micIoPortsMasterControlUnitPullUpDisable( Boolean enable ) ;

//set the Port A|B|C|D Input Pins Address
Boolean micIoPortsInputPinsAddress( Int8U port_name, Int8U pin_io, Boolean value ) ;

//set the Port A|B|C|D Data Direction Register
Boolean micIoPortsDirectionRegister( Int8U port_name, Int8U pin_io, Boolean value ) ;

//set the Port A|B|C|D Data Register
Boolean micIoPortsDataRegister( Int8U port_name, Int8U pin_io, Boolean value ) ;

//set the Port A Data Register
Boolean micIoPortsDataRegisterA( Int8U pin_io , Boolean value )  ;

//Read the Port A Data Register
Int8U micIoPortsReadDataRegisterA( void ) ;

//set the Port A Data Direction Register
Boolean micIoPortsDirectionRegisterA( Int8U pin_io , Boolean value )  ;

//set the Port A Input Pins Address
Boolean micIoPortsInputPinsAddressA( Int8U pin_io , Boolean value )  ;

//set the Port B Data Register
Boolean micIoPortsDataRegisterB( Int8U pin_io , Boolean value )  ;

//Read the Port B Data Register
Int8U micIoPortsReadDataRegisterB( void ) ;

//set the Port B Data Direction Register
Boolean micIoPortsDirectionRegisterB( Int8U pin_io , Boolean value )  ;

//set the Port B Input Pins Address
Boolean micIoPortsInputPinsAddressB( Int8U pin_io , Boolean value )  ;

//set the Port C Data Register
Boolean micIoPortsDataRegisterC( Int8U pin_io , Boolean value )  ;

//Read the Port C Data Register
Int8U micIoPortsReadDataRegisterC( void ) ;

//set the Port C Data Direction Register
Boolean micIoPortsDirectionRegisterC( Int8U pin_io , Boolean value )  ;

//set the Port C Input Pins Address
Boolean micIoPortsInputPinsAddressC( Int8U pin_io , Boolean value )  ;

//set the Port D Data Register
Boolean micIoPortsDataRegisterD( Int8U pin_io , Boolean value )  ;

//Read the Port D Data Register
Int8U micIoPortsReadDataRegisterD( void ) ;

//set the Port D Data DireDtion Register
Boolean micIoPortsDirectionRegisterD( Int8U pin_io , Boolean value )  ;

//set the Port D Input Pins Address
Boolean micIoPortsInputPinsAddressD( Int8U pin_io , Boolean value )  ;




//////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//Set IO pin as output 
Boolean micIoPortsConfigureOutput( EIoPin io_pin )
{
	Boolean o_success = TRUE;
	Int8U port = ( io_pin / 8 ) ;
	Int8U pin =  ( io_pin % 8 ) ;
	micIoPortsDirectionRegister(port,pin,TRUE);
	
	return o_success;
}

//Set IO pin as Low Level 
Boolean micIoPortsConfigureToLowLevel( EIoPin io_pin )
{
	Boolean o_success = TRUE;
	Int8U port = ( io_pin / 8 ) ;
	Int8U pin =  ( io_pin % 8 ) ;
	micIoPortsDataRegister(port,pin,FALSE);
	
	return o_success;
}

//Set IO pin as High Level 
Boolean micIoPortsConfigureToHighLevel( EIoPin io_pin )
{
	Boolean o_success = TRUE;
	Int8U port = ( io_pin / 8 ) ;
	Int8U pin =  ( io_pin % 8 ) ;
	micIoPortsDataRegister(port,pin,TRUE);
	
	return o_success;
}

//Toggle IO pin
Boolean micIoPortsConfigureToToggleLevel( EIoPin io_pin )
{
	Boolean o_success = TRUE;
	Int8U port = ( io_pin / 8 ) ;
	Int8U pin =  ( io_pin % 8 ) ;
	if( port == 0 )
	{
		BIT_TOGGLE(PORTA,pin);
	}
	else if( port == 1 )
	{
		BIT_TOGGLE(PORTB,pin);
	}
	else if( port == 2 )
	{
		BIT_TOGGLE(PORTC,pin);
	}
	else if( port == 3 )
	{
		BIT_TOGGLE(PORTD,pin);
	}
	
	return o_success;
}

//Set IO as input and add pull up if necessary 
Boolean micIoPortsConfigureInput( EIoPin IO, EInputPullUp pull_up_enable )
{
	Boolean o_success = TRUE;
	Int8U port = ( IO / 8 ) ;
	Int8U pin =  ( IO % 8 ) ;
	micIoPortsDirectionRegister(port,pin,FALSE);
	if(pull_up_enable == PORT_PULL_UP)
	{
		micIoPortsDataRegister(port,pin,TRUE);
	}
	else
	{
		micIoPortsDataRegister(port,pin,FALSE);
	}		
	
	return o_success;
}

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

//set the PUD: PUD: Pull-up Disable
Boolean micIoPortsMasterControlUnitPullUpDisable( Boolean enable ) 
{
	Boolean o_success = TRUE;
	BIT_SET(MCUCR,PUD,enable);
	return o_success;
}

//set the Port A|B|C|D Data Register
Boolean micIoPortsDataRegister( Int8U port_name, Int8U pin_io, Boolean value ) 
{
	Boolean o_success = TRUE;
	if( port_name == 0 )
	{
		micIoPortsDataRegisterA(pin_io,value);
	}
	else if( port_name == 1 )
	{
		micIoPortsDataRegisterB(pin_io,value);
	}
	else if( port_name == 2 )
	{
		micIoPortsDataRegisterC(pin_io,value);
	}
	else if( port_name == 3 )
	{
		micIoPortsDataRegisterD(pin_io,value);
	}
	return o_success;
}

//set the Port A|B|C|D Data Direction Register
Boolean micIoPortsDirectionRegister( Int8U port_name, Int8U pin_io, Boolean value ) 
{
	Boolean o_success = TRUE;
	if( port_name == 0 )
	{
		micIoPortsDirectionRegisterA(pin_io,value);
	}
	else if( port_name == 1 )
	{
		micIoPortsDirectionRegisterB(pin_io,value);
	}
	else if( port_name == 2 )
	{
		micIoPortsDirectionRegisterC(pin_io,value);
	}
	else if( port_name == 3 )
	{
		micIoPortsDirectionRegisterD(pin_io,value);
	}
	return o_success;
}

//set the Port A|B|C|D Input Pins Address
Boolean micIoPortsInputPinsAddress( Int8U port_name, Int8U pin_io, Boolean value ) 
{
	Boolean o_success = TRUE;
	if( port_name == 0 )
	{
		micIoPortsInputPinsAddressA(pin_io,value);
	}
	else if( port_name == 1 )
	{
		micIoPortsInputPinsAddressB(pin_io,value);
	}
	else if( port_name == 2 )
	{
		micIoPortsInputPinsAddressC(pin_io,value);
	}
	else if( port_name == 3 )
	{
		micIoPortsInputPinsAddressD(pin_io,value);
	}
	return o_success;
}

//set the Port A Data Register
Boolean micIoPortsDataRegisterA( Int8U pin_io, Boolean value ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PORTA,pin_io,value);
	return o_success;
}

//Read the Port A Data Register
Int8U micIoPortsReadDataRegisterA( void ) 
{
	return PORTA;
}

//set the Port A Data Direction Register
Boolean micIoPortsDirectionRegisterA( Int8U pin_io , Boolean value ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PORTA,pin_io,value);
	return o_success;
}

//set the Port A Input Pins Address
Boolean micIoPortsInputPinsAddressA( Int8U pin_io , Boolean value ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PINA,pin_io,value);
	return o_success;
}

//set the Port B Data Register
Boolean micIoPortsDataRegisterB( Int8U pin_io , Boolean value )  
{
	Boolean o_success = TRUE;
	BIT_SET(PORTB,pin_io,value);
	return o_success;
}

//Read the Port B Data Register
Int8U micIoPortsReadDataRegisterB( void ) 
{
	return PORTB;
}

//set the Port B Data Direction Register
Boolean micIoPortsDirectionRegisterB( Int8U pin_io , Boolean value )  
{
	Boolean o_success = TRUE;
	BIT_SET(DDRB,pin_io,value);
	return o_success;
}

//set the Port B Input Pins Address
Boolean micIoPortsInputPinsAddressB( Int8U pin_io , Boolean value ) 
{
	Boolean o_success = TRUE;
	BIT_SET(PINB,pin_io,value);
	return o_success;
}

//set the Port C Data Register
Boolean micIoPortsDataRegisterC( Int8U pin_io , Boolean value )  
{
	Boolean o_success = TRUE;
	BIT_SET(PORTC,pin_io,value);
	return o_success;
}

//Read the Port C Data Register
Int8U micIoPortsReadDataRegisterC( void ) 
{
	return PORTC;
}

//set the Port C Data Direction Register
Boolean micIoPortsDirectionRegisterC( Int8U pin_io , Boolean value )  
{
	Boolean o_success = TRUE;
	BIT_SET(DDRC,pin_io,value);
	return o_success;
}

//set the Port C Input Pins Address
Boolean micIoPortsInputPinsAddressC( Int8U pin_io , Boolean value )  
{
	Boolean o_success = TRUE;
	BIT_SET(PINC,pin_io,value);
	return o_success;
}

//set the Port D Data Register
Boolean micIoPortsDataRegisterD( Int8U pin_io , Boolean value )  
{
	Boolean o_suDDess = TRUE;
	BIT_SET(PORTD,pin_io,value);
	return o_suDDess;
}

//Read the Port D Data Register
Int8U micIoPortsReadDataRegisterD( void ) 
{
	return PORTD;
}

//set the Port D Data DireDtion Register
Boolean micIoPortsDirectionRegisterD( Int8U pin_io , Boolean value ) 
{
	Boolean o_suDDess = TRUE;
	BIT_SET(DDRD,pin_io,value);
	return o_suDDess;
}

//set the Port D Input Pins Address
Boolean micIoPortsInputPinsAddressD( Int8U pin_io , Boolean value )  
{
	Boolean o_suDDess = TRUE;
	BIT_SET(PIND,pin_io,value);
	return o_suDDess;
}