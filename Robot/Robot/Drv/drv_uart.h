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
#define NB_BYTES_SEND_MAX 50U

////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////

//////////////////////////////////////////PUBLIC PTR FCTS//////////////////////////////////////////
typedef void (*ptrfct_Isr_Callback_Uart_RX)( Int8U received_byte );

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////



/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUart( void ) ;



//************************************
// Method:    DrvUart0SendMessage
// FullName:  DrvUart0SendMessage
// Access:    public 
// Returns:   void
// Qualifier: on recupere le message
// Parameter: Int8U i_message[50U]		//message a recuperer
// Parameter: Int8U byte_to_send		//taille du message a recuperer 
//************************************
void DrvUart0SendMessage( Int8U i_message[50U], Int8U i_message_len ) ;

//************************************
// Method:    DrvUart1SendMessage
// FullName:  DrvUart1SendMessage
// Access:    public 
// Returns:   void
// Qualifier: on recupere le message
// Parameter: Int8U i_message[50U]		//message a recuperer
// Parameter: Int8U i_message_len		//taille du message a recuperer 
//************************************
void DrvUart1SendMessage( Int8U i_message[50U], Int8U i_message_len ) ;

//************************************
// Method:    DrvUart0ReadMessage
// FullName:  DrvUart0ReadMessage
// Access:    public 
// Returns:   void
// Qualifier: on recupere le message
// Parameter: Int8U i_message[50U]		//message a recuperer
// Parameter: Int8U byte_to_send		//taille du message a recuperer 
//************************************
void DrvUart0ReadMessage( Int8U i_message[50U], Int8U *i_message_len ) ;

//************************************
// Method:    DrvUart1ReadMessage
// FullName:  DrvUart1ReadMessage
// Access:    public 
// Returns:   void
// Qualifier: on recupere le message
// Parameter: Int8U i_message[50U]		//message a recuperer
// Parameter: Int8U i_message_len		//taille du message a recuperer 
//************************************
void DrvUart1ReadMessage( Int8U i_message[50U], Int8U *i_message_len ) ;

#endif /* DRV_UART_H_ */

