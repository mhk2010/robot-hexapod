/*
 * drv_uart.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_uart.h"
#include "Tools/tools_string.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

//pointeur vers la fct de callback
#ifdef CONF_UART_0_INDEX
	ptrfct_Isr_Callback_Uart_RX loc_ptrfct_Isr_Callback_Uart0_RX = NULL;
#endif
#ifdef CONF_UART_1_INDEX
	ptrfct_Isr_Callback_Uart_RX loc_ptrfct_Isr_Callback_Uart1_RX = NULL;
#endif


//UART 0
//-------
//message stocke
Int8U in_message_0[100U];
Int8U in_message_len_0 = 0U;
//buffer de recpetion de message uart 0
Int8U buff_uart_0[100U];
Int8U ptr_buff_uart_0 = 0U;
Boolean start_frame_uart_0 = FALSE;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
 
  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUart( )
{
	#ifdef CONF_UART_0_INDEX 
		UBRR0 = 0x0010U;
		micUsart0SetDataSize( USART_8_BITS_DATA ) ;
		micUsart0SetParityMode( USART_NO_PARITY ) ;
		micUsart0SetStopBits( USART_1_STOP_BIT ) ;
		micUsart0SetTransmitterEnable();
		micUsart0SetReceiverEnable();
		micUsart0SetRxInterrupt();

	#endif
			
	#ifdef CONF_UART_1_INDEX
				
		UBRR1 = 0x0010U;
		micUsart1SetDataSize( USART_8_BITS_DATA ) ;
		micUsart1SetParityMode( USART_NO_PARITY ) ;
		micUsart1SetStopBits( USART_1_STOP_BIT ) ;
		micUsart1SetTransmitterEnable();
		micUsart1SetReceiverEnable();
		micUsart1SetRxInterrupt();

	#endif
}

//envoie d'octets sur la liason serie en direct sans IT
Boolean DrvUartDirectSendBytes( const Int8U index_uart , const Int8U* ptr_byte_to_send , const Int8U nb_bytes )
{
	Boolean o_success = FALSE;
	Int8U loop_send;
	if( index_uart== E_USART_0 )
	{
		for ( loop_send = 0U ; loop_send < nb_bytes ; loop_send++ )
		{
			//on attend que le registre d'envoie soit vide
			while ( !( UCSR0A & (1<<UDRE0)) );
			UDR0 = ptr_byte_to_send [ loop_send ];
			o_success = TRUE;
		}			
	}
	if( index_uart == E_USART_1 )
	{
		for ( loop_send = 0U ; loop_send < nb_bytes ; loop_send++ )
		{
			//on attend que le registre d'envoie soit vide
			while ( !( UCSR1A & (1<<UDRE1)) );
			UDR1 = ptr_byte_to_send [ loop_send ];
			o_success = TRUE;
		}
	}	
	return o_success;
}	



//envoie de bytes sur la liason serie
Boolean DrvUartSendByte( const Int8U index_uart , Int8U byte_to_send )
{
	Boolean o_success = FALSE;
	if( index_uart== E_USART_0 )
	{
		//on attend que le registre d'envoie soit vide
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = byte_to_send;
		o_success = TRUE;
	}
	else if( index_uart == E_USART_1 )
	{
		//on attend que le registre d'envoie soit vide
		while ( !( UCSR1A & (1<<UDRE1)) );
		UDR1 = byte_to_send;
		o_success = TRUE;
	}
	return o_success;
}	

//on recupere le message
void DrvUart0ReadMessage( Int8U *i_message, Int8U *i_message_len )
{
	//on enregistre le message 
	for ( Int8U loop_send = 0U ; loop_send < in_message_len_0 ; loop_send++)
	{
		i_message[ loop_send ] = in_message_0[ loop_send ];
	} 
	*i_message_len = in_message_len_0;
}


//reception d'octets sur la liason serie
void DrvUartSetPtrfctReceiveComplete( const Int8U index_uart , ptrfct_Isr_Callback_Uart_RX ptrfct )
{
	#ifdef CONF_UART_0_INDEX
		if(index_uart == CONF_UART_0_INDEX)
		{
			loc_ptrfct_Isr_Callback_Uart0_RX = ptrfct ;
		}
	#endif
	#ifdef CONF_UART_1_INDEX
		if(index_uart == CONF_UART_1_INDEX)
		{
			loc_ptrfct_Isr_Callback_Uart1_RX = ptrfct ;
		}
	#endif
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////

//UART0
//-------------------

//ISR uart octet recu 
ISR(USART0_RX_vect)
{
	#ifdef CONF_UART_0_INDEX	
		Int8U rcv_byte = 0U;
		//on enregistre l'octet recu
		rcv_byte = UDR0;
		//si on a deja recu le start frame
		if( start_frame_uart_0 == FALSE )
        {
			//si c'est un debut de trame
			if(rcv_byte == '*' )
			{
				buff_uart_0[ 0U ] = '*';
				ptr_buff_uart_0 = 1U;
				//on a recu le start frame
				start_frame_uart_0 = TRUE;
			}
		}
		else
		{
			//on charge le message dans le buff_uart_0er
			buff_uart_0[ptr_buff_uart_0] = rcv_byte;
			ptr_buff_uart_0++;	
			if(( buff_uart_0[ptr_buff_uart_0 - 1U] == '#' ) && ( buff_uart_0[ptr_buff_uart_0 - 2U] == '#' ))
			{
				//on charge le message
				for ( Int8U loop_send = 0U ; loop_send < ptr_buff_uart_0 ; loop_send++)
				{
					in_message_0[ loop_send ] = buff_uart_0[ loop_send ];
				} 
				//on stock la taille
				in_message_len_0 = ptr_buff_uart_0;
				//on attend le start frame
				start_frame_uart_0 = FALSE;				
				//on lance l'event
				DrvEventAddEvent( CONF_EVENT_UART_MSG_RCV );
			}			
		}		
	#endif
}


//UART1
//-------------------

//ISR uart octet recu 
/*ISR(USART1_RX_vect)
{
	#ifdef CONF_UART_1_INDEX
		//on recoit un octet
		if( loc_ptrfct_Isr_Callback_Uart1_RX != NULL )
		{
			loc_ptrfct_Isr_Callback_Uart1_RX( micUsart1GetIODataRegister());
		}	
	#endif
}*/

