/*
 * tools_typedefs.h
 *
 * Created: 28/06/2011 15:55:05
 *  Author: berryer
 */ 


#ifndef TOOLS_TYPEDEFS_H_
#define TOOLS_TYPEDEFS_H_

#include <avr/interrupt.h> 

#ifndef ATOMIC
  #define ATOMIC(code)                      \
    {                                       \
      cli();								\
      do{ code }while(0);                   \
      sei();								\
    }
#endif



/*
 * Basic Macros
 */
#define RAND()						(Int8U)( DrvAdcReadChannel( CONF_ADC_IR ) + DrvAdcReadChannel( CONF_ADC_LDR_GAUCHE ) + DrvAdcReadChannel( CONF_ADC_LDR_DROITE ))


#define BIT_HIGH( reg , bit )		reg |=  ( 1U << bit );
#define BIT_LOW( reg , bit )		reg &= ~( 1U << bit );
#define BIT_TOGGLE( reg , bit )		reg ^=  ( 1U << bit );
#define BIT_SET( reg , bit , val)							\
									if( val )				\
									{						\
										BIT_HIGH( reg , bit)\
									}						\
									else					\
									{						\
										BIT_LOW( reg , bit)	\
									};

/*
 * Basic types for the microcontroler
 */

// Unsigned 8 bits char
typedef char Char;

// Unsigned 8 bits integer type
typedef unsigned char Int8U;
// Unsigned 16 bits integer type
typedef unsigned int Int16U;
// Unsigned 32 bits integer type
typedef unsigned long Int32U;

// Signed 8 bits integer type
typedef signed char Int8S;
// Signed 16 bits integer type
typedef signed int Int16S;
// Signed 32 bits integer type
typedef signed long Int32S;

// Boolean type
typedef Int8U Boolean;
  #define FALSE       0U
  #define TRUE        1U

// Null pointer
#ifndef NULL
  #define NULL     ((void *)0U)
#endif

//definit un type de pointeur de fonction pour abstraire les interruptions micro
typedef void (*ptrfct_Isr_Callback)(void);



#endif /* TOOLS_TYPEDEFS_H_ */