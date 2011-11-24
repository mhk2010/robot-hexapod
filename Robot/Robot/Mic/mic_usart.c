/*
 * mic_usart.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "mic_usart.h"


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the UDRn – USART I/O Data Register 0
Boolean micUsart0SetIODataRegister( Int8U udr0 ) 
{
	Boolean o_success = TRUE;
	UDR0 = udr0;
	return o_success;
}
//set the UDRn – USART I/O Data Register 1
Boolean micUsart1SetIODataRegister( Int8U udr1 ) 
{
	Boolean o_success = TRUE;
	UDR1 = udr1;
	return o_success;
}

//Get the UDRn – USART I/O Data Register 0
Int8U micUsart0GetIODataRegister( void ) 
{
	return UDR0 ;
}
//Get the UDRn – USART I/O Data Register 1
Int8U micUsart1GetIODataRegister( void ) 
{
	return UDR1 ;
}

//Get the UDREn: USART Data Register Empty
Boolean micUsart0GetRegisterEmpty( void )
{
  return ( UCSR0A & (1U << UDRE0 ) );
}
//Get the UDREn: USART Data Register Empty
Boolean micUsart1GetRegisterEmpty( void )
{
  return ( UCSR1A & (1U << UDRE1 ) );
}

//Get the Error bits -> Framing, Data Overrun and Parity
EUsartError micUsart0GetError( void )
{ 
  return ( UCSR0A & ( ( 1U << FE0 ) | ( 1U << DOR0 ) | ( 1U << UPE0 ) ) );
}
//Get the Error bits -> Framing, Data Overrun and Parity
EUsartError micUsart1GetError( void )
{ 
  return ( UCSR1A & ( ( 1U << FE1 ) | ( 1U << DOR1 ) | ( 1U << UPE1 ) ) );
}

//Set the U2Xn: Double the USART Transmission Speed
void micUsart0SetSpeedMode( EUsartSpeedMode mode )
{
	if( mode == E_USART_SPEED_NORMAL )
	{
		UCSR0A &= ~mode;
	}
	else
	{
		UCSR0A |= mode;
	}		
}
//Set the U2Xn: Double the USART Transmission Speed
void micUsart1SetSpeedMode( EUsartSpeedMode mode )
{
	if( mode == E_USART_SPEED_NORMAL )
	{
		UCSR1A &= ~mode;
	}
	else
	{
		UCSR1A |= mode;
	}		
}

//Get the U2Xn: Double the USART Transmission Speed
EUsartSpeedMode micUsart0GetSpeedMode( void )
{
	return ( UCSR0A & ( 1U << U2X0 ) );	
}
//Get the U2Xn: Double the USART Transmission Speed
EUsartSpeedMode micUsart1GetSpeedMode( void )
{
	return ( UCSR1A & ( 1U << U2X1 ) );	
}

//Set the MPCMn: Multi-processor Communication Mode
Boolean micUsart0SetMultiProcessorMode( void )
{
	Boolean o_success = TRUE;
	UCSR0A = UCSR0A | ( 1U << MPCM0);
	return o_success;
}
//Set the MPCMn: Multi-processor Communication Mode
Boolean micUsart1SetMultiProcessorMode( void )
{
	Boolean o_success = TRUE;
	UCSR1A = UCSR1A | ( 1U << MPCM1);
	return o_success;
}

//Get the MPCMn: Multi-processor Communication Mode
Boolean micUsart0GetMultiProcessorMode( void )
{
	return ( UCSR0A & ( 1U << MPCM0 ) );
}
//Get the MPCMn: Multi-processor Communication Mode
Boolean micUsart1GetMultiProcessorMode( void )
{
	return ( UCSR1A & ( 1U << MPCM1 ) );
}

//Get the RXCn: USART Receive Complete
Boolean micUsart0GetReceiptCompleted(void)
{
  return ( UCSR0A & ( 1U << RXC0 ) );
}
//Get the RXCn: USART Receive Complete
Boolean micUsart1GetReceiptCompleted(void)
{
  return ( UCSR1A & ( 1U << RXC1 ) );
}

//Set the TXCn: USART Transmit Complete
Boolean micUsart0SetTransmitCompleted(void)
{
	Boolean o_success = TRUE;
	UCSR0A |= ( 1U << TXC0);
	return o_success;
}
//Set the TXCn: USART Transmit Complete
Boolean micUsart1SetTransmitCompleted(void)
{
	Boolean o_success = TRUE;
	UCSR1A |= ( 1U << TXC1);
	return o_success;
}

//Get the TXCn: USART Transmit Complete
Boolean micUsart0GetTransmitCompleted(void)
{
  return ( UCSR0A & ( 1U << TXC0 ) );
}
//Get the TXCn: USART Transmit Complete
Boolean micUsart1GetTransmitCompleted(void)
{
  return ( UCSR1A & ( 1U << TXC1 ) );
}

//Get the UDREn: USART Data Register Empty
Boolean micUsart0GetDataRegisterEmpty(void)
{
  return (Boolean)( 0x20 & ( 1U << UDRE0  ) ) >> UDRE0;
}
//Get the UDREn: USART Data Register Empty
Boolean micUsart1GetDataRegisterEmpty(void)
{
  return ( UCSR1A & ( 1U << UDRE1 ) );
}

//Set the TXENn: Transmitter Enable 0
Boolean micUsart0SetTransmitterEnable( void )
{
	Boolean o_success = TRUE;
	UCSR0B = UCSR0B | ( 1U << TXEN0);
	return o_success;
}
//Set the TXENn: Transmitter Enable 0
Boolean micUsart1SetTransmitterEnable( void )
{
	Boolean o_success = TRUE;
	UCSR1B = UCSR1B | ( 1U << TXEN1);
	return o_success;
}

//Set the TXENn: Transmitter Disable 0
Boolean micUsart0SetTransmitterDisable( void )
{
	Boolean o_success = TRUE;
	UCSR0B &= ~( 1U << TXEN0 );
	return o_success;
}
//Set the TXENn: Transmitter Disable 0
Boolean micUsart1SetTransmitterDisable( void )
{
	Boolean o_success = TRUE;
	UCSR1B &= ~( 1U << TXEN1 );
	return o_success;
}

//Set the RXENn: Receiver Enable 0
Boolean micUsart0SetReceiverEnable( void )
{
	Boolean o_success = TRUE;
	UCSR0B = UCSR0B | ( 1U << RXEN0);
	return o_success;
}
//Set the RXENn: Receiver Enable 0
Boolean micUsart1SetReceiverEnable( void )
{
	Boolean o_success = TRUE;
	UCSR1B = UCSR1B | ( 1U << RXEN1);
	return o_success;
}

//Set the RXENn: Receiver Disable 0
Boolean micUsart0SetReceiverDisable( void )
{
	Boolean o_success = TRUE;
	UCSR0B &= ~( 1U << RXEN0 );
	return o_success;
}
//Set the RXENn: Receiver Disable 0
Boolean micUsart1SetReceiverDisable( void )
{
	Boolean o_success = TRUE;
	UCSR1B &= ~( 1U << RXEN1 );
	return o_success;
}

//Set the UCSZn : Character Size n
Boolean micUsart0SetDataSize( EUsartDataSize data_size )
{
	Boolean o_success = TRUE;
	UCSR0B = ( UCSR0B & ~(1U << UCSZ02)) |
			( data_size & (1U << UCSZ02));

	UCSR0C = ( UCSR0C & ~((1U << UCSZ01) | (1U << UCSZ00))) |
			( (Int8U)(data_size << 1U) & ((1U << UCSZ01) | (1U << UCSZ00)));
	return o_success;
}
//Set the UCSZn : Character Size n
Boolean micUsart1SetDataSize( EUsartDataSize data_size )
{
	Boolean o_success = TRUE;
	UCSR1B = ( UCSR1B & ~(1U << UCSZ12)) |
			( data_size & (1U << UCSZ12));

	UCSR1C = ( UCSR1C & ~((1U << UCSZ11) | (1U << UCSZ10))) |
			( (Int8U)(data_size << 1U) & ((1U << UCSZ11) | (1U << UCSZ10)));
	return o_success;
}

//Set the UPMn1:0: Parity Mode
Boolean micUsart0SetParityMode( EUsartParityMode parity_mode )
{
	Boolean o_success = TRUE;
	UCSR0C = (UCSR0C & ~((1U << UPM01) | (1U << UPM00))) |
			(parity_mode & ((1U << UPM01) | (1U << UPM00)));
	return o_success;
}
//Set the UPMn1:0: Parity Mode
Boolean micUsart1SetParityMode( EUsartParityMode parity_mode )
{
	Boolean o_success = TRUE;
	UCSR1C = (UCSR1C & ~((1U << UPM11) | (1U << UPM10))) |
			(parity_mode & ((1U << UPM11) | (1U << UPM10)));
	return o_success;
}

//Set the USBSn: Stop Bit Select
Boolean micUsart0SetStopBits( EUsartStopBits stop_bits)
{
	Boolean o_success = TRUE;
	UCSR0C = (UCSR0C & ~(1U << USBS0)) |
			(stop_bits & (1U << USBS0));
	return o_success;
}
//Set the USBSn: Stop Bit Select
Boolean micUsart1SetStopBits( EUsartStopBits stop_bits)
{
	Boolean o_success = TRUE;
	UCSR1C = (UCSR1C & ~(1U << USBS1)) |
			(stop_bits & (1U << USBS1));
	return o_success;
}

//Set RXCIEn: RX Complete Interrupt Enable 0
Boolean micUsart0SetRxInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR0B |= (1U << RXCIE0);

	return o_success;
}
//Set RXCIEn: RX Complete Interrupt Enable 0
Boolean micUsart1SetRxInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR1B |= (1U << RXCIE1);

	return o_success;
}

//Clear RXCIEn: RX Complete Interrupt Enable 0
Boolean micUsart0ClearRxInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR0B &= ~(1U << RXCIE0);

	return o_success;
}
//Clear RXCIEn: RX Complete Interrupt Enable 0
Boolean micUsart1ClearRxInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR1B &= ~(1U << RXCIE1);

	return o_success;
}

//Set TXCIEn: TX Complete Interrupt Enable 0
Boolean micUsart0SetTxInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR0B |= (1U << TXCIE0);

	return o_success;
}
//Set TXCIEn: TX Complete Interrupt Enable 0
Boolean micUsart1SetTxInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR1B |= (1U << TXCIE1);

	return o_success;
}

//Clear TXCIEn: TX Complete Interrupt Enable 0
Boolean micUsart0ClearTxInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR0B &= ~(1U << TXCIE0);

	return o_success;
}
//Clear TXCIEn: TX Complete Interrupt Enable 0
Boolean micUsart1ClearTxInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR1B &= ~(1U << TXCIE1);

	return o_success;
}

//Set UDRIEn: USART Data Register Empty Interrupt Enable n
Boolean micUsart0SetDataRegisterEmptyInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR0B |= (1U << UDRIE0);

	return o_success;
}
//Set UDRIEn: USART Data Register Empty Interrupt Enable n
Boolean micUsart1SetDataRegisterEmptyInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR1B |= (1U << UDRIE1);

	return o_success;
}

//Clear UDRIEn: USART Data Register Empty Interrupt Enable n
Boolean micUsart0ClearDataRegisterEmptyInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR0B &= ~(1U << UDRIE0);

	return o_success;
}
//Clear UDRIEn: USART Data Register Empty Interrupt Enable n
Boolean micUsart1ClearDataRegisterEmptyInterrupt( void )
{
	Boolean o_success = TRUE;
	UCSR1B &= ~(1U << UDRIE1);

	return o_success;
}

//Set UCPOLn: Clock Polarity
Boolean micUsart0SetSynchronousClockPolarity( EUsartClockPolarity polarity )
{
	Boolean o_success = TRUE;
	UCSR0C = (UCSR0C & ~(1U << UCPOL0)) | (polarity & (1U << UCPOL0));
  
	return o_success;
}
//Set UCPOLn: Clock Polarity
Boolean micUsart1SetSynchronousClockPolarity( EUsartClockPolarity polarity )
{
	Boolean o_success = TRUE;
	UCSR1C = (UCSR1C & ~(1U << UCPOL1)) | (polarity & (1U << UCPOL1));
  
	return o_success;
}

//Set UBRRn: Baud Rate Asynchronous Normal mode (U2Xn = 0)
Boolean micUsart0SetBaudRateAsynchronousNormalMode( EUsartBaudRate baudrate )
{
	Boolean o_success = FALSE;
	
	if( FALSE == micUsart0GetMultiProcessorMode( ) )
	{
		if( E_USART_SPEED_NORMAL == micUsart0GetSpeedMode( ) )
		{
			UBRR0 = ( CONF_FOSC_HZ / ( 16 * baudrate ) ) - 1 ; 
			o_success = TRUE;
		}
	}	
	
	return o_success;
}	
//Set UBRRn: Baud Rate Asynchronous Normal mode (U2Xn = 0)
Boolean micUsart1SetBaudRateAsynchronousNormalMode( EUsartBaudRate baudrate )
{
	Boolean o_success = FALSE;
	
	if( FALSE == micUsart1GetMultiProcessorMode( ) )
	{
		if( E_USART_SPEED_NORMAL == micUsart1GetSpeedMode( ) )
		{
			UBRR1 = ( CONF_FOSC_HZ / ( 16 * baudrate ) ) - 1 ; 
			o_success = TRUE;
		}
	}	
	
	return o_success;
}	

//Set UBRRn: Baud Rate Asynchronous Double Speed mode (U2Xn = 1)
Boolean micUsart0SetBaudRateAsynchronousDoubleSpeedMode( EUsartBaudRate baudrate )
{	
	Boolean o_success = FALSE;
	
	if( FALSE == micUsart0GetMultiProcessorMode( ) )
	{
		if( E_USART_SPEED_HIGH_SPEED == micUsart0GetSpeedMode( ) )
		{
			UBRR0 = ( CONF_FOSC_HZ / ( 8 * baudrate ) ) - 1 ; 
			o_success = TRUE;
		
		}	
	}
	
	return o_success;
}
//Set UBRRn: Baud Rate Asynchronous Double Speed mode (U2Xn = 1)
Boolean micUsart1SetBaudRateAsynchronousDoubleSpeedMode( EUsartBaudRate baudrate )
{	
	Boolean o_success = FALSE;
	
	if( FALSE == micUsart1GetMultiProcessorMode( ) )
	{
		if( E_USART_SPEED_HIGH_SPEED == micUsart1GetSpeedMode( ) )
		{
			UBRR1 = ( CONF_FOSC_HZ / ( 8 * baudrate ) ) - 1 ; 
			o_success = TRUE;
		
		}	
	}
	
	return o_success;
}

//Set UBRRn: Baud Rate Synchronous Master mode
Boolean micUsart0SetBaudRateSynchronousMasterMode( EUsartBaudRate baudrate )
{	
	Boolean o_success = FALSE;
	
	if( TRUE == micUsart0GetMultiProcessorMode( ) )
	{
		UBRR0 = ( CONF_FOSC_HZ / ( 2 * baudrate ) ) - 1 ; 
		o_success = TRUE;
	}
	
	return o_success;
}
//Set UBRRn: Baud Rate Synchronous Master mode
Boolean micUsart1SetBaudRateSynchronousMasterMode( EUsartBaudRate baudrate )
{	
	Boolean o_success = FALSE;
	
	if( TRUE == micUsart1GetMultiProcessorMode( ) )
	{
		UBRR1 = ( CONF_FOSC_HZ / ( 2 * baudrate ) ) - 1 ; 
		o_success = TRUE;
	}
	
	return o_success;
}