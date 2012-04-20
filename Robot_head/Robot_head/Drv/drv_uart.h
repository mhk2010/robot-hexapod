/*
 * drv_uart.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef DRV_UART_H_
#define DRV_UART_H_

#include "Tools/tools_typedefs.h"
#include "Tools/tools_string.h"

#include "Conf/conf_hard.h"

#include "Mic/mic_io_ports.h"
#include "Mic/mic_usart.h"

////////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////
// nombre d'octet maximum que l'on peux envoyer en une trame
#define NB_BYTES_SEND_MAX 20U

////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////

//////////////////////////////////////////PUBLIC PTR FCTS//////////////////////////////////////////
typedef void (*ptrfct_Isr_Callback_Uart_RX)( Int8U received_byte );

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////



/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUart( void ) ;

//************************************
// Method:    DrvUartSendByte
// FullName:  DrvUartSendByte
// Access:    public 
// Returns:   void
// Qualifier: envoie d'un octet sur la liason serie
// Parameter: Int8U index_uart			//index uart conf_hard.h
// Parameter: Int8U byte_to_send		//octet a envoyer
//************************************
Boolean DrvUartSendByte( Int8U index_uart , Int8U byte_to_send ) ;

//************************************
// Method:    DrvUartDirectSendBytes
// FullName:  DrvUartDirectSendBytes
// Access:    public 
// Returns:   void
// Qualifier: envoie d'octets sur la liason serie en direct sans IT
// Parameter: Int8U index_uart			//index uart conf_hard.h
// Parameter: Int8U* ptr_byte_to_send	//ptr vers le premier des octets a envoyer
//************************************
Boolean DrvUartDirectSendBytes( const Int8U index_uart , const Int8U* ptr_byte_to_send , const Int8U nb_bytes );

//on recupere le message
void DrvUart0ReadMessage( Int8U i_message[50U], Int8U *i_message_len );

//************************************
// Method:    DrvUartSetPtrfctReceiveComplete
// FullName:  DrvUartSetPtrfctReceiveComplete
// Access:    public 
// Returns:   void
// Qualifier: recois les octet de la liason serie
// Parameter: Int8U index_uart						//index de l'uart auquel on associe le ptr de fct
// Parameter: ptrfct_Isr_Callback_Uart_RX ptrfct	//ptrfct appellé lors d'une reception 
//************************************
void DrvUartSetPtrfctReceiveComplete( const Int8U index_uart , ptrfct_Isr_Callback_Uart_RX ptrfct ) ;

#endif /* DRV_UART_H_ */

