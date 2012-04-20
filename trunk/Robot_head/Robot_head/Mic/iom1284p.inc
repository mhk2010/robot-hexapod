#ifdef ENABLE_BIT_DEFINITIONS


/* Bit definitions for use with the IAR Assembler
   The Register Bit names are represented by their bit number (0-7).
*/


/* UCSR1C */
#define UMSEL11 7U
#define UMSEL10 6U
#define UPM11 5U
#define UPM10 4U
#define USBS1 3U
#define UCSZ11 2U
#define UCSZ10 1U
#define UCPOL1 0U

/* UCSR1B */
#define RXCIE1 7U
#define TXCIE1 6U
#define UDRIE1 5U
#define RXEN1 4U
#define TXEN1 3U
#define UCSZ12 2U
#define RXB81 1U
#define TXB81 0U

/* UCSR1A */
#define RXC1 7U
#define TXC1 6U
#define UDRE1 5U
#define FE1 4U
#define DOR1 3U
#define UPE1 2U
#define U2X1 1U
#define MPCM1 0U

/* UCSR0C */
#define UMSEL01 7U
#define UMSEL00 6U
#define UPM01 5U
#define UPM00 4U
#define USBS0 3U
#define UCSZ01 2U
#define UCSZ00 1U
#define UCPOL0 0U

/* UCSR0B */
#define RXCIE0 7U
#define TXCIE0 6U
#define UDRIE0 5U
#define RXEN0 4U
#define TXEN0 3U
#define UCSZ02 2U
#define RXB80 1U
#define TXB80 0U

/* UCSR0A */
#define RXC0 7U
#define TXC0 6U
#define UDRE0 5U
#define FE0 4U
#define DOR0 3U
#define UPE0 2U
#define U2X0 1U
#define MPCM0 0U

/* TWAMR */
#define TWAM6 7U
#define TWAM5 6U
#define TWAM4 5U
#define TWAM3 4U
#define TWAM2 3U
#define TWAM1 2U
#define TWAM0 1U

/* TWCR */
#define TWINT 7U
#define TWEA 6U
#define TWSTA 5U
#define TWSTO 4U
#define TWWC 3U
#define TWEN 2U
#define TWIE 0U

/* TWAR */
#define TWA6 7U
#define TWA5 6U
#define TWA4 5U
#define TWA3 4U
#define TWA2 3U
#define TWA1 2U
#define TWA0 1U
#define TWGCE 0U

/* TWSR */
#define TWS7 7U
#define TWS6 6U
#define TWS5 5U
#define TWS4 4U
#define TWS3 3U
#define TWPS1 1U
#define TWPS0 0U

/* ASSR */
#define EXCLK 6U
#define AS2 5U
#define TCN2UB 4U
#define OCR2AUB 3U
#define OCR2BUB 2U
#define TCR2AUB 1U
#define TCR2BUB 0U

/* TCCR2B */
#define FOC2A 7U
#define FOC2B 6U
#define WGM22 3U
#define CS22 2U
#define CS21 1U
#define CS20 0U

/* TCCR2A */
#define COM2A1 7U
#define COM2A0 6U
#define COM2B1 5U
#define COM2B0 4U
#define WGM21 1U
#define WGM20 0U

/* TCCR3C */
#define FOC3A 7U
#define FOC3B 6U

/* TCCR3B */
#define ICNC3 7U
#define ICES3 6U
#define WGM33 4U
#define WGM32 3U
#define CS32 2U
#define CS31 1U
#define CS30 0U

/* TCCR3A */
#define COM3A1 7U
#define COM3A0 6U
#define COM3B1 5U
#define COM3B0 4U
#define WGM31 1U
#define WGM30 0U

/* TCCR1C */
#define FOC1A 7U
#define FOC1B 6U

/* TCCR1B */
#define ICNC1 7U
#define ICES1 6U
#define WGM13 4U
#define WGM12 3U
#define CS12 2U
#define CS11 1U
#define CS10 0U

/* TCCR1A */
#define COM1A1 7U
#define COM1A0 6U
#define COM1B1 5U
#define COM1B0 4U
#define WGM11 1U
#define WGM10 0U

/* DIDR1 */
#define AIN1D 1U
#define AIN0D 0U

/* DIDR0 */
#define ADC7D 7U
#define ADC6D 6U
#define ADC5D 5U
#define ADC4D 4U
#define ADC3D 3U
#define ADC2D 2U
#define ADC1D 1U
#define ADC0D 0U

/* ADMUX */
#define REFS1 7U
#define REFS0 6U
#define ADLAR 5U
#define MUX4 4U
#define MUX3 3U
#define MUX2 2U
#define MUX1 1U
#define MUX0 0U

/* ADCSRB */
#define ACME 6U
#define ADTS2 2U
#define ADTS1 1U
#define ADTS0 0U

/* ADCSRA */
#define ADEN 7U
#define ADSC 6U
#define ADATE 5U
#define ADIF 4U
#define ADIE 3U
#define ADPS2 2U
#define ADPS1 1U
#define ADPS0 0U

/* PCMSK3 */
#define PCINT31 7U
#define PCINT30 6U
#define PCINT29 5U
#define PCINT28 4U
#define PCINT27 3U
#define PCINT26 2U
#define PCINT25 1U
#define PCINT24 0U

/* TIMSK3 */
#define ICIE3 5U
#define OCIE3B 2U
#define OCIE3A 1U
#define TOIE3 0U

/* TIMSK2 */
#define OCIE2B 2U
#define OCIE2A 1U
#define TOIE2 0U

/* TIMSK1 */
#define ICIE1 5U
#define OCIE1B 2U
#define OCIE1A 1U
#define TOIE1 0U

/* TIMSK0 */
#define OCIE0B 2U
#define OCIE0A 1U
#define TOIE0 0U

/* PCMSK2 */
#define PCINT23 7U
#define PCINT22 6U
#define PCINT21 5U
#define PCINT20 4U
#define PCINT19 3U
#define PCINT18 2U
#define PCINT17 1U
#define PCINT16 0U

/* PCMSK1 */
#define PCINT15 7U
#define PCINT14 6U
#define PCINT13 5U
#define PCINT12 4U
#define PCINT11 3U
#define PCINT10 2U
#define PCINT9 1U
#define PCINT8 0U

/* PCMSK0 */
#define PCINT7 7U
#define PCINT6 6U
#define PCINT5 5U
#define PCINT4 4U
#define PCINT3 3U
#define PCINT2 2U
#define PCINT1 1U
#define PCINT0 0U

/* EICRA */
#define ISC21 5U
#define ISC20 4U
#define ISC11 3U
#define ISC10 2U
#define ISC01 1U
#define ISC00 0U

/* PCICR */
#define PCIE3 3U
#define PCIE2 2U
#define PCIE1 1U
#define PCIE0 0U

/* PRR1 */
#define PRTIM3 0U

/* PRR0 */
#define PRTWI 7U
#define PRTIM2 6U
#define PRTIM0 5U
#define PRUSART1 4U
#define PRTIM1 3U
#define PRSPI 2U
#define PRUSART0 1U
#define PRADC 0U

/* CLKPR */
#define CLKPCE 7U
#define CLKPS3 3U
#define CLKPS2 2U
#define CLKPS1 1U
#define CLKPS0 0U

/* WDTCSR */
#define WDIF 7U
#define WDIE 6U
#define WDP3 5U
#define WDCE 4U
#define WDE  3U
#define WDP2 2U
#define WDP1 1U
#define WDP0 0U

/* SREG */
#define I 7U
#define T 6U
#define H 5U
#define S 4U
#define V 3U
#define N 2U
#define Z 1U
#define C 0U

/* SPH */
#define SP15 7U
#define SP14 6U
#define SP13 5U
#define SP12 4U
#define SP11 3U
#define SP10 2U
#define SP9 1U
#define SP8 0U
/* SPL */
#define SP7 7U
#define SP6 6U
#define SP5 5U
#define SP4 4U
#define SP3 3U
#define SP2 2U
#define SP1 1U
#define SP0 0U

/* RAMPZ */
#define RAMPZ0 0U

/* SPMCSR */
#define SPMIE 7U
#define RWWSB 6U
#define SIGRD 5U
#define RWWSRE 4U
#define BLBSET 3U
#define PGWRT 2U
#define PGERS 1U
#define SPMEN 0U

/* MCUCR */
#define JTD 7U
#define BODS 6U
#define BODSE 5U
#define PUD 4U
#define IVSEL 1U
#define IVCE 0U

/* MCUSR */
#define JTRF 4U
#define WDRF 3U
#define BORF 2U
#define EXTRF 1U
#define PORF 0U

/* SMCR */
#define SM2 3U
#define SM1 2U
#define SM0 1U
#define SE 0U

/* ACSR */
#define ACD 7U
#define ACBG 6U
#define ACO 5U
#define ACI 4U
#define ACIE 3U
#define ACIC 2U
#define ACIS1 1U
#define ACIS0 0U

/* SPSR */
#define SPIF 7U
#define WCOL 6U
#define SPI2X 0U

/* SPCR */
#define SPIE 7U
#define SPE 6U
#define DORD 5U
#define MSTR 4U
#define CPOL 3U
#define CPHA 2U
#define SPR1 1U
#define SPR0 0U

/* TCCR0B */
#define FOC0A 7U
#define FOC0B 6U
#define WGM02 3U
#define CS02 2U
#define CS01 1U
#define CS00 0U

/* TCCR0A */
#define COM0A1 7U
#define COM0A0 6U
#define COM0B1 5U
#define COM0B0 4U
#define WGM01 1U
#define WGM00 0U

/* GTCCR */
#define TSM 7U
#define PSRASY 1U
#define PSRSYNC 0U

/* EECR */
#define EEPM1 5U
#define EEPM0 4U
#define EERIE 3U
#define EEMWE 2U
#define EEWE 1U
#define EERE 0U

/* EIMSK */
#define INT2 2U
#define INT1 1U
#define INT0 0U

/* EIFR */
#define INTF2 2U
#define INTF1 1U
#define INTF0 0U

/* PCIFR */
#define PCIF3 3U
#define PCIF2 2U
#define PCIF1 1U
#define PCIF0 0U

/* TIFR3 */
#define ICF3 5U
#define OCF3B 2U
#define OCF3A 1U
#define TOV3 0U

/* TIFR2 */
#define OCF2B 2U
#define OCF2A 1U
#define TOV2 0U

/* TIFR1 */
#define ICF1 5U
#define OCF1B 2U
#define OCF1A 1U
#define TOV1 0U

/* TIFR0 */
#define OCF0B 2U
#define OCF0A 1U
#define TOV0 0U

/* PORTD */
#define PORTD7 7U
#define PORTD6 6U
#define PORTD5 5U
#define PORTD4 4U
#define PORTD3 3U
#define PORTD2 2U
#define PORTD1 1U
#define PORTD0 0U

/* DDRD */
#define DDD7 7U
#define DDD6 6U
#define DDD5 5U
#define DDD4 4U
#define DDD3 3U
#define DDD2 2U
#define DDD1 1U
#define DDD0 0U

/* PIND */
#define PIND7 7U
#define PIND6 6U
#define PIND5 5U
#define PIND4 4U
#define PIND3 3U
#define PIND2 2U
#define PIND1 1U
#define PIND0 0U

/* PORTC */
#define PORTC7 7U
#define PORTC6 6U
#define PORTC5 5U
#define PORTC4 4U
#define PORTC3 3U
#define PORTC2 2U
#define PORTC1 1U
#define PORTC0 0U

/* DDRC */
#define DDC7 7U
#define DDC6 6U
#define DDC5 5U
#define DDC4 4U
#define DDC3 3U
#define DDC2 2U
#define DDC1 1U
#define DDC0 0U

/* PINC */
#define PINC7 7U
#define PINC6 6U
#define PINC5 5U
#define PINC4 4U
#define PINC3 3U
#define PINC2 2U
#define PINC1 1U
#define PINC0 0U

/* PORTB */
#define PORTB7 7U
#define PORTB6 6U
#define PORTB5 5U
#define PORTB4 4U
#define PORTB3 3U
#define PORTB2 2U
#define PORTB1 1U
#define PORTB0 0U

/* DDRB */
#define DDB7 7U
#define DDB6 6U
#define DDB5 5U
#define DDB4 4U
#define DDB3 3U
#define DDB2 2U
#define DDB1 1U
#define DDB0 0U

/* PINB */
#define PINB7 7U
#define PINB6 6U
#define PINB5 5U
#define PINB4 4U
#define PINB3 3U
#define PINB2 2U
#define PINB1 1U
#define PINB0 0U

/* PORTA */
#define PORTA7 7U
#define PORTA6 6U
#define PORTA5 5U
#define PORTA4 4U
#define PORTA3 3U
#define PORTA2 2U
#define PORTA1 1U
#define PORTA0 0U

/* DDRA */
#define DDA7 7U
#define DDA6 6U
#define DDA5 5U
#define DDA4 4U
#define DDA3 3U
#define DDA2 2U
#define DDA1 1U
#define DDA0 0U

/* PINA */
#define PINA7 7U
#define PINA6 6U
#define PINA5 5U
#define PINA4 4U
#define PINA3 3U
#define PINA2 2U
#define PINA1 1U
#define PINA0 0U



/* Pointer definition */
#define    XL     r26
#define    XH     r27
#define    YL     r28
#define    YH     r29
#define    ZL     r30
#define    ZH     r31

/* Constants */
#define    RAMEND   0x40FFUL    /*Last On-Chip SRAM location*/
#define    XRAMEND  RAMEND
#define    E2END    0x0FFFUL
#define    FLASHEND 0x1FFFFUL

#endif /* ENABLE_BIT_DEFINITIONS */
