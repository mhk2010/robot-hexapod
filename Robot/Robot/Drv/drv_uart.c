/*
 * drv_uart.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "drv_uart.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//structure qui sert a envoyer les octets sur la liaison serie
typedef struct SSUartSend
{
	Int8U loc_loop_bytes_to_send;
	Int8U loc_nb_bytes_to_send;
	Int8U loc_bytes_to_send[NB_BYTES_SEND_MAX];
}SUartSend;

//structure uart
typedef struct SSUart
{
	Boolean enable;
	EUsartBaudRate baudrate;
	EUsartDataSize datasize;
	EUsartParityMode parity;
	EUsartStopBits stop_bit;
	ptrfct_Isr_Callback_Uart_RX loc_ptrfct_Isr_Callback_Uart_RX;
	SUartSend send;
}SUart ;

//configuration initial des uarts
SUart MesUarts[ CONF_UART_NB ] = 
{
	//CONF_UART_0_INDEX
	{
		.enable		= TRUE,
		.baudrate	= USART_BAUD_9600,
		.datasize	= USART_8_BITS_DATA,
		.parity		= USART_NO_PARITY,
		.stop_bit	= USART_1_STOP_BIT,
		.loc_ptrfct_Isr_Callback_Uart_RX = NULL,
		.send = 
		{
			.loc_loop_bytes_to_send = 0U,
			.loc_nb_bytes_to_send = 0U,
		},
	},
};


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
 
  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUart( )
{
	for(Int8U loop_config = 0; loop_config < CONF_UART_NB ; loop_config++ )
	{
		if ( MesUarts[loop_config].enable == TRUE )
		{
			if( loop_config == E_USART_0 )
			{
				micUsart0SetBaudRateAsynchronousNormalMode( MesUarts[loop_config].baudrate ) ;
				micUsart0SetDataSize( MesUarts[loop_config].datasize ) ;
				micUsart0SetParityMode( MesUarts[loop_config].parity ) ;
				micUsart0SetStopBits( MesUarts[loop_config].stop_bit ) ;
				micUsart0SetTransmitterEnable();
				micUsart0SetReceiverEnable();
				micUsart0SetRxInterrupt();
				micUsart0SetTxInterrupt();
			}
			else if( loop_config == E_USART_1 )
			{
				micUsart1SetBaudRateAsynchronousNormalMode( MesUarts[loop_config].baudrate ) ;
				micUsart1SetDataSize( MesUarts[loop_config].datasize ) ;
				micUsart1SetParityMode( MesUarts[loop_config].parity ) ;
				micUsart1SetStopBits( MesUarts[loop_config].stop_bit ) ;
				micUsart1SetTransmitterEnable();
				micUsart1SetReceiverEnable();
				micUsart1SetRxInterrupt();
				micUsart1SetTxInterrupt();
			}
			else
			{
				break;
			}
		}
	}
}

//envoie d'un string sur la liason serie
Boolean DrvUartSendString( Int8U index_uart , Char* string )
{
	Boolean o_success = FALSE;
	//on cherhce le carcatere nul //fin de trame
	Int8U index_fin = TlsStringSearchCaract( string, 0x00, NB_BYTES_SEND_MAX);
	if( index_fin > 0 )
	{
		o_success = TRUE;	
	}
	DrvUartSendBytes( index_uart , (Int8U*)string , index_fin ) ;
	return o_success;
}	

//envoie d'octets sur la liason serie
Boolean DrvUartSendBytes( Int8U index_uart , Int8U* ptr_byte_to_send , Int8U nb_bytes )
{
	Boolean o_success = FALSE;
	
	//on envoie le premier octet l'it TX se charge de faire la suite
	o_success = DrvUartSendByte( index_uart , ptr_byte_to_send[0U] );
		
	//on charge les variables locales
	MesUarts[index_uart].send.loc_loop_bytes_to_send = 0U;
	MesUarts[index_uart].send.loc_nb_bytes_to_send = nb_bytes;
	for ( Int8U loop_send = 1U ; loop_send <= NB_BYTES_SEND_MAX ; loop_send++ )
	{
		MesUarts[index_uart].send.loc_bytes_to_send[ loop_send - 1 ] = ptr_byte_to_send[ loop_send ];
	}
	
	return o_success;		
}

//envoie de bytes sur la liason serie
Boolean DrvUartSendByte( Int8U index_uart , Int8U byte_to_send )
{
	Boolean o_success = FALSE;
	if( index_uart== E_USART_0 )
	{
		//on attend que le registre d'envoie soit vide
		while ( !micUsart0GetDataRegisterEmpty() );
		micUsart0SetIODataRegister( byte_to_send );
		micUsart0SetTransmitCompleted();
		o_success = TRUE;
	}
	else if( index_uart == E_USART_1 )
	{
		//on attend que le registre d'envoie soit vide
		while ( !micUsart1GetDataRegisterEmpty() );
		micUsart1SetIODataRegister( byte_to_send );
		micUsart1SetTransmitCompleted();
		o_success = TRUE;
	}
	return o_success;
}	

//reception d'octets sur la liason serie
void DrvUartSetPtrfctReceiveComplete( Int8U index_uart , ptrfct_Isr_Callback_Uart_RX ptrfct )
{
	MesUarts[index_uart].loc_ptrfct_Isr_Callback_Uart_RX = ptrfct ;
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////

//UART0
//-------------------

//ISR uart octet recu 
ISR(USART0_RX_vect)
{
	#ifdef CONF_UART_0_INDEX
		//on recoit un octet
		if( MesUarts[CONF_UART_0_INDEX].loc_ptrfct_Isr_Callback_Uart_RX != NULL )
		{
			MesUarts[ CONF_UART_0_INDEX ].loc_ptrfct_Isr_Callback_Uart_RX( micUsart0GetIODataRegister());
		}		
	#endif
}

//ISR uart octet envoyé
ISR(USART0_TX_vect)
{
	#ifdef CONF_UART_0_INDEX
		//on envoie les octets tant qu'il y en a
		if (MesUarts[ CONF_UART_0_INDEX ].send.loc_nb_bytes_to_send > MesUarts[ CONF_UART_0_INDEX ].send.loc_loop_bytes_to_send + 1U )
		{
			DrvUartSendByte( CONF_UART_0_INDEX , MesUarts[ CONF_UART_0_INDEX ].send.loc_bytes_to_send[ MesUarts[ CONF_UART_0_INDEX ].send.loc_loop_bytes_to_send++ ] );
		}
		else
		{
			//on remet a zero les variables locales
			MesUarts[ CONF_UART_0_INDEX ].send.loc_loop_bytes_to_send = 0U;
			MesUarts[ CONF_UART_0_INDEX ].send.loc_nb_bytes_to_send = 0U;
		}
	#endif
}


//UART1
//-------------------

//ISR uart octet recu 
ISR(USART1_RX_vect)
{
	#ifdef CONF_UART_1_INDEX
		//on recoit un octet
		if( MesUarts[CONF_UART_1_INDEX].loc_ptrfct_Isr_Callback_Uart_RX != NULL )
		{
			MesUarts[ CONF_UART_1_INDEX ].loc_ptrfct_Isr_Callback_Uart_RX( micUsart1GetIODataRegister());
		}	
	#endif
}

//ISR uart octet envoyé
ISR(USART1_TX_vect)
{
	#ifdef CONF_UART_1_INDEX
		//on envoie les octets tant qu'il y en a
		if (MesUarts[ CONF_UART_1_INDEX ].send.loc_nb_bytes_to_send > MesUarts[ CONF_UART_1_INDEX ].send.loc_loop_bytes_to_send + 1U )
		{
			DrvUartSendByte( CONF_UART_1_INDEX , MesUarts[ CONF_UART_1_INDEX ].send.loc_bytes_to_send[ MesUarts[ CONF_UART_1_INDEX ].send.loc_loop_bytes_to_send++ ] );
		}
		else
		{
			//on remet a zero les variables locales
			MesUarts[ CONF_UART_1_INDEX ].send.loc_loop_bytes_to_send = 0U;
			MesUarts[ CONF_UART_1_INDEX ].send.loc_nb_bytes_to_send = 0U;
		}
	#endif
}