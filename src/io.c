/**
 *
 * 2012 OpenSARM
 * Avtor: Arpad Buerman
 * Za OpenSARM prilagodil: Samo Penič
 *
 */

#ifdef IO_H_INCLUDED

#include "lpc214x.h"

inline void _TimerInit(void)
{
	// Set timer information. For more information take a look in Chapter 15 of LPC214x User's manual
	// Prescaler to get 1ms clock ticks.
	T0PR = CPU_FREQ - 1;
	T0MR0 = 0xFFFFFFFF;
	// we want a free running counter
	T0MCR = 0x0000;
	// Reset counter&prescaler and disable timer
	T0TCR = 0x02;
	// Timer mode
	T0CTCR = 0x00;
	// Enable timer
	T0TCR = 0x01;
}

unsigned long clock(void)
//return number of milliseconds since _TimerInit() call.
{
	return T0TC;
}

void delay(unsigned long m)
//pause for m milliseconds
//there is a bug in original code, that may cause delay malfunction if the CPU is running more than 49 days (T0TC reaches T0MR0). If delay is called just
//before this happens (unsigned) T0TC-start will always be more than m for almost any m.
{
	unsigned long start = T0TC;
	unsigned long end = start + m;
	// check whether addition overflows.
	if (end > start) {
		while (T0TC < end);
	}
	else
	{
		if (T0TC > start)
			while (T0TC > end);
		else
			while (T0TC < end);
	}
}

inline void _LEDInit(void)
{
	//define function of pins to GPIO just in case if the function is broken!
	PINSEL2 &= ~LEDPINSELMASK;
	FIO1DIR |= LEDMASK;
}

inline void _setleds(int mask)
{
	FIO1SET = (((mask) & 0xf) << LEDMASKSHIFT); \
}

inline void _clrleds(int mask)
{
	FIO1CLR = (((mask) & 0xf) << LEDMASKSHIFT); \
}


void _setpindir(unsigned int pinid, int dir)
{
	set_pin_direction(pinid, dir);
}

void outportp(unsigned int pinid, int value)
{
	set_pin(pinid, value);
}

int inportp(unsigned int pinid)
{
	return read_pin(pinid);
}

void set_pin(unsigned int pinid, unsigned int value)
{
	volatile unsigned long *fioclr;
	volatile unsigned long *fioset;

	if (pinid > 31 || pinid == 24 || pinid == 26 || pinid == 27)
		return;

	fioclr = &FIO0CLR;
	fioset = &FIO0SET;

	if (value == 0)
		*fioclr = 1 << pinid;
	else
		*fioset = 1 << pinid;
}

int read_pin(unsigned int pinid)
{
	volatile unsigned long *fio;

	if (pinid > 31 || pinid == 24 || pinid == 26 || pinid == 27)
		return -1;

	fio = &FIO0PIN;

	return (*fio & (1 << pinid)) >> pinid;
}

void set_pin_direction(unsigned int pinid, unsigned int dir)
{
	unsigned int dirmask;
	unsigned int selectpinmask;
	volatile unsigned long *pinsel;
	volatile unsigned long *fiodir;

	//Pins P0.24, P0.26 and P0.27 are not available.
	if (pinid > 31 || pinid == 24 || pinid == 26 || pinid == 27)
		return;

	dirmask = 1 << pinid;

	if (pinid < 16)
	{
		pinsel = &PINSEL0;
	}
	else
	{
		pinsel = &PINSEL1;
		pinid -= 16;
	}

	fiodir = &FIO0DIR;
	selectpinmask = ~(0x3 << (pinid << 2));
	*pinsel &= selectpinmask;

	if (dir == 0)
		*fiodir &= ~dirmask;
	else
		*fiodir |= dirmask;
}

char _kbdbuffer;

void _KeyInit(void)
{
	PINSEL0 &= ~KEYSELMASK;
	FIO0DIR &= ~KEYMASK;
	_kbdbuffer = 0;
}

/* Get state of all four keys, non-blocking call */
int _getkeys(void)
{
	int i, state, revstate = 0;
	state = (~(FIO0PIN) & KEYMASK);
	state >>= 12;

	for (i = 0; i < 4; i++)
	{
		revstate |= state & 1;
		state >>= 1;
		revstate <<= 1;
	}

	return revstate >> 1;
}

/* detects keypresss (0->1). if no keypress returns 0, nonzero value otherwise. the code of pressed key is stored in _kbdbuffer*/
int kbhit(void)
{
	int i;
	static int keys = 0;

	int keys1 = _getkeys();
	for (i = 8; i > 0; i >>= 1)
	{
		if ((keys1 & i) > (keys & i))
			break;
	}

	keys = keys1;

	switch (i)
	{
		case 8:
			_kbdbuffer = '0';
			break;
		case 4:
			_kbdbuffer = '1';
			break;
		case 2:
			_kbdbuffer = '2';
			break;
		case 1:
			_kbdbuffer = '3';
			break;
	}

	return _kbdbuffer;
}

int getch(void)
{
	char ret;
	while (!kbhit());
	ret = _kbdbuffer;
	_kbdbuffer = 0;
	return ret;
}

void _ADCInit(void)
{
	//TODO: REWRITE AT LEAST LAST COMMAND
	PINSEL1 = (PINSEL1 & ~ADCSELMASK) | ADCSELVAL;
	ADCR = 0x2 | (0x4 << 8) | (0x1 << 21);
}

int _adconvert(void)
{
	ADCR = 0x2 | (0xD << 8) | (0x1 << 21) | (0x1 << 24);
	while ((ADDR & (0x1 << 31)) == 0);
	return (ADDR & 0xFFC0) >> 6;
}

//input: 0 selects AD0.0, 7 selects AD0.7
//Needs no initialization
//Notice: _adconvertExt(0); is equivalent to _ADCInit(); _adconvert();
int _adconvertExt(int input)
{
	if (!input)
		input = 1;

	int val = 0x400000 << (input * 2);
	int mask = 0xc00000 << (input * 2);
	int selectpin = 0x1 << input;
	int retval;

	if (input < 0 || input > 7)
		return 0;

	PINSEL1 = (PINSEL1 & ~mask) | val;

	ADCR = selectpin | (0x4 << 8) | (0x1 << 21) | (0x1 << 24);
	do {
		retval = ADDR;
	} while ((retval & (0x1 << 31)) == 0);
	retval = ((ADDR & 0xffc0) >> 6);

	return retval;
}

void _DACInit(void)
{
	PINSEL1 = (PINSEL1 & ~DACSELMASK) | DACSELVAL;
}

void _dacwrite(int val)
{
  if (val < 0) val = 0;
  if (val > 1023) val = 1023;
  DACR = (((val) & 0x3ff) << 6);
}

#endif
