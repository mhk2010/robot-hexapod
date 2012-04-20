/****************************************************************************
 **             - iom1284P.h -
 **
 **     This file declares the internal register addresses for ATmega1284P.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright 2007 IAR Systems AB. All rights reserved.
 **
 **     File version: $Revision: 8192 $
 **
 ***************************************************************************/

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#include "iomacro.h"

#if TID_GUARD(3)
#error This file should only be compiled with iccavr or aavr with processor option -v3
#endif /* TID_GUARD(3) */

#ifndef __IOM1284P_H


/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#define    RESET_vect          (0x00) /* External Pin, Power-on Reset, Brown-out Reset,
                                         Watchdog Reset, and JTAG AVR Reset */
#define    INT0_vect           (0x04) /* External Interrupt Request 0 */
#define    INT1_vect           (0x08) /* External Interrupt Request 1 */
#define    INT2_vect           (0x0C) /* External Interrupt Request 2 */
#define    PCINT0_vect         (0x10) /* Pin Change Interrupt Request 0 */
#define    PCINT1_vect         (0x14) /* Pin Change Interrupt Request 1 */
#define    PCINT2_vect         (0x18) /* Pin Change Interrupt Request 2 */
#define    PCINT3_vect         (0x1C) /* Pin Change Interrupt Request 3 */
#define    WDT_vect            (0x20) /* Watchdog Time-out Interrupt */
#define    TIMER2_COMPA_vect   (0x24) /* Timer/Counter2 Compare Match A */
#define    TIMER2_COMPB_vect   (0x28) /* Timer/Counter2 Compare Match B */
#define    TIMER2_OVF_vect     (0x2C) /* Timer/Counter2 Overflow */
#define    TIMER1_CAPT_vect    (0x30) /* Timer/Counter1 Capture Event */
#define    TIMER1_COMPA_vect   (0x34) /* Timer/Counter1 Compare Match A */
#define    TIMER1_COMPB_vect   (0x38) /* Timer/Counter1 Compare Match B */
#define    TIMER1_OVF_vect     (0x3C) /* Timer/Counter1 Overflow */
#define    TIMER0_COMPA_vect   (0x40) /* Timer/Counter0 Compare Match A */
#define    TIMER0_COMPB_vect   (0x44) /* Timer/Counter0 Compare match B */
#define    TIMER0_OVF_vect     (0x48) /* Timer/Counter0 Overflow */
#define    SPI_STC_vect        (0x4C) /* SPI Serial Transfer Complete */
#define    USART0_RX_vect      (0x50) /* USART0 Rx Complete */
#define    USART0_UDRE_vect    (0x54) /* USART0 Data Register Empty */
#define    USART0_TX_vect      (0x58) /* USART0 Tx Complete */
#define    ANALOG_COMP_vect    (0x5C) /* Analog Comparator */
#define    ADC_vect            (0x60) /* ADC Conversion Complete */
#define    EE_READY_vect       (0x64) /* EEPROM Ready */
#define    TWI_vect            (0x68) /* 2-wire Serial Interface */
#define    SPM_READY_vect      (0x6C) /* Store Program Memory Ready */
#define    USART1_RX_vect      (0x70) /* USART1 Rx Complete */
#define    USART1_UDRE_vect    (0x74) /* USART1 Data Register Empty */
#define    USART1_TX_vect      (0x78) /* USART1 Tx Complete */
#define    TIMER3_CAPT_vect    (0x7C) /* Timer/Counter3 Capture Event */
#define    TIMER3_COMPA_vect   (0x80) /* Timer/Counter3 Compare Match A */
#define    TIMER3_COMPB_vect   (0x84) /* Timer/Counter3 Compare Match B */
#define    TIMER3_OVF_vect     (0x88) /* Timer/Counter3 Overflow */

#ifdef __IAR_SYSTEMS_ASM__
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#include "bitdefinitions/iom1284p.inc"
#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* __IOM1284P_H (define part) */


/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IOM1284P_H) || defined(__IAR_SYSTEMS_ASM__)
#define __IOM1284P_H

#pragma language=save
#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call,
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call,
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union {
 *              unsigned char TCCR2;
 *              struct {
 *                      unsigned char TCCR2_Bit0:1,
 *                                    TCCR2_Bit1:1,
 *                                    TCCR2_Bit2:1,
 *                                    TCCR2_Bit3:1,
 *                                    TCCR2_Bit4:1,
 *                                    TCCR2_Bit5:1,
 *                                    TCCR2_Bit6:1,
 *                                    TCCR2_Bit7:1;
 *                     };
 *              struct {
 *                      unsigned char TCCR2_CS20:1,
 *                                    TCCR2_CS21:1,
 *                                    TCCR2_CS22:1,
 *                                    TCCR2_WGM21:1,
 *                                    TCCR2_COM20:1,
 *                                    TCCR2_COM21:1,
 *                                    TCCR2_WGM20:1,
 *                                    TCCR2_FOC2:1;
 *                     };
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5);
 * or if ENABLE_BIT_DEFINITIONS is defined
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

SFR_B_R(0xCE, UDR1)
SFR_W_R(0xCC, UBRR1)
SFR_B_N(0xCA, UCSR1C, UMSEL11, UMSEL10, UPM11, UPM10, USBS1, UCSZ11, UCSZ10, UCPOL1)
SFR_B_N(0xC9, UCSR1B, RXCIE1, TXCIE1, UDRIE1, RXEN1, TXEN1, UCSZ12, RXB81, TXB81)
SFR_B_N(0xC8, UCSR1A, RXC1, TXC1, UDRE1, FE1, DOR1, UPE1, U2X1, MPCM1)
SFR_B_R(0xC6, UDR0)
SFR_W_R(0xC4, UBRR0)
SFR_B_N(0xC2, UCSR0C, UMSEL01, UMSEL00, UPM01, UPM00, USBS0, UCSZ01, UCSZ00, UCPOL0)
SFR_B_N(0xC1, UCSR0B, RXCIE0, TXCIE0, UDRIE0, RXEN0, TXEN0, UCSZ02, RXB80, TXB80)
SFR_B_N(0xC0, UCSR0A, RXC0, TXC0, UDRE0, FE0, DOR0, UPE0, U2X0, MPCM0)
SFR_B_N(0xBD, TWAMR, TWAM6, TWAM5, TWAM4, TWAM3, TWAM2, TWAM1, TWAM0, Dummy0)
SFR_B_N(0xBC, TWCR, TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN, Dummy1, TWIE)
SFR_B_R(0xBB, TWDR)
SFR_B_N(0xBA, TWAR, TWA6, TWA5, TWA4, TWA3, TWA2, TWA1, TWA0, TWGCE)
SFR_B_N(0xB9, TWSR, TWS7, TWS6, TWS5, TWS4, TWS3, Dummy2, TWPS1, TWPS0)
SFR_B_R(0xB8, TWBR)
SFR_B_N(0xB6, ASSR, Dummy7, EXCLK, AS2, TCN2UB, OCR2AUB, OCR2BUB, TCR2AUB, TCR2BUB)
SFR_B_R(0xB4, OCR2B)
SFR_B_R(0xB3, OCR2A)
SFR_B_R(0xB2, TCNT2)
SFR_B_N(0xB1, TCCR2B, FOC2A, FOC2B, Dummy5, Dummy4, WGM22, CS22, CS21, CS20)
SFR_B_N(0xB0, TCCR2A, COM2A1, COM2A0, COM2B1, COM2B0, Dummy3, Dummy2, WGM21, WGM20)
SFR_W_R(0x9A, OCR3B)
SFR_W_R(0x98, OCR3A)
SFR_W_R(0x96, ICR3)
SFR_W_R(0x94, TCNT3)
SFR_B_N(0x92, TCCR3C, FOC3A, FOC3B, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0x91, TCCR3B, ICNC3, ICES3, Dummy5, WGM33, WGM32, CS32, CS31, CS30)
SFR_B_N(0x90, TCCR3A, COM3A1, COM3A0, COM3B1, COM3B0, Dummy3, Dummy2, WGM31, WGM30)
SFR_W_R(0x8A, OCR1B)
SFR_W_R(0x88, OCR1A)
SFR_W_R(0x86, ICR1)
SFR_W_R(0x84, TCNT1)
SFR_B_N(0x82, TCCR1C, FOC1A, FOC1B, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0x81, TCCR1B, ICNC1, ICES1, Dummy5, WGM13, WGM12, CS12, CS11, CS10)
SFR_B_N(0x80, TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, Dummy3, Dummy2, WGM11, WGM10)
SFR_B_N(0x7F, DIDR1, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, AIN1D, AIN0D)
SFR_B_N(0x7E, DIDR0, ADC7D, ADC6D, ADC5D, ADC4D, ADC3D, ADC2D, ADC1D, ADC0D)
SFR_B_N(0x7C, ADMUX, REFS1, REFS0, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0)
SFR_B_N(0x7B, ADCSRB, Dummy7, ACME, Dummy5, Dummy4, Dummy3, ADTS2, ADTS1, ADTS0)
SFR_B_N(0x7A, ADCSRA, ADEN, ADSC, ADATE, ADIF, ADIE, ADPS2, ADPS1, ADPS0)
SFR_W_R(0x78, ADC)
SFR_B_N(0x73, PCMSK3, PCINT31, PCINT30, PCINT29, PCINT28, PCINT27, PCINT26, PCINT25, PCINT24)
SFR_B_N(0x71, TIMSK3, Dummy7, Dummy6, ICIE3, Dummy4, Dummy3, OCIE3B, OCIE3A, TOIE3)
SFR_B_N(0x70, TIMSK2, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCIE2B, OCIE2A, TOIE2)
SFR_B_N(0x6F, TIMSK1, Dummy7, Dummy6, ICIE1, Dummy4, Dummy3, OCIE1B, OCIE1A, TOIE1)
SFR_B_N(0x6E, TIMSK0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCIE0B, OCIE0A, TOIE0)
SFR_B_N(0x6D, PCMSK2, PCINT23, PCINT22, PCINT21, PCINT20, PCINT19, PCINT18, PCINT17, PCINT16)
SFR_B_N(0x6C, PCMSK1, PCINT15, PCINT14, PCINT13, PCINT12, PCINT11, PCINT10, PCINT9, PCINT8)
SFR_B_N(0x6B, PCMSK0, PCINT7, PCINT6, PCINT5, PCINT4, PCINT3, PCINT2, PCINT1, PCINT0)
SFR_B_N(0x69, EICRA, Dummy7, Dummy6, ISC21, ISC20, ISC11, ISC10, ISC01, ISC00)
SFR_B_N(0x68, PCICR, Dummy7, Dummy6, Dummy5, Dummy4, PCIE3, PCIE2, PCIE1, PCIE0)
SFR_B_R(0x66, OSCCAL)
SFR_B_N(0x65, PRR1, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, PRTIM3)
SFR_B_N(0x64, PRR0, PRTWI, PRTIM2, PRTIM0, PRUSART1, PRTIM1, PRSPI, PRUSART0, PRADC)
SFR_B_N(0x61, CLKPR, CLKPCE, Dummy6, Dummy5, Dummy4, CLKPS3, CLKPS2, CLKPS1, CLKPS0)
SFR_B_N(0x60, WDTCSR, WDIF, WDIE, WDP3, WDCE, WDE, WDP2, WDP1, WDP0)
SFR_B_N(0x3F, SREG, I, T, H, S, V, N, Z, C)
SFR_W_N(0x3D, SP, SP15, SP14, SP13, SP12, SP11, SP10, SP9, SP8, SP7, SP6, SP5, SP4, SP3, SP2, SP1, SP0)
SFR_B_N(0x3B, RAMPZ, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, RAMPZ0)
SFR_B_N(0x37, SPMCSR, SPMIE, RWWSB, SIGRD, RWWSRE, BLBSET, PGWRT, PGERS, SPMEN)
SFR_B_N(0x35, MCUCR, JTD, BODS, BODSE, PUD, Dummy3, Dummy2, IVSEL, IVCE)
SFR_B_N(0x34, MCUSR, Dummy7, Dummy6, Dummy5, JTRF, WDRF, BORF, EXTRF, PORF)
SFR_B_N(0x33, SMCR, Dummy7, Dummy6, Dummy5, Dummy4, SM2, SM1, SM0, SE)
SFR_B_R(0x31, OCDR)
SFR_B_N(0x30, ACSR, ACD, ACBG, ACO, ACI, ACIE, ACIC, ACIS1, ACIS0)
SFR_B_R(0x2E, SPDR)
SFR_B_N(0x2D, SPSR, SPIF, WCOL, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, SPI2X)
SFR_B_N(0x2C, SPCR, SPIE, SPE, DORD, MSTR, CPOL, CPHA, SPR1, SPR0)
SFR_B_R(0x2B, GPIOR2)
SFR_B_R(0x2A, GPIOR1)
SFR_B_R(0x28, OCR0B)
SFR_B_R(0x27, OCR0A)
SFR_B_R(0x26, TCNT0)
SFR_B_N(0x25, TCCR0B, FOC0A, FOC0B, Dummy5, Dummy4, WGM02, CS02, CS01, CS00)
SFR_B_N(0x24, TCCR0A, COM0A1, COM0A0, COM0B1, COM0B0, Dummy3, Dummy2, WGM01, WGM00)
SFR_B_N(0x23, GTCCR, TSM, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, PSR2, PSR54310)
SFR_W_R(0x21, EEAR)
SFR_B_R(0x20, EEDR)
SFR_B_N(0x1F, EECR, Dummy7, Dummy6, EEPM1, EEPM0, EERIE, EEMWE, EEWE, EERE)
SFR_B_R(0x1E, GPIOR0)
SFR_B_N(0x1D, EIMSK, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, INT2, INT1, INT0)
SFR_B_N(0x1C, EIFR, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, INTF2, INTF1, INTF0)
SFR_B_N(0x1B, PCIFR, Dummy7, Dummy6, Dummy5, Dummy4, PCIF3, PCIF2, PCIF1, PCIF0)
SFR_B_N(0x18, TIFR3, Dummy7, Dummy6, ICF3, Dummy4, Dummy3, OCF3B, OCF3A, TOV3)
SFR_B_N(0x17, TIFR2, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCF2B, OCF2A, TOV2)
SFR_B_N(0x16, TIFR1, Dummy7, Dummy6, ICF1, Dummy4, Dummy3, OCF1B, OCF1A, TOV1)
SFR_B_N(0x15, TIFR0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCF0B, OCF0A, TOV0)
SFR_B_N(0x0B, PORTD, PORTD7, PORTD6, PORTD5, PORTD4, PORTD3, PORTD2, PORTD1, PORTD0)
SFR_B_N(0x0A, DDRD, DDD7, DDD6, DDD5, DDD4, DDD3, DDD2, DDD1, DDD0)
SFR_B_N(0x09, PIND, PIND7, PIND6, PIND5, PIND4, PIND3, PIND2, PIND1, PIND0)
SFR_B_N(0x08, PORTC, PORTC7, PORTC6, PORTC5, PORTC4, PORTC3, PORTC2, PORTC1, PORTC0)
SFR_B_N(0x07, DDRC, DDC7, DDC6, DDC5, DDC4, DDC3, DDC2, DDC1, DDC0)
SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
SFR_B_N(0x05, PORTB, PORTB7, PORTB6, PORTB5, PORTB4, PORTB3, PORTB2, PORTB1, PORTB0)
SFR_B_N(0x04, DDRB, DDB7, DDB6, DDB5, DDB4, DDB3, DDB2, DDB1, DDB0)
SFR_B_N(0x03, PINB, PINB7, PINB6, PINB5, PINB4, PINB3, PINB2, PINB1, PINB0)
SFR_B_N(0x02, PORTA, PORTA7, PORTA6, PORTA5, PORTA4, PORTA3, PORTA2, PORTA1, PORTA0)
SFR_B_N(0x01, DDRA, DDA7, DDA6, DDA5, DDA4, DDA3, DDA2, DDA1, DDA0)
SFR_B_N(0x00, PINA, PINA7, PINA6, PINA5, PINA4, PINA3, PINA2, PINA1, PINA0)



#pragma language=restore

#ifndef __IAR_SYSTEMS_ASM__

#include "iom1284p.inc"
#endif

#endif /* __IOM1284P_H (SFR part) */
