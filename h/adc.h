#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include "lpc214x.h"
#include "io.h"


#define AD0CR			(*((volatile unsigned long *) 0xE0034000))
#define AD0GDR			(*((volatile unsigned long *) 0xE0034004))
#define AD0STAT			(*((volatile unsigned long *) 0xE0034030))
#define ADGSR			(*((volatile unsigned long *) 0xE0034008))
#define AD0INTEN		(*((volatile unsigned long *) 0xE003400C))
#define AD0DR0			(*((volatile unsigned long *) 0xE0034010))
#define AD0DR1			(*((volatile unsigned long *) 0xE0034014))
#define AD0DR2			(*((volatile unsigned long *) 0xE0034018))
#define AD0DR3			(*((volatile unsigned long *) 0xE003401C))
#define AD0DR4			(*((volatile unsigned long *) 0xE0034020))
#define AD0DR5			(*((volatile unsigned long *) 0xE0034024))
#define AD0DR6			(*((volatile unsigned long *) 0xE0034028))
#define AD0DR7			(*((volatile unsigned long *) 0xE003402C))


#define AD1CR			(*((volatile unsigned long *) 0xE0060000))
#define AD1GDR			(*((volatile unsigned long *) 0xE0060004))
#define AD1STAT			(*((volatile unsigned long *) 0xE0060030))
//#define ADGSR 			(*((volatile unsigned long *) 0xE0060008))
#define AD1INTEN		(*((volatile unsigned long *) 0xE006000C))
#define AD1DR0			(*((volatile unsigned long *) 0xE0060010))
#define AD1DR1			(*((volatile unsigned long *) 0xE0060014))
#define AD1DR2			(*((volatile unsigned long *) 0xE0060018))
#define AD1DR3			(*((volatile unsigned long *) 0xE006001C))
#define AD1DR4			(*((volatile unsigned long *) 0xE0060020))
#define AD1DR5			(*((volatile unsigned long *) 0xE0060024))
#define AD1DR6			(*((volatile unsigned long *) 0xE0060028))
#define AD1DR7			(*((volatile unsigned long *) 0xE006002C))

#define DONE_FLAGS	0
#define OVERRUN_FLAGS	1
#define BURST_ON	1
#define BURST_OFF	0
#define FALLING_EDGE	1
#define RISING_EDGE	0

#define ADINTEN0	(1<<0)
#define ADINTEN1	(1<<1)
#define ADINTEN2	(1<<2)
#define ADINTEN3	(1<<3)
#define ADINTEN4	(1<<4)
#define ADINTEN5	(1<<5)
#define ADINTEN6	(1<<6)
#define ADINTEN7	(1<<7)
#define ADGINTEN	(1<<8)

#define ADC0		0
#define	ADC1		1
#define EDGE		27
#define ADC_G		2


#define START		24
#define NO_START	0
#define START_NOW	1
#define	START_MAT0_2	2
#define START_P0_16	2
#define START_P0_22	3
#define	START_MAT0_0	3
#define	START_MAT0_1	4
#define	START_MAT0_3	5
#define	START_MAT1_0	6
#define	START_MAT1_1	7


#define PDN		21
#define CLKS		17
#define CLKDIV		8
#define BURST		16

#define	CLKS_10BITS	0
#define	CLKS_9BITS	1
#define	CLKS_8BITS	2
#define	CLKS_7BITS	3
#define	CLKS_6BITS	4
#define	CLKS_5BITS	5
#define	CLKS_4BITS	6
#define	CLKS_3BITS	7

#define ADx_0		0
#define ADx_1		1
#define ADx_2		2
#define ADx_3		3
#define ADx_4		4
#define ADx_5		5
#define ADx_6		6
#define ADx_7		7


unsigned char adc_init(unsigned char adc_number, unsigned char sampling_resolution);
void adc_set_interrupt(unsigned char adc_number, unsigned char adc_channel_mask, unsigned char adc_global_done_flag_interrupt);
unsigned int adc_get_global_status(unsigned char adc_number, unsigned char status_type);
unsigned char adc_start_conversion(unsigned char adc_number, unsigned char adc_channel, unsigned char start_source, unsigned char start_source_edge);
int adc_get_result(unsigned char adc_number, unsigned char adc_channel);
unsigned char adc_is_done(unsigned char adc_number);
unsigned char adc_set_io(unsigned char adc_number, unsigned char adc_channel);

#ifdef ONLY_USED
#include "adc.c"
#endif

#endif
