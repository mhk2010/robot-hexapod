/*
 * ctrl_camera.c
 *
 * Created: 14/11/2011 15:35:40
 *  Author: berryer
 */ 

#include "ctrl_camera.h"

#include "Drv/drv_ucam.h"
#include "Drv/drv_uart.h"

////////////////////////////////////////PRIVATE DEFINES/////////////////////////////////////////
#define START_FRAME			0xAAU
#define FRAME_LENGHT		6U

#define NB_RETRIES			60U

#define CMD_INITIAL			0x01U
#define CMD_GET_PICTURE		0x04U
#define CMD_SNAPSHOT		0x05U
#define CMD_RESET			0x08U
#define CMD_DATA			0x0AU
#define CMD_SYNC			0x0DU
#define CMD_ACK				0x0EU
#define CMD_NACK			0x0FU

#define GRAY_SCALE_2_BIT	0x01U
#define GRAY_SCALE_4_BIT	0x02U
#define GRAY_SCALE_8_BIT	0x03U
#define COLOR_8_BIT			0x04U
#define COLOR_12_BIT		0x05U
#define COLOR_16_BIT		0x06U
#define JPEG				0x07U

#define RES_80_60			0x01U
#define RES_160_120			0x03U
#define RES_320_240			0x05U
#define RES_640_480			0x07U
#define RES_128_128			0x09U
#define RES_128_96			0x0BU

#define GET_PICTURE_TYPE_SNAPSHOT	0x01U
#define GET_PICTURE_TYPE_RAW		0x02U
#define GET_PICTURE_TYPE_JPEG		0x03U

#define SNAPSHOT_TYPE_RAW			0x01U

#define NB_PIXELS_PAR_BYTES			0x04U

#define WIDTH				80U
#define HEIGHT				60U 

#define WIDTH_DIV_3				WIDTH / 3U
#define WIDTH_2_DIV_3			(2 * WIDTH) / 3U
#define HEIGHT_DIV_3			HEIGHT / 3U
#define HEIGHT_2_DIV_3			(2 * HEIGHT) / 3U

#define IMAGE_BYTES_SIZE	( ( HEIGHT * WIDTH ) / NB_PIXELS_PAR_BYTES )

//seuille de detection de mouvements
#define SEUILLAGE_MOUVEMENT_LOW		0x0AU
#define SEUILLAGE_MOUVEMENT_MEDIUM	0x08U
#define SEUILLAGE_MOUVEMENT_HIGH	0x03U



////////////////////////////////////////PRIVATE STUCTURES/////////////////////////////////////////
//structure de l'etat de l a camera
typedef struct EEStateCamera
{
	Boolean rcv_sync_ack;
	Boolean rcv_nack;
	Boolean rcv_set_ack;
	Boolean rcv_get_picture_ack;
	Boolean send_get_picture;
	Boolean rcv_data;
	Boolean rcv_data_complete;
	Int8U timeout;
	Int8U ack_id;
	Int8U nb_retries;
}EStateCamera;

// structure image
typedef struct SSImage
{
	Int16U index ;
	Int16U size ;
	Int8U image [ IMAGE_BYTES_SIZE ] ;
}SImage;

//structure protocole
typedef struct SSCamera
{
	SImage *image;
	EStateCamera state;
	Boolean enable;
	Boolean power;
	Boolean get_images;
	Int8U waitting;
}SCamera;



////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//permet de prendre deux images a la suite
void CtrlCameraGetPicture( void ) ;
//on envoie un ack camera 
static void CtrlCameraCmdAck( Int8U ack_number ) ;
//on synchronise la camera 
static void CtrlCameraCmdSynchro( void ) ;
//on set la camera 
static void CtrlCameraCmdSettings( void ) ;
//on prend l'image
static void CtrlCameraCmdGetPicture( void ) ;
//active la camera
static void CtrlCameraEnable( Boolean enable ) ;
//permet de recuperer l'image apres event
static void CtrlCameraSetStructPicture( SImage * i_image ) ;
// permet de faire le seuillage sur l'image
static Boolean CtrlCameraSeuillage( void ) ;
//machine d'etat de connexion avec la camera
static void CtrlCameraStateMachine( void ) ;
//on envoie la trame sur l'uart
static void CtrlCameraExecuteSendUartMovement( void ) ;
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//structre de la camera
volatile SCamera cam;

//cmd camera
Int8U camera_ack[] = {START_FRAME,CMD_ACK,0x00,0x00,0x00,0x00} ;
	
const Int8U camera_sync[] = {START_FRAME,CMD_SYNC,0x00,0x00,0x00,0x00} ;
	
const Int8U camera_initial[] = {START_FRAME,CMD_INITIAL,0x00,GRAY_SCALE_2_BIT,RES_80_60,0x00} ;
	
const Int8U camera_get_picture[] = {START_FRAME,CMD_GET_PICTURE,GET_PICTURE_TYPE_RAW,0x00,0x00,0x00} ;
	
const Int8U camera_reset[] = {START_FRAME,CMD_RESET,0x00,0x00,0x00,0x00} ;
	
	
//UART frame decode
Int8U start_trame = FALSE;
Int16U index_cam_uart = 0U;
static Int8U recpt_cmd_frame_cam[6U] ;

//structure image
static SImage mes_images[2U];
static Int8U index_image = 0U;
static Boolean can_comp_image = FALSE;

//tableau mouvements
Int8U compress_tab_mvt[600];


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//init
void CtrlCamera( void ) 
{ 
	cam.power = FALSE;
	cam.enable = FALSE;
	cam.waitting = 0U;
	cam.get_images = FALSE;
	
	cam.state.timeout = 0U;
	cam.state.rcv_sync_ack = FALSE;
	cam.state.rcv_nack = FALSE;
	cam.state.rcv_set_ack = FALSE;
	cam.state.rcv_get_picture_ack = FALSE;
	cam.state.send_get_picture = FALSE;
	cam.state.rcv_data = FALSE;
	cam.state.rcv_data_complete = FALSE;
	cam.state.nb_retries = 0U;
	cam.state.ack_id = 0U;
	can_comp_image = FALSE;
	
	//on ective la camera
	CtrlCameraEnable( TRUE );
	
	//on veux enregistrer sur l'image 1
	CtrlCameraSetStructPicture(&mes_images[index_image]);
	
	CtrlCameraGetPicture();
}

//permet de prendre deux images a la suite
void CtrlCameraGetPicture( void ) 
{
	cam.get_images = TRUE;
}

	
//active la camera
static void CtrlCameraEnable( Boolean enable ) 
{
	cam.enable = enable;
}


//permet de recuperer l'image apres event
static void CtrlCameraSetStructPicture( SImage * i_image ) 
{
	cam.image = i_image;
}	
	


//dispatcher
void CtrlCameraDispatcher( Event_t event ) 
{
	if( cam.enable == TRUE)
	{	
		//Test de connexion
		if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_100MS ))
		{	
			if( cam.power == TRUE )
			{		
				//on lance la prochaine capture d'iamge
				if(cam.state.rcv_data_complete == TRUE)
				{
					cam.state.rcv_data_complete = FALSE;
						
					//on change de pointeur sur le record de la prochaine image	
					/*if(index_image == 0U)
					{		
						index_image = 1U;						
					}
					else
					{
						index_image = 0U;
						//on a recus 2 images 
						//on peux faire une comparaison
						can_comp_image = TRUE;
					}
				
					//charge sur la prochaine image
					CtrlCameraSetStructPicture(&mes_images[index_image]);
				
					//on compare les images pour avoir la diff
					if( can_comp_image == TRUE )
					{
						//on fait un premier seuilage pour voir les difference entre les 2
						if (TRUE == CtrlCameraSeuillage() ) 
						{
								
						}
						
					}*/				
					//on envoie la diff d'image sur l'uart
					CtrlCameraExecuteSendUartMovement();
					
					//on remet les données a jour
					cam.image->size = 0U ;
					cam.image->index = 0U ;
			
					//on prend une nouvelle image
					cam.state.rcv_get_picture_ack = FALSE ; 
					cam.state.send_get_picture = FALSE ;
					cam.state.rcv_data = FALSE;
				}
				

				if( cam.get_images == TRUE)
				{	
					//on gere la machine d'etat 
					CtrlCameraStateMachine();
				}
			}			
		}
		//on active la camera apres 1S
		if ( DrvEventTestEvent(event ,CONF_EVENT_TIMER_1S ))
		{
			//on attend 2 sec pour l'allumage
			if ((cam.power == FALSE) && (cam.waitting > 2))
			{
				cam.power = TRUE;
				cam.waitting = 0U;
				cam.state.timeout = 0U;
				cam.state.rcv_sync_ack = FALSE;
				cam.state.rcv_nack = FALSE;
				cam.state.rcv_set_ack = FALSE;
				cam.state.rcv_get_picture_ack = FALSE;
				cam.state.send_get_picture = FALSE;
				cam.state.rcv_data = FALSE;
				cam.state.rcv_data_complete = FALSE;
				cam.state.nb_retries = 0U;
				cam.state.ack_id = 0U;
				can_comp_image = FALSE;
				micIoPortsConfigureOutput(CONF_CMD_ALIM_CAMERA);
				micIoPortsConfigureToLowLevel(CONF_CMD_ALIM_CAMERA);

			}
			else
			{
				//on a l'alim power 
				if(cam.power == TRUE)
				{
					//si on a pas recu de ack apres un get picture
					if( ( cam.state.rcv_get_picture_ack == FALSE ) && ( cam.state.send_get_picture == TRUE )  && ( cam.state.timeout > 1 ))
					{
						//on reinit la camera
						micIoPortsConfigureToHighLevel(CONF_CMD_ALIM_CAMERA);
						CtrlCamera();
						cam.waitting = 0;
					}
					else
					{	
						cam.state.timeout++;			
					}
				}
				else
				{
					cam.waitting++;
				}
			}
		}	
		//On a recu une image
		if ( DrvEventTestEvent(event ,CONF_EVENT_CAM_PICT_RCV ) )
		{
			//on confirme la reception
			CtrlCameraCmdAck( 0x00 );
			cam.state.rcv_data_complete = TRUE;
						
		}	
	}				
}


// permet de faire le seuillage sur l'image
static Boolean CtrlCameraSeuillage( void ) 
{
	Int16U loop_pix = 0U ;
	Int8U mvt_detect = 0U;
	Int8U index_pix = 0;
	Int16U index_octet_pix = 0;
	
	Boolean o_success = FALSE;
					
	for (loop_pix = 0; loop_pix < IMAGE_BYTES_SIZE; loop_pix++)
	{
		static Int8U pix11;
		static Int8U pix22;
		pix11 = (mes_images[ 0 ].image[ loop_pix ] & 0xF0 )>>4;
		pix22 = (mes_images[ 1 ].image[ loop_pix ] & 0xF0 )>>4;				
		
		//pix11 = mes_images[ 0 ].image[ loop_pix ];
		//pix22 = mes_images[ 1 ].image[ loop_pix ];
			
		if( index_pix == 8 )
		{
			index_pix = 0;
			index_octet_pix++;
			compress_tab_mvt[ index_octet_pix ]=0;
		}
		
				
		//on seuille le pixel poid faible
		if( pix11 > pix22 )
		{
			if ((pix11 - pix22 ) > SEUILLAGE_MOUVEMENT_HIGH)
			{
				compress_tab_mvt[ index_octet_pix ] |= (1 << (7-(index_pix)));
				mvt_detect++;
			}
			else
			{
				compress_tab_mvt[ index_octet_pix ] &= ~(1 << (7-(index_pix)));
			}
		}
		else
		{
			if ((pix22 - pix11 ) > SEUILLAGE_MOUVEMENT_HIGH)
			{
				compress_tab_mvt[ index_octet_pix ] |= (1 << (7-(index_pix)));
				mvt_detect++;
			}
			else
			{
				compress_tab_mvt[ index_octet_pix ] &= ~(1 << (7-(index_pix)));
			}
		}
			
		index_pix++;	
		pix11 = (mes_images[ 0 ].image[ loop_pix ] & 0x0F );
		pix22 = (mes_images[ 1 ].image[ loop_pix ] & 0x0F );				
		//on seuille le pixel poid faible
		if( pix11 > pix22 )
		{
			if ((pix11 - pix22 ) > SEUILLAGE_MOUVEMENT_HIGH)
			{
				compress_tab_mvt[ index_octet_pix ] |= (1 << (7-(index_pix)));
				mvt_detect++;
			}
			else
			{
				compress_tab_mvt[ index_octet_pix ] &= ~(1 << (7-(index_pix)));
			}
		}
		else
		{
			if ((pix22 - pix11 ) > SEUILLAGE_MOUVEMENT_HIGH)
			{
				compress_tab_mvt[ index_octet_pix ] |= (1 << (7-(index_pix)));
				mvt_detect++;
			}
			else
			{
				compress_tab_mvt[ index_octet_pix ] &= ~(1 << (7-(index_pix)));
			}
		}
		index_pix++;
	}
	
	if(mvt_detect > 5U)
	{
		o_success = TRUE;		
	}
	return o_success;
}	


//on envoie la trame sur l'uart
static void CtrlCameraExecuteSendUartMovement(void) 
{
	Int8U buffer[27];
	static Int16U loop_mvt = 0U;
	static Int16U loop_area = 0U;
	for ( loop_area = 0U; loop_area < 1200U ; loop_area += 20U)
	{
		buffer[0] = '*';
		buffer[1] = E_PROTOCOLE_HEAD;
		buffer[2] = E_PROTOCOLE_WHO_CAMERA;
		buffer[3] = loop_area >> 8U;
		buffer[4] = loop_area ;
		for (loop_mvt = 0U; loop_mvt < 20U ; loop_mvt++)
		{
			buffer[5 + loop_mvt] = cam.image->image/* compress_tab_mvt*/[ loop_area + loop_mvt ] ;
		}	
		buffer[25] = '#';
		buffer[26] = '#';
		DrvUartDirectSendBytes(CONF_UART_0_INDEX,buffer,27U);
	}	
}	


//machine d'etat de connexion avec la camera
static void CtrlCameraStateMachine( void ) 
{
	//on essaye de se synchroniser 
	if( ( cam.state.nb_retries < NB_RETRIES ) && ( cam.state.rcv_sync_ack == FALSE ) )
	{
		//on rallume la camera apres avoir recu un NACK
		if(cam.state.rcv_nack == TRUE)
		{
			micIoPortsConfigureToLowLevel(CONF_CMD_ALIM_CAMERA);
		}				
		//on essaye de synchroniser
		CtrlCameraCmdSynchro();
					
	}
	//on a pas reussi s a la synchro
	else if( cam.state.nb_retries >= NB_RETRIES )
	{
		cam.power = FALSE;
		cam.enable = FALSE;
		cam.waitting = 0U;
		cam.get_images = FALSE;
	
		cam.state.timeout = 0U;
		cam.state.rcv_sync_ack = FALSE;
		cam.state.rcv_nack = FALSE;
		cam.state.rcv_set_ack = FALSE;
		cam.state.rcv_get_picture_ack = FALSE;
		cam.state.send_get_picture = FALSE;
		cam.state.rcv_data = FALSE;
		cam.state.rcv_data_complete = FALSE;
		cam.state.nb_retries = 0U;
		cam.state.ack_id = 0U;
		can_comp_image = FALSE;
	
		//on ective la camera
		CtrlCameraEnable( TRUE );
	
		CtrlCameraGetPicture();
	}
	//on envoie une cmd de setting
	else if(( cam.state.rcv_sync_ack == TRUE ) && ( cam.waitting < 5U ) )
	{
		cam.waitting++;
	}
	//on envoie une cmd de setting
	else if(( cam.state.rcv_sync_ack == TRUE ) && ( cam.state.rcv_set_ack == FALSE ) )
	{
		cam.waitting = 0U;
		CtrlCameraCmdSettings();
	}
	//on envoie une cmd de pour recuperer l'image
	else if(( cam.state.rcv_set_ack == TRUE ) && ( cam.state.rcv_get_picture_ack == FALSE ) && ( cam.state.send_get_picture == FALSE ))
	{
		CtrlCameraCmdGetPicture();
		cam.state.timeout = 0U;
		cam.state.send_get_picture = TRUE;
	}
	else
	{
		//MISRA 
	}		
}


//callback de la reception UART ISR
ISR(USART1_RX_vect)
{
//static void CtrlCameraCmdCallbackCamera_ISR( Int8U received_byte )
//{
	Int8U received_byte = UDR1;
	//si on capture image
	if (cam.state.rcv_data == TRUE)
	{
		cam.image->image[ cam.image->index++ ] = received_byte;
		if( cam.image->index == cam.image->size )	
		{
			//on ajoute l'event
			DrvEventAddEvent(CONF_EVENT_CAM_PICT_RCV);
		}
	}
	else 
	{
		//si on a recu un start
		if( start_trame == TRUE )
		{		
			recpt_cmd_frame_cam[ index_cam_uart++ ] = received_byte ;

			if(index_cam_uart == 6)
			{
				start_trame = FALSE;
				//on a recu un NACk on eteind l'alim de la camera 
				if ( recpt_cmd_frame_cam[ 1U ] == CMD_NACK)
				{
					micIoPortsConfigureToHighLevel(CONF_CMD_ALIM_CAMERA);
					cam.state.rcv_nack = TRUE;
				}
				//on traite la commande			
				else
				{
					cam.state.rcv_nack = FALSE;
					index_cam_uart = 0U;	
					//si la cam ACk la sync
					if( ( recpt_cmd_frame_cam[ 1U ] == CMD_ACK) && ( recpt_cmd_frame_cam[ 2U ] == CMD_SYNC))
					{
						cam.state.ack_id = recpt_cmd_frame_cam[ 3U ];						
					}
					else if( recpt_cmd_frame_cam[ 1U ] == CMD_SYNC )
					{
						//on envoie le ack
						CtrlCameraCmdAck(cam.state.ack_id);
						cam.state.ack_id = 0;
						cam.state.rcv_sync_ack = TRUE;						
					}
					else if( ( recpt_cmd_frame_cam[ 1U ] == CMD_ACK) && ( recpt_cmd_frame_cam[ 2U ] == CMD_INITIAL))
					{
						cam.state.rcv_set_ack = TRUE;	
					}
					else if( ( recpt_cmd_frame_cam[ 1U ] == CMD_ACK) && ( recpt_cmd_frame_cam[ 2U ] == CMD_GET_PICTURE))
					{
						cam.state.rcv_get_picture_ack = TRUE;	
					}
					else if( ( recpt_cmd_frame_cam[ 1U ] == CMD_DATA ) && ( recpt_cmd_frame_cam[ 2U ] == GET_PICTURE_TYPE_RAW))
					{
						cam.image->size = (( recpt_cmd_frame_cam[ 4U ] << 8 ) | recpt_cmd_frame_cam[ 3U ]);
						cam.state.rcv_data = TRUE;	
					}
					else
					{
						//MISRA oblige
					}
				}				
			}
		}
		else
		{
			//si le premier byte est un Start 
			if( received_byte == START_FRAME )
			{
				start_trame = TRUE;
				recpt_cmd_frame_cam[ 0 ] = START_FRAME ;
				index_cam_uart = 1U;
			}
		}	
	}									
}



//on envoie un reset 
static void CtrlCameraCmdReset( void ) 
{
	DrvUartDirectSendBytes(CONF_UART_1_INDEX, camera_reset, FRAME_LENGHT);
}

//on envoie un ack camera 
static void CtrlCameraCmdAck( Int8U ack_number ) 
{
	camera_ack[2] = ack_number;
	DrvUartDirectSendBytes(CONF_UART_1_INDEX, camera_ack, FRAME_LENGHT);
}

//on synchronise la camera 
static void CtrlCameraCmdSynchro( void ) 
{
	//on fixe l'etat de la cam
	cam.state.rcv_sync_ack = FALSE;
	DrvUartDirectSendBytes(CONF_UART_1_INDEX, camera_sync, FRAME_LENGHT);
	//on incremente les reties
	cam.state.nb_retries++;
}	

//on set la camera 
static void CtrlCameraCmdSettings( void ) 
{
	//on fixe l'etat de la cam
	cam.state.rcv_set_ack = FALSE;
	DrvUartDirectSendBytes(CONF_UART_1_INDEX, camera_initial, FRAME_LENGHT);
}	

//on prend l'image
static void CtrlCameraCmdGetPicture( void ) 
{
	//on fixe l'etat de la cam
	cam.state.rcv_get_picture_ack = FALSE;
	DrvUartDirectSendBytes(CONF_UART_1_INDEX, camera_get_picture, FRAME_LENGHT);
}


