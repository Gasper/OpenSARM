/**
 * 2012 OpenSARM
 * Avtor: Jernej Sorta <jernejsorta@gmail.com>
 *
 */

#ifdef TIMER_H_INCLUDED

#include "lpc214x.h"
#include "io.h"
#include "timer.h"


/*
 S fjo nastavimo časovnik/števec. Kot parameter prejme številko števca/časovnika (TC0 ali TC1), način delovanja (timer_counter = "TIMER" ali "COUNTER").
 Prejme še kot parameter frekvenco delovanja, ki je uporabna samo, če je nastavljen kot časovnik. Če je nastavljen kot časovnik pa zadnja dva parametra nista uporabna.
 Če ga nastavimo kot števec (timer_counter = "COUNTER"), potem predzadnji parameter nastavlja vhod za uro. Možne vrednosti so:
	-CRx_0	0
	-CRx_1	1
	-CRx_2	2
	-CRx_3	3

	Na željenem vhodu za uro ne smemo nastavljati vhodnega zaznavanja!!

 */

unsigned char tc_init(unsigned char tc_number, unsigned char timer_counter, unsigned int frequency, unsigned char counter_clk_source, unsigned char counter_mode)
{
	if ((frequency > (CPU_FREQ * 1000)) || (counter_clk_source > 3) || (counter_mode < 1) || (counter_mode > 3))
		return 0;

	if (tc_number & 1)
	{
		if (timer_counter == COUNTER)
		{
			#define __INPUT_CLK1__
			T1CTCR |= (counter_mode) | (counter_clk_source << COUNT_INPUT_SELECT);
		}
		else
		{
			#ifndef __TC_STATE__
			T1TCR = (1 << COUNTER_RESET);
			#endif
			T1PR = CPU_FREQ * 1000 / frequency - 1;
		}
	}
	else
	{
		if (timer_counter == COUNTER)
		{
			#define __INPUT_CLK0__ c
			T0CTCR |= (counter_mode) | (counter_clk_source << COUNT_INPUT_SELECT);
		}
		else
		{
			#ifndef __TC_STATE__
			T0TCR = (1 << COUNTER_RESET);
			#endif
			T0PR = CPU_FREQ * 1000 / frequency - 1;
		}
	}

	return 1;
}

/*
 S fjo nastavimo stanje časovnika(TC_number = TC0 ali TC1). Če ima parameter "state" vrednost "COUNTER_ENABLE", potem se števec zažene. Če ima
 vrednost "COUNTER_RESET", potem se števec ponastavi in ustavi. Ponovno ga poženemo z "COUNTER_ENABLE".
 */

void tc_state(unsigned char tc_number, unsigned char state)
{
	#define __TC_STATE__
	if (tc_number)
	{
		if (state == COUNTER_ENABLE)
			T1TCR = 1;
		else
			T1TCR = 0;	//Counter reset
	}
	else
	{
		if (state == COUNTER_ENABLE)
			T0TCR = 1;
		else
			T0TCR = 0;	//Counter reset
	}
}


/*
 Zakasnitev za določeno število ms. Deluje neodvisno od frekvence časovnika(da ga lahko hkrati uporabljamo še za kakžno drugo stvar),
 dokler je frekvenca višja od 1kHz. Parameter "reset" določa način delovanja.
 Če ima vrednost "NO_RESET" (0), bo časovnik tekel nemoteno, vendar se program utegne obesiti po približno 49,7 dneh(takrat se števec samodejno ponastavi).
 Če pa ima vrednost "RESET", potem se časovnik vsakič znova ponastavi in je ta težava odpravljena. Žal pa zato časovnika ne moremo nemoteno uporabiti še za
 kakšno drugo stvar.
 */

void delay_ms(unsigned char tc_number, unsigned int mili_sec, unsigned char reset)
{
	//Variables are declared on the beginning of the function for more accurate delay
	unsigned int t1_val = T1TC;
	unsigned int t0_val = T0TC;
	if (tc_number)
	{
		if (reset == NO_RESET)
		{
			while (!(T1TC == mili_sec * (CPU_FREQ / (T1PR + 1)) + t1_val));
		}
		else
		{
			T1TCR = 2; //Reset TC
			T1TCR = 1; //Enable TC
			while (!(T1TC == mili_sec * (CPU_FREQ / (T1PR + 1)))); //1kHz
		}
	}
	else
	{
		if (reset == NO_RESET)
		{
			while(!(T0TC == mili_sec * (CPU_FREQ / (T0PR + 1)) + t0_val));
		}
		else
		{
			T0TCR = 2;
			T0TCR = 1;
			while (!(T0TC == mili_sec * (CPU_FREQ / (T0PR + 1))) ); //1kHz
		}
	}
}



/*
 * Fja vrne stanje prekinitve. Če vrne vrednost 1, potem se je zgodila prekinitev, če vrne 0, pa se ni.
 Če je vnešena napačna številka zastavice, fja vrne -1, sicer pa stanje prekinitve.
 Možni parametri so številka časovnika(0 (TC0) ali 1 (TC1)) in številka zastavice, ki je lahko:

MR0_IF 	0
MR1_IF 	1
MR2_IF 	2
MR3_IF 	3
CR0_IF 	4
CR1_IF 	5
CR2_IF 	6
CR3_IF 	7
 */
char tc_get_interrupt_status(unsigned char tc_number, unsigned char flag_num)
{
	if (flag_num > 7)
		return -1;

	if (tc_number)
		return (T1IR >> flag_num) & 1;
	else
		return (T0IR >> flag_num) & 1;
}

/*
 Kot argument sprejme številko časovnika, številko primerjalnega registra (če je več kot 3, vrne -1), ter vrednost.
 */
char tc_set_match_register(unsigned char tc_number, unsigned char register_number, unsigned int value)
{
	if (register_number > 3)
		return -1;

	if (tc_number)
	{
		switch (register_number)
		{
			case MR0:
				T1MR0 = value;
				break;
			case MR1:
				T1MR1 = value;
				break;
			case MR2:
				T1MR2 = value;
				break;
			case MR3:
				T1MR3 = value;
				break;
		}
	}
	else
	{
		switch (register_number)
		{
			case MR0:
				T0MR0 = value;
				break;
			case MR1:
				T0MR1 = value;
				break;
			case MR2:
				T0MR2 = value;
				break;
			case MR3:
				T0MR3 = value;
				break;
		}
	}

	return 1;
}



/*
 Fja nastavi dogodek, ki naj se zgodi, ko je vrednost match registra enaka vrednosti števca.
 Izbiramo lahko med:

INTERRUPT_ON_MATCH	1	->prekinitev ob ujemanju
RESET_ON_MATCH		2	->ponastavitev števca ob ujemanju
STOP_ON_MATCH		4	->ustavitev števca ob ujemanju

oziroma željeni kombinaciji teh treh.

Možne številke registrov so:
MR0	0
MR1	1
MR2	2
MR3	3
 */

char tc_set_match_control(unsigned char tc_number, unsigned char register_number, unsigned char match_mode)
{
	if ((register_number > 3) || (match_mode > 7))
		return -1;

	if (tc_number)
	{
		T1MCR &= ~(0x07 << (register_number * 3));		//first delete posible previous settings
		T1MCR |= match_mode << (register_number * 3);
	}
	else
	{
		T0MCR &= ~(0x07 << (register_number * 3));		//first delete posible previous settings
		T0MCR |= match_mode << (register_number * 3);
	}

	return 1;
}



/*
 Fja vrne vrednost zaznavnega registra. Kot številko registra lahko prejme:

CRx_0	0
CRx_1	1
CRx_2	2
CRx_3	3

Kot številko števca pa 0 (TC0) ali 1 (TC1).
 */
unsigned int tc_get_capture_value(unsigned char tc_number, unsigned char register_number)
{
	if (register_number > 3)
		return 0;

	if (tc_number)
	{
		switch (register_number)
		{
			case CRx_0:
				return T1CR0;
			case CRx_1:
				return T1CR1;
			case CRx_2:
				return T1CR2;
			case CRx_3:
				return T1CR3;
		}
	}
	else
	{
		switch (register_number)
		{
			case CRx_0:
				return T0CR0;
			case CRx_1:
				return T0CR1;
			case CRx_2:
				return T0CR2;
			case CRx_3:
				return T0CR3;
		}
	}

	return 0;
}



/*
 Fja nastavi potrebne V/I, ter nastavi način oziroma dogodek vhodnega zaznavanja. Možni dogodki so:

CAPTURE_ON_RISING_EDGE	1
CAPTURE_ON_FALLING_EDGE	2
INTERRUPT_ON_CAPTURE	4



Z "register_number" izberemo željeni register. Izbiramo lahko med:

CRx_0	0
CRx_1	1
CRx_2	2
CRx_3	3

 */
char tc_set_capture_control(unsigned char tc_number, unsigned char register_number, unsigned char capture_mode)
{
	//in case trying to configure capture input, that is used for input clk for counter
	#ifdef __INPUT_CLK1__
	if (((T1CTCR >> 2) & 0x03) == register_number)
		return -1;
	#endif

	#ifdef __INPUT_CLK0__
	if (((T0CTCR >> 2) & 0x03) == register_number)
		return -1;
	#endif

	if ((register_number > 3) || (capture_mode > 7))
		return -1;

	if (tc_number)
	{
		T1CCR &= ~(0x07 << (register_number * 3));		//first delete posible previous settings
		T1CCR |= capture_mode << (register_number * 3);
	}
	else
	{
		T0CCR &= ~(0x07 << (register_number * 3));		//first delete posible previous settings
		T0CCR |= capture_mode << (register_number * 3);
	}

	return 1;
}


/*
S parametrom capture_pin_num lahko izberemo vhod za zaznavanje. Ker so nekatere možnosti speljane na več sponk(npr. CAP0_0 je speljana na P0.2, P0.22, ter P0.30).
S številkami od 0 do 2 izberermo zaporedno številko vhoda. Za CAP0_0: če izberemo 0 je vhod na P0.2, če izberemo 1 je na P0.22, če pa 2, pa je na P0.30.
Nekatere možnosti so speljane na samo eno sponko, zato zanje ta parameter nima vpliva.

Z "register_number" izberemo željeni register. Izbiramo lahko med:

CRx_0	0
CRx_1	1
CRx_2	2
CRx_3	3


*/
char tc_io_capture_config(unsigned char tc_number, unsigned char register_number, unsigned char capture_pin_num)
{
	if (register_number > 3)
		return -1;

	if(tc_number)
	{
		switch(register_number)
		{
			case CRx_0:
				PINSEL0 &= ~(0x3 << (PIN10 << 1));	//first delete posible previous settings
				PINSEL0 |= (FUN_2 << (PIN10 << 1));
				IODIR0 &= ~(1 << PIN10);
				break;
			case CRx_1:
				PINSEL0 &= ~(0x3 << (PIN11 << 1));	//first delete posible previous settings
				PINSEL0 |= (FUN_2 << (PIN11 << 1));
				IODIR0 &= ~(1 << PIN11);
				break;
			case CRx_2:
				if (capture_pin_num == 0)
				{
					PINSEL1 &= ~(0x3 << 2);	//first delete posible previous settings
					PINSEL1 |= (FUN_1 << 2);
					IODIR0 &= ~(1 << PIN17);
				}
				else
				{
					PINSEL1 &= ~(0x3 << 6);	//first delete posible previous settings
					PINSEL1 |= (FUN_3 << 6);
					IODIR0 &= ~(1 << PIN19);
				}
				break;
			case CRx_3:
				if (capture_pin_num == 0)
				{
					PINSEL1 &= ~(0x3 << 4);	//first delete posible previous settings
					PINSEL1 |= (FUN_1 << 4);
					IODIR0 &= ~(1 << PIN18);
				}
				else
				{
					PINSEL1 &= ~(0x3 << 10);	//first delete posible previous settings
					PINSEL1 |= (FUN_3 << 10);
					IODIR0 &= ~(1 << PIN21);
				}
		 		break;
	 	}
	}
	else
	{
		switch (register_number)
		{
			case CRx_0:
				if (capture_pin_num == 0)
				{
					PINSEL0 &= ~(0x3 << (PIN2 * 2));	//first delete posible previous settings
					PINSEL0 |= (FUN_2 << (PIN2*2));
					IODIR0 &= ~(1 << PIN2);
				}
				else if (capture_pin_num == 1)
				{
					PINSEL1 &= ~(0x3 << 12);	//first delete posible previous settings
					PINSEL1 |= (FUN_2 << 12);
					IODIR0 &= ~(1 << PIN22);
				}
				else
				{
					PINSEL1 &= ~(0x3 << 28);	//first delete posible previous settings
					PINSEL1 |= (FUN_3 << 28);
					 IODIR0 &= ~(1 << PIN30);
				}
				break;
		 	case CRx_1:
				PINSEL0 &= ~(0x3 << (PIN4 << 1));	//first delete posible previous settings
				PINSEL0 |= (FUN_2 << (PIN4 << 1));
				IODIR0 &= ~(1 << PIN4);
		 		break;
		 	case CRx_2:
				if (capture_pin_num == 0)
				{
					PINSEL0 &= ~(0x3 << (PIN6 << 1));	//first delete posible previous settings
					PINSEL0 |= (FUN_2 << (PIN6 << 1));
					IODIR0 &= ~(1 << PIN6);
				}
				else if (capture_pin_num == 1)
				{
					PINSEL1 &= ~(0x3);	//first delete posible previous settings
					PINSEL1 |= (FUN_3);
					IODIR0 &= ~(1 << PIN16);
				}
				else
				{
					PINSEL1 &= ~(0x3 << 24);	//first delete posible previous settings
					PINSEL1 |= (FUN_2 << 24);
					IODIR0 &= ~(1 << PIN28);
				}
				break;
			case CRx_3:
				PINSEL1 &= ~(0x3 << 29);	//first delete posible previous settings
				PINSEL1 |= (FUN_2 << 29);
				IODIR0 &= ~(1 << PIN29);
				break;
		}
	}

	return 1;
}

#endif
