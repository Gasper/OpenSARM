/**
 * 2012 OpenSARM
 * Avtor: Jernej Sorta <jernejsorta@gmail.com>
 *
 */

#ifdef UART_H_INCLUDED

#include "lpc214x.h"
#include "io.h"
#include "uart.h"


/*
 Fja sprejme kot parameter številko UART vmesnika (UART_0 ali UART_1), bitno hitrost(baud_rate->naj bo standardna: 9600, 115200, itd...), število
 bitov, ki se bodo prenašali(number_of_bits->običajno 8), število stop bitov (1 ali 2), vklop parnosti (parity_enable = 0 ali 1), ter kakšno
 parnost(parity= ...).

 Primer uporabe:
 UART_Init(UART_0, BAUD_115200, 8, TWO_STOP_BITS, PARITY_ENABLE, ODD_PARITY);

 */
void uart_init(unsigned char uart_number, unsigned int baud_rate, unsigned char number_of_bits, unsigned char stop_bits, unsigned char parity_enable, unsigned char parity)
{
	if ((stop_bits > 2) || (stop_bits < 1) || (parity_enable > 1) || (parity > 4) || (uart_number > 1) || (number_of_bits > 8) || (number_of_bits < 5))
			return; //security for non-valid settings

	unsigned int divisor = (CPU_FREQ * 1000) / (16 * baud_rate);

	if (uart_number == UART_0)
	{
		PINSEL0 &= ~(0x0F);
		PINSEL0 |= 0x05;
		/*
		IODIR
		*/
		U0LCR = (number_of_bits - 5) | ((stop_bits - 1) << 2) | (parity_enable << 3) | (parity << 4) | (1 << DLAB);
		U0DLL = (divisor & 0xFF); //lower 8 bits
		U0DLM = (divisor >> 8) & 0xFF; //upper 8 bits
		U0LCR = (number_of_bits - 5) | ((stop_bits - 1) << 2) | (parity_enable << 3) | (parity << 4); //cleares DLAB bit
	}
	else
	{
		/*
		 IODIR
		 */
		PINSEL0 &= ~(0x0F << 16);
		PINSEL0 |= (0x05 << 16);
		U1LCR = (number_of_bits - 5) | ((stop_bits - 1) << 2) | (parity_enable << 3) | (parity << 4) | (1 << DLAB);
		U1DLL = (divisor & 0xFF); //lower 8 bits
		U1DLM = (divisor >> 8) & 0xFF; //upper 8 bits
		U1LCR = (number_of_bits - 5) | ((stop_bits - 1) << 2) | (parity_enable << 3) | (parity << 4); //cleares DLAB bit
	}
}

/*
 Fja pošlje po željenem UART vmesniku(UART_0 ali UART_1) en znak.
 Primer uporabe:
 putchar(UART_0, 'S');
 */
unsigned char put_char(unsigned char uart_number, char c)
{
	if ((uart_number > 1))
		return 0;

	if (uart_number == UART_0)
	{
		//wait for Transmitter Holding Register to be Empty
		while (!(U0LSR & (1 << THRE)));
		U0THR = c;
	}
	else
	{
		//wait for Transmitter Holding Register to be Empty
		while (!(U1LSR & (1 << THRE)));
		U1THR = c;
	}

	return 1;
}

/*
 Fja prejme en znak po željenem UART vmesniku.
 Primer uporabe:

 unsigned char prejeti_znak = getchar(UART_0);
 */
char getchar(unsigned char uart_number)
{
	if (uart_number > 1)
		return -1;

	if (uart_number == UART_0)
	{
		//wait for Receiver Data Ready
		while (!(U0LSR & (1 << RDR)));
		return (U0RBR);
	}
	else
	{
		//wait for Receiver Data Ready
		while (!(U1LSR & (1 << RDR)));
		return (U1RBR);
	}
}
/*
 Fja pošlje znakovni niz po željenem UART vmesniku.
 Primer uporabe:

 putstring(UART_0, "Serbus!", 8);
 */
unsigned char putstring(unsigned char uart_number, char *string, unsigned int string_length)
{
	if ((uart_number > 1) || (string_length == 0))
		return 0;

	if (uart_number == UART_0)
	{
		while (string_length--)
			put_char(UART_0, *string++);
	}
	else
	{
		while (string_length--)
			put_char(UART_1, *string++);
	}

	return 1;
}

/*
 Fja je druga različica fje putstring(), le da predvideva ničelni znak na koncu niza in zato
 ni potrebno podati dolžine niza.

 Primer uporabe:

 puts(UART_0, "OpenSARM");
 */
unsigned char put_s(unsigned char uart_number, char *string)
{
	if (uart_number > 1)
		return 0;

	if (uart_number == UART_0)
	{
		while (*string)
			put_char(UART_0, *string++);

		put_char(UART_0, '\n');
	}
	else
	{
		while (*string)
			put_char(UART_1, *string++);

		put_char(UART_1, '\n');
	}

	return 1;
}

#endif
