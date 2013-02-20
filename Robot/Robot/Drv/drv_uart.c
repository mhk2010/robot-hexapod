/*
 * drv_uart.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_uart.h"
#include "drv_event.h"
#include "Tools/tools_string.h"

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


//UART 0
//-------
//message stocke
Int8U in_message_0[50U];
Int8U in_message_len_0 = 0U;
//buffer de recpetion de message uart 0
Int8U buff_uart_0[50U];
Int8U ptr_buff_uart_0 = 0U;
Boolean start_frame_uart_0 = FALSE;

//UART 1
//-------
//message stocke
Int8U in_message_1[50U];
Int8U in_message_len_1 = 0U;
//buffer de recpetion de message uart 0
Int8U buff_uart_1[50U];
Int8U ptr_buff_uart_1 = 0U;
Boolean start_frame_uart_1 = FALSE;
 

  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUart( )
{
	//on fixe les registres
	#ifdef CONF_UART_0_INDEX 
		UBRR0 = 0x0008U;		//57600 baud
		UCSR0B |= (1<<RXEN0);	//enable RX
		UCSR0B |= (1<<TXEN0);	//enable TX 
		UCSR0B |= (1<<RXCIE0);	//enable RX interrupt 
		UCSR0C|= (1<<UCSZ00); 	//8 bits, no parity, 1 stop 
		UCSR0C|= (1<<UCSZ01); 
	#endif
			
	#ifdef CONF_UART_1_INDEX
		UBRR1 = 0x0010U;		//57600 baud
		UCSR1B |= (1<<RXEN1);	//enable RX
		UCSR1B |= (1<<TXEN1);	//enable TX 
		UCSR1B |= (1<<RXCIE1);	//enable RX interrupt 
		UCSR1C|= (1<<UCSZ10); 	//8 bits, no parity, 1 stop 
		UCSR1C|= (1<<UCSZ11);  
	#endif
}

//on recupere le message
void DrvUart0ReadMessage( Int8U i_message[50U], Int8U *i_message_len )
{
	//on enregistre le message 
	for ( Int8U loop_send = 0U ; loop_send < in_message_len_0 ; loop_send++)
	{
		i_message[ loop_send ] = in_message_0[ loop_send ];
	} 
	*i_message_len = in_message_len_0;
}
//on recupere le message
void DrvUart0SendMessage( Int8U i_message[50U], Int8U i_message_len )
{
	//on enregistre le message 
	for ( Int8U loop_send = 0U ; loop_send < i_message_len ; loop_send++)
	{
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = i_message[ loop_send ];
	} 
}


//on recupere le message
void DrvUart1ReadMessage( Int8U i_message[50U], Int8U *i_message_len )
{
	//on enregistre le message 
	for ( Int8U loop_send = 0U ; loop_send < in_message_len_1 ; loop_send++)
	{
		i_message[ loop_send ] = in_message_1[ loop_send ];
	} 
	*i_message_len = in_message_len_1;
}

//on recupere le message
void DrvUart1SendMessage( Int8U i_message[50U], Int8U i_message_len )
{
	//on enregistre le message 
	for ( Int8U loop_send = 0U ; loop_send < i_message_len ; loop_send++)
	{
		while ( !( UCSR1A & (1<<UDRE1)) );
		UDR1 = i_message[ loop_send ];
	} 
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
				DrvEventAddEvent( CONF_EVENT_HEAD_MSG_RCV );
			}			
		}		
	#endif
}

//UART1
//-------------------
//ISR uart octet recu 
ISR(USART1_RX_vect)
{
	#ifdef CONF_UART_1_INDEX		
		Int8U rcv_byte = 0U;
		//on enregistre l'octet recu
		rcv_byte = UDR1;
		//si on a deja recu le start frame
		if( start_frame_uart_1 == FALSE )
        {
			//si c'est un debut de trame
			if(rcv_byte == '*' )
			{
				buff_uart_1[ 0U ] = '*';
				ptr_buff_uart_1 = 1U;
				//on a recu le start frame
				start_frame_uart_1 = TRUE;
			}
		}
		else
		{
			//on charge le message dans le buff_uart_0er
			buff_uart_1[ptr_buff_uart_1] = rcv_byte;
			ptr_buff_uart_1++;	
			if(( buff_uart_1[ptr_buff_uart_1 - 1U] == '#' ) && ( buff_uart_1[ptr_buff_uart_1 - 2U] == '#' ))
			{
				//on charge le message
				for ( Int8U loop_send = 0U ; loop_send < ptr_buff_uart_1 ; loop_send++)
				{
					in_message_1[ loop_send ] = buff_uart_1[ loop_send ];
				} 
				//on stock la taille
				in_message_len_1 = ptr_buff_uart_1;
				//on attend le start frame
				start_frame_uart_1 = FALSE;				
				//on lance l'event
				DrvEventAddEvent( CONF_EVENT_DIGI_MSG_RCV );
			}			
		}		
	#endif
}
