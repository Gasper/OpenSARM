/**
 * 2012 OpenSARM
 * Avtor: Jernej Sorta <jernejsorta@gmail.com>
 *
 */

#if !defined(ONLY_USED) || defined(ADC_H_INCLUDED)

#include "lpc214x.h"
#include "timer.h"
#include "adc.h"

unsigned char adc_init(unsigned char adc_number, unsigned char sampling_resolution)
{
	if ((sampling_resolution < 3) || (sampling_resolution > 10) || (adc_number > 1)) {
		return 0;
	}
	else if (adc_number == 1)
	{
		AD1CR = 0x00000000;
		AD1CR |= ((10 - sampling_resolution) << CLKS) | (1 << PDN) | ((CPU_FREQ/4500 + 1) << CLKDIV);
	}
	else
	{
		AD0CR = 0x00000000;
		AD0CR |= ((10 - sampling_resolution) << CLKS) | (1 << PDN) | ((CPU_FREQ/4500 + 1) << CLKDIV);//4363 je kritična...?
	}

	return 1;
}

/*
 S to funkcio vklopimo prekinitve ob koncu pretvorbe za posamezen kanal.
 Parameter "adc_number" je številka ADP in je lahko 0(ADC0) ali 1(ADC1). Parameter "adc_channel_mask" je maska prekinitev. LSB predstavlja prekinitev na
 kanalu ADx.0, MSB pa na kanalu ADx.7, itd. Parameter "adc_global_done_flag_interrupt" ima prednost pred "adc_channel_mask" in vklopi prekinitev, ko je zastavica
 DONE postavljena. Lahko ima vrednost 0 ali 1.

 Primer uporabe:

 adc_set_interrupt(ADC0, ADx_0|ADx_1|ADx_5, 0); -> vklopi prekinitev ob končani pretvorbi na kanalih ADx_0, ADx_1 in ADx_5

 */
void adc_set_interrupt(unsigned char adc_number, unsigned char adc_channel_mask, unsigned char adc_global_done_flag_interrupt)
{
	if (adc_number & 1)
	{
		AD1INTEN = (adc_global_done_flag_interrupt > 0 ? ADGINTEN : adc_channel_mask);
	}
	else
	{
		AD0INTEN = (adc_global_done_flag_interrupt > 0 ? ADGINTEN : adc_channel_mask);
	}
}


/*
 Parameter "adc_number" je številka ADP in je lahko 0(ADC0) ali 1(ADC1).
 Funkcija vrne bajt, v katerem so željene zastavice za vse kanale (MSB od vrnjene vrednosti predstavlja zastavico kanala ADx.7, LSB pa ADx.0).
 Parameter "status_type" določa vrsto vrnjenih zastavic. Če ima vrednost 0 (DONE_FLAGS) so vrnjene DONE zastavice, če pa 1 (OVERRUN_FLAGS) pa OVERRUN zastavice.

 Primer uporabe:

 unsigned char zastavica_done0;
 zastavica_done7 = (adc_get_global_status(ADC0, DONE_FLAGS) >> ADx_7)&1;

 */
unsigned int adc_get_global_status(unsigned char adc_number, unsigned char status_type)//type==0->DONE flags are returned, type==1->OVERRUN flags are returned
{
	if (adc_number)
		return ((AD1STAT >> ((status_type > 0 ? OVERRUN_FLAGS : DONE_FLAGS) * 8)) & 0xFF);
	else
		return ((AD0STAT >> ((status_type > 0 ? OVERRUN_FLAGS : DONE_FLAGS) * 8)) & 0xFF);
}


unsigned char adc_start_conversion(unsigned char adc_number, unsigned char adc_channel, unsigned char start_source, unsigned char start_source_edge)
{

	if ((adc_number > 1) || (adc_channel > 7) || (start_source > 7) || (start_source < 1) || (start_source_edge > 1))
		return 0;

	if (adc_number == 1)
	{
		AD1CR &= 0xF0FEFF00;
		AD1CR |= (1 << adc_channel) | (start_source << START) | (start_source_edge << EDGE);
	}
	else
	{
		AD0CR &= 0xF0FEFF00;
		AD0CR |= (1 << adc_channel) | (start_source << START) | (start_source_edge << EDGE);
	}

	return 1;
}


int adc_get_result(unsigned char adc_number, unsigned char adc_channel)
{
	int result;
	if (adc_number == 1)
	{
		switch (adc_channel)
		{
			case ADx_0:
				result = (AD1DR0 >> 6) & 0x3FF;
				break;
			case ADx_1:
				result = (AD1DR1 >> 6) & 0x3FF;
				break;
			case ADx_2:
				result = (AD1DR2 >> 6) & 0x3FF;
				break;
			case ADx_3:
				result = (AD1DR3 >> 6) & 0x3FF;
				break;
			case ADx_4:
				result = (AD1DR4 >> 6) & 0x3FF;
				break;
			case ADx_5:
				result = (AD1DR5 >> 6) & 0x3FF;
				break;
			case ADx_6:
				result = (AD1DR6 >> 6) & 0x3FF;
				break;
			case ADx_7:
				result = (AD1DR7 >> 6) & 0x3FF;
				break;
			default:
				result = -1;
				break;
		}
	}
	else
	{
		switch (adc_channel)
		{
			case ADx_0:
				result = (AD0DR0 >> 6) & 0x3FF;
				break;
			case ADx_1:
				result = (AD0DR1 >> 6) & 0x3FF;
				break;
			case ADx_2:
				result = (AD0DR2 >> 6) & 0x3FF;
				break;
			case ADx_3:
				result = (AD0DR3 >> 6) & 0x3FF;
				break;
			case ADx_4:
				result = (AD0DR4 >> 6) & 0x3FF;
				break;
			case ADx_5:
				result = (AD0DR5 >> 6) & 0x3FF;
				break;
			case ADx_6:
				result = (AD0DR6 >> 6) & 0x3FF;
				break;
			case ADx_7:
				result = (AD0DR7 >> 6) & 0x3FF;
				break;
			default:
				result = -1;
				break;
		}
	}

	return result;
}


unsigned char adc_is_done(unsigned char adc_number)
{
	if (adc_number == 1)
	{
		return ((AD1GDR >> 31) & 1);
	}
	else
	{
		return ((AD0GDR >> 31) & 1);
	}
}


/*
 Ta funkcija nastavi vse potrebne registre, da analogne vhode.
 Kot parameter sprejme številko ADP (0 ali 1-> ADC0 ali ADC1) ter številko kanala.
 Kanala AD0.0 in AD0.5. Nista povezana na nobene vhode.
 V primeru, da želimo ta dva kanala vklopiti, funkcija vrne 0, sicer pa 1.

 Primer uporabe:
 adc_set_io(ADC0, ADx_1);

 */
unsigned char adc_set_io(unsigned char adc_number, unsigned char adc_channel)
{
	unsigned char wrong_ad_channel_flag = 1;

	if (adc_number & 1)
	{
		switch (adc_channel)
		{
			case ADx_0:
				PINSEL0 &= ~(0x03 << (PIN6 * 2));
				PINSEL0 |= (FUN_3 << (PIN6 * 2));
				break;
			case ADx_1:
				PINSEL0 &= ~(0x03 << (PIN8 * 2));
				PINSEL0 |= (FUN_3 << (PIN8 * 2));
				break;
			case ADx_2:
				PINSEL0 &= ~(0x03 << (PIN10 * 2));
				PINSEL0 |= (FUN_3 << (PIN10 * 2));
				break;
			case ADx_3:
				PINSEL0 &= ~(0x03 << (PIN12 * 2));
				PINSEL0 |= (FUN_3 << (PIN12 * 2));
				break;
			case ADx_4:
				PINSEL0 &= ~(0x03 << (PIN13 * 2));
				PINSEL0 |= (FUN_3 << (PIN13 * 2));
				break;
			case ADx_5:
				PINSEL0 &= ~(0x03 << (PIN15 * 2));
				PINSEL0 |= (FUN_3 << (PIN15 * 2));
				break;
			case ADx_6:
				PINSEL1	&= ~(0x03 << 10);
				PINSEL1 |= (FUN_2 << 10);
				break;
			case ADx_7:
				PINSEL1	&= ~(0x03 << 12);
				PINSEL1 |= (FUN_1 << 12);
				break;
			default:
				wrong_ad_channel_flag = 0;
				break;
		}
	}
	else
	{
		switch (adc_channel)
		{
			case ADx_0:
				wrong_ad_channel_flag = 0;
				break;
			case ADx_1:
				PINSEL1 &= ~(0x03 << 24);
				PINSEL1 |= (FUN_1 << 24);
				break;
			case ADx_2:
				PINSEL1 &= ~(0x03 << 26);
				PINSEL1 |= (FUN_1 << 26);
				break;
			case ADx_3:
				PINSEL1 &= ~(0x03 << 28);
				PINSEL1 |= (FUN_1 << 28);
				break;
			case ADx_4:
				PINSEL1 &= ~(0x03 << 18);
				PINSEL1 |= (FUN_1 << 18);
				break;
			case ADx_5:
				wrong_ad_channel_flag = 0;
				break;
			case ADx_6:
				PINSEL0 &= ~(0x03 << 8);
				PINSEL0 |= (FUN_3 << 8);
				break;
			case ADx_7:
				PINSEL0 &= ~(0x03 << 10);
				PINSEL0 |= (FUN_3 << 10);
				break;
			default:
				wrong_ad_channel_flag = 0;
				break;
		}
	}

	return wrong_ad_channel_flag;
}


unsigned char adc_set_burst_mode(unsigned char adc_number, unsigned char channel_mask)
{
	if (adc_number > 1)
		return 0;

	if (adc_number)
	{
		AD1CR &= 0xF0FFFF00;
		AD1CR |= channel_mask | (1 << BURST) | (1 << PDN);
	}
	else
	{
		AD0CR &= 0xF0FFFF00;
		AD0CR |= channel_mask | (1 << BURST) | (1 << PDN);
	}

	return 1;
}

#endif
