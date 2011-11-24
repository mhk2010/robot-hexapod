/*
 * mic_usart.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef MIC_USART_H_
#define MIC_USART_H_

#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"


/////////////////////////////////////////PUBLIC ENUMS/////////////////////////////////////////
typedef enum EEUsartIndex
{
  E_USART_0 ,
  E_USART_1 ,
  E_USART_NONE ,
}EUsartIndex;

typedef enum EEUsartError
{
  E_USART_FRAMING_ERROR = (1U << FE0),
  E_USART_OVERRUN_ERROR = (1U << DOR0),
  E_USART_PARITY_ERROR	= (1U << UPE0)
}EUsartError;

typedef enum EEUsartSpeedMode
{
  E_USART_SPEED_NORMAL		= (0U << U2X0),
  E_USART_SPEED_HIGH_SPEED	= (1U << U2X0),
}EUsartSpeedMode;

typedef enum EEUsartDataSize
{
  USART_5_BITS_DATA = ((0U << UCSZ02) | (((0U << UCSZ01) | (0U << UCSZ00)) >> 1)),
  USART_6_BITS_DATA = ((0U << UCSZ02) | (((0U << UCSZ01) | (1U << UCSZ00)) >> 1)),
  USART_7_BITS_DATA = ((0U << UCSZ02) | (((1U << UCSZ01) | (0U << UCSZ00)) >> 1)),
  USART_8_BITS_DATA = ((0U << UCSZ02) | (((1U << UCSZ01) | (1U << UCSZ00)) >> 1)),
  USART_9_BITS_DATA = ((1U << UCSZ02) | (((0U << UCSZ01) | (0U << UCSZ00)) >> 1))
}EUsartDataSize;

typedef enum EEUsartParityMode
{ 
  USART_NO_PARITY		= ((0U << UPM01) | (0U << UPM00)),
  USART_EVEN_PARITY	= ((1U << UPM01) | (0U << UPM00)),
  USART_ODD_PARITY	= ((1U << UPM01) | (1U << UPM00))
}EUsartParityMode;

typedef enum EEUsartStopBits
{ 
  USART_1_STOP_BIT  = (0U << USBS0),
  USART_2_STOP_BIT  = (1U << USBS0),
}EUsartStopBits;


typedef enum EEUsartClockPolarity
{ 
  USART_0_CLOCK_POLARITY_0 = (0U << UCPOL0),
  USART_0_CLOCK_POLARITY_1 = (1U << UCPOL0)
}EUsartClockPolarity;

typedef enum EEUsartBaudRate
{ 
  USART_BAUD_300	= 300U,
  USART_BAUD_600	= 600U,
  USART_BAUD_1200	= 1200U,
  USART_BAUD_2400	= 2400U,
  USART_BAUD_4800	= 4800U,
  USART_BAUD_9600	= 9600U,
  USART_BAUD_14400	= 14400U,
  USART_BAUD_19200	= 19200U,
  USART_BAUD_28800	= 28800U,
  USART_BAUD_38400	= 38400U,
  USART_BAUD_57600	= 54600U,
  USART_BAUD_76800	= 76800U,
  USART_BAUD_115200	= 115200U,
}EUsartBaudRate;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//set the UDRn – USART I/O Data Register 0
Boolean micUsart0SetIODataRegister( Int8U udr0 ) ;
//set the UDRn – USART I/O Data Register 1
Boolean micUsart1SetIODataRegister( Int8U udr1 ) ;

//Get the UDRn – USART I/O Data Register 0
Int8U micUsart0GetIODataRegister( void ) ;
//Get the UDRn – USART I/O Data Register 1
Int8U micUsart1GetIODataRegister( void ) ;

//Get the UDREn: USART Data Register Empty
Boolean micUsart0GetRegisterEmpty( void ) ;
//Get the UDREn: USART Data Register Empty
Boolean micUsart1GetRegisterEmpty( void ) ;

//Get the Error bits -> Framing, Data Overrun and Parity
EUsartError micUsart0GetError( void ) ;
//Get the Error bits -> Framing, Data Overrun and Parity
EUsartError micUsart1GetError( void ) ;

//Set the U2Xn: Double the USART Transmission Speed
void micUsart0SetSpeedMode( EUsartSpeedMode mode ) ;
//Set the U2Xn: Double the USART Transmission Speed
void micUsart1SetSpeedMode( EUsartSpeedMode mode ) ;

//Get the U2Xn: Double the USART Transmission Speed
EUsartSpeedMode micUsart0GetSpeedMode( void ) ;
//Get the U2Xn: Double the USART Transmission Speed
EUsartSpeedMode micUsart1GetSpeedMode( void ) ;

//Set the MPCMn: Multi-processor Communication Mode
Boolean micUsart0SetMultiProcessorMode( void ) ;
//Set the MPCMn: Multi-processor Communication Mode
Boolean micUsart1SetMultiProcessorMode( void ) ;

//Get the MPCMn: Multi-processor Communication Mode
Boolean micUsart0GetMultiProcessorMode( void ) ;
//Get the MPCMn: Multi-processor Communication Mode
Boolean micUsart1GetMultiProcessorMode( void ) ;

//Get the RXCn: USART Receive Complete
Boolean micUsart0GetReceiptCompleted( void ) ;
//Get the RXCn: USART Receive Complete
Boolean micUsart1GetReceiptCompleted( void ) ;

//Set the TXCn: USART Transmit Complete
Boolean micUsart0SetTransmitCompleted( void ) ;
//Set the TXCn: USART Transmit Complete
Boolean micUsart1SetTransmitCompleted( void ) ;

//Get the TXCn: USART Transmit Complete
Boolean micUsart0GetTransmitCompleted( void ) ;
//Get the TXCn: USART Transmit Complete
Boolean micUsart1GetTransmitCompleted( void ) ;

//Get the UDREn: USART Data Register Empty
Boolean micUsart0GetDataRegisterEmpty( void ) ;
//Get the UDREn: USART Data Register Empty
Boolean micUsart1GetDataRegisterEmpty( void ) ;

//Set the TXENn: Transmitter Enable 0
Boolean micUsart0SetTransmitterEnable( void ) ;
//Set the TXENn: Transmitter Enable 0
Boolean micUsart1SetTransmitterEnable( void ) ;

//Set the TXENn: Transmitter Disable 0
Boolean micUsart0SetTransmitterDisable( void ) ;
//Set the TXENn: Transmitter Disable 0
Boolean micUsart1SetTransmitterDisable( void ) ;

//Set the RXENn: Receiver Enable 0
Boolean micUsart0SetReceiverEnable( void ) ;
//Set the RXENn: Receiver Enable 0
Boolean micUsart1SetReceiverEnable( void ) ;

//Set the RXENn: Receiver Disable 0
Boolean micUsart0SetReceiverDisable( void ) ;
//Set the RXENn: Receiver Disable 0
Boolean micUsart1SetReceiverDisable( void ) ;

//Set the UCSZn : Character Size n
Boolean micUsart0SetDataSize( EUsartDataSize data_size ) ;
//Set the UCSZn : Character Size n
Boolean micUsart1SetDataSize( EUsartDataSize data_size ) ;

//Set the UPMn1:0: Parity Mode
Boolean micUsart0SetParityMode( EUsartParityMode parity_mode ) ;
//Set the UPMn1:0: Parity Mode
Boolean micUsart1SetParityMode( EUsartParityMode parity_mode ) ;

//Set the USBSn: Stop Bit Select
Boolean micUsart0SetStopBits( EUsartStopBits stop_bits) ;
//Set the USBSn: Stop Bit Select
Boolean micUsart1SetStopBits( EUsartStopBits stop_bits) ;

//set RXCIEn: RX Complete Interrupt Enable 0
Boolean micUsart0SetRxInterrupt( void ) ;
//set RXCIEn: RX Complete Interrupt Enable 0
Boolean micUsart1SetRxInterrupt( void ) ;

//Clear RXCIEn: RX Complete Interrupt Enable 0
Boolean micUsart0ClearRxInterrupt( void ) ;
//Clear RXCIEn: RX Complete Interrupt Enable 0
Boolean micUsart1ClearRxInterrupt( void ) ;

//Set TXCIEn: TX Complete Interrupt Enable 0
Boolean micUsart0SetTxInterrupt( void ) ;
//Set TXCIEn: TX Complete Interrupt Enable 0
Boolean micUsart1SetTxInterrupt( void ) ;

//Clear TXCIEn: TX Complete Interrupt Enable 0
Boolean micUsart0ClearTxInterrupt( void ) ;
//Clear TXCIEn: TX Complete Interrupt Enable 0
Boolean micUsart1ClearTxInterrupt( void ) ;

//Set UDRIEn: USART Data Register Empty Interrupt Enable n
Boolean micUsart0SetDataRegisterEmptyInterrupt( void ) ;
//Set UDRIEn: USART Data Register Empty Interrupt Enable n
Boolean micUsart1SetDataRegisterEmptyInterrupt( void ) ;

//Clear UDRIEn: USART Data Register Empty Interrupt Enable n
Boolean micUsart0ClearDataRegisterEmptyInterrupt( void ) ;
//Clear UDRIEn: USART Data Register Empty Interrupt Enable n
Boolean micUsart1ClearDataRegisterEmptyInterrupt( void ) ;

//Set UCPOLn: Clock Polarity
Boolean micUsart0SetSynchronousClockPolarity( EUsartClockPolarity polarity ) ;
//Set UCPOLn: Clock Polarity
Boolean micUsart1SetSynchronousClockPolarity( EUsartClockPolarity polarity ) ;

//Set UBRRn: Baud Rate Synchronous Master mode
Boolean micUsart0SetBaudRateAsynchronousNormalMode( EUsartBaudRate baudrate ) ;	
//Set UBRRn: Baud Rate Synchronous Master mode
Boolean micUsart1SetBaudRateAsynchronousNormalMode( EUsartBaudRate baudrate ) ;	

//Set UBRRn: Baud Rate Asynchronous Double Speed mode (U2Xn = 1)
Boolean micUsart0SetBaudRateAsynchronousDoubleSpeedMode( EUsartBaudRate baudrate ) ;
//Set UBRRn: Baud Rate Asynchronous Double Speed mode (U2Xn = 1)
Boolean micUsart1SetBaudRateAsynchronousDoubleSpeedMode( EUsartBaudRate baudrate ) ;

//Set UBRRn: Baud Rate Asynchronous Normal mode (U2Xn = 0)
Boolean micUsart0SetBaudRateSynchronousMasterMode( EUsartBaudRate baudrate ) ;
//Set UBRRn: Baud Rate Asynchronous Normal mode (U2Xn = 0)
Boolean micUsart1SetBaudRateSynchronousMasterMode( EUsartBaudRate baudrate ) ;

#endif /* MIC_USART_H_ */