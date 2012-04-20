/*
 * drv_ucam.h
 *
 * Created: 30/03/2012 10:58:01
 *  Author: berryer
 */ 


#ifndef DRV_UCAM_H_
#define DRV_UCAM_H_


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


#endif /* DRV_UCAM_H_ */