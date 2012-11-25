
#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "lpc214x.h"

#ifdef CPU_12MHZ
#define CPU_FREQ 12000
#define PLL_CONF 0x60 //P=8, M=1
#endif

#ifdef CPU_24MHZ
#define CPU_FREQ 24000
#define PLL_CONF 0x41 //P=4, M=2
#endif

#ifdef CPU_36MHZ
#define CPU_FREQ 36000
#define PLL_CONF 0x42 //P=4, M=3
#endif

#ifdef CPU_48MHZ
#define CPU_FREQ 48000
#define PLL_CONF 0x23 //P=2, M=4
#endif

#ifdef CPU_60MHZ
#define CPU_FREQ 60000
#define PLL_CONF 0x24 //P=2, M=5
#endif


/******************************************************************************
 *  Hardware connections on OpenSARM board v.1.0                              *
 *                                                                            *
 ******************************************************************************/

#define LEDMASK       0x0000f0000
#define LEDPINSELMASK 0x8
#define LEDMASKSHIFT  16

#define KEYSELMASK 0xff000000
#define KEYMASK 0xf000

#define ADCSELMASK 0x3000000
#define ADCSELVAL  0x1000000

#define DACSELMASK 0xc0000
#define DACSELVAL  0x80000

#define IN 0
#define OUT 1

void Initialize(void);
inline void _TimerInit(void);
unsigned long clock(void);
void delay(unsigned long ms);
inline void _LEDInit(void);
inline void _setleds(int mask);
inline void _clrleds(int mask);
void _setpindir(unsigned int pinid, int dir);
void outportp(unsigned int pinid, int value);
int inportp(unsigned int pinid);
void _KeyInit(void);
int _getkeys(void);
int kbhit(void);
int getch(void);
void _ADCInit(void);
int _adconvert(void);
int _adconvertExt(int input);
void _DACInit(void);
void _dacwrite(int val);
void set_pin_direction(unsigned int pinid, unsigned int dir);
int read_pin(unsigned int pinid);
void set_pin(unsigned int pinid, unsigned int value);

#endif // IO_H_INCLUDED
