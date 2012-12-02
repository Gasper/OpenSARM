/**
 *  2008 John C. Wren
 *  Za OpenSARM prilagodila: Samo Penič in Jernej Sorta
 *
 */

#if !defined(ONLY_USED) || defined(LCD_H_INCLUDED)

#include "lpc214x.h"


//
//	This is where the various LCD control pins are assigned.	Currently they're
//	all assigned on port 1.	If you have to break them up, you'll need to edit
//	the functions them.	It's very convienent to have the D7..D0 lines grouped
//	together.	Otherwise you'll have to bit test each bit and assign the pin.
//	Much slower.
//
#define LCD_D4				(1<<16)
#define LCD_D5				(1<<17)
#define LCD_D6				(1<<18)
#define LCD_D7				(1<<19)
#define LCD_DATA			(LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4)
#define LCD_Dx_SHIFT	((unsigned int) 16)
#define LCD_RS				(1<<20)
#define LCD_RW				(1<<22)
#define LCD_E				 (1<<21)

//
//
//
#define LCD_COMMAND_CLEAR			 0x01
#define LCD_COMMAND_HOME				0x02
#define LCD_COMMAND_MODE				0x04
#define LCD_COMMAND_DISPLAY		 0x08
#define LCD_COMMAND_SHIFT			 0x10
#define LCD_COMMAND_FUNCTION		0x20
#define LCD_COMMAND_CGRAM			 0x40
#define LCD_COMMAND_DDRAM			 0x80

#define LCD_MODE_SHIFT_NO			 0x00
#define LCD_MODE_SHIFT_YES			0x01
#define LCD_MODE_DECREMENT			0x00
#define LCD_MODE_INCREMENT			0x02
#define LCD_MODE_MASK					 0x03

#define LCD_SHIFT_CURSOR				0x00
#define LCD_SHIFT_DISPLAY			 0x04
#define LCD_SHIFT_LEFT					0x00
#define LCD_SHIFT_RIGHT				 0x08
#define LCD_SHIFT_MASK					0x0c

#define LCD_FUNCTION_FONT_5X8	 0x00
#define LCD_FUNCTION_FONT_5X11	0x04
#define LCD_FUNCTION_LINES_1		0x00
#define LCD_FUNCTION_LINES_2		0x08
#define LCD_FUNCTION_BUS_4			0x00
#define LCD_FUNCTION_BUS_8			0x10
#define LCD_FUNCTION_MASK			 0x1c

#define LCD_DISPLAY_BLINK_OFF	 0x00
#define LCD_DISPLAY_BLINK_ON		0x01
#define LCD_DISPLAY_CURSOR_OFF	0x00
#define LCD_DISPLAY_CURSOR_ON	 0x02
#define LCD_DISPLAY_DISPLAY_OFF 0x00
#define LCD_DISPLAY_DISPLAY_ON	0x04
#define LCD_DISPLAY_MASK				0x07

#define LCD_PWM_FREQ 20000

#define delay166ns() do { asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
													asm volatile (" nop" : /* no output */ : /* no inputs */ ); \
												} while (0)

//
//	166ns measured
//
static inline void lcdDelay140ns(void)
{
	delay166ns();
}

//
//	333ns measured
//
static inline void lcdDelay320ns(void)
{
	delay166ns();
	delay166ns();
}

//
//	500ns measured
//
static inline void lcdDelay450ns(void)
{
	delay166ns();
	delay166ns();
	delay166ns();
}

//
//	666ns measured
//
static inline void lcdDelay550ns(void)
{
	delay166ns();
	delay166ns();
	delay166ns();
	delay166ns();
}

static inline void lcdDataToPort(unsigned char c)
{
	FIO0CLR = (~c & 0x0f) << LCD_Dx_SHIFT;
	FIO0SET = ( c & 0x0f) << LCD_Dx_SHIFT;
}

static inline unsigned int lcdDataFromPort(void)
{
	return (IOPIN0 & LCD_DATA) >> LCD_Dx_SHIFT;
}

static inline void lcdSelectCommandRegister(void)
{
	FIO0CLR = LCD_RS;
}

static inline void lcdSelectDataRegister(void)
{
	FIO0SET = LCD_RS;
}

static inline void lcdSelectWriteMode(void)
{
	FIO0CLR = LCD_RW;
}

static inline void lcdSelectReadMode(void)
{
	FIO0SET = LCD_RW;
}

static inline void lcdEnableHigh(void)
{
	FIO0SET = LCD_E;
}

static inline void lcdEnableLow(void)
{
	FIO0CLR = LCD_E;
}

static inline void lcdDataAsInputs(void)
{
	FIO0DIR &= ~LCD_DATA;
}

static inline void lcdDataAsOutputs(void)
{
	FIO0DIR |= LCD_DATA;
}

static void lcdWritePort4(unsigned char c)
{
	lcdEnableHigh();
	lcdDataToPort(c & 0x0f);
	lcdDelay140ns();
	lcdEnableLow();
	lcdDelay550ns();
	lcdDelay550ns();
}

static void lcdWriteData(unsigned char c)
{
	lcdSelectDataRegister();
	lcdSelectWriteMode();

	lcdWritePort4(c >> 4);
	lcdWritePort4(c & 0x0f);
}

static void lcdWriteCommand4(unsigned char c)
{
	lcdSelectCommandRegister();
	lcdSelectWriteMode();

	lcdWritePort4(c);
}

static void lcdWriteCommand(unsigned char c)
{
	lcdSelectCommandRegister();
	lcdSelectWriteMode();

	lcdWritePort4(c >> 4);
	lcdWritePort4(c & 0x0f);
}

static int lcdReadStatus4(void)
{
	unsigned char c;

	lcdEnableHigh();
	lcdDataAsInputs();
	lcdDelay140ns();
	c = lcdDataFromPort();
	lcdEnableLow();
	lcdDelay550ns();
	lcdDelay550ns();

	return c & 0x0f;
}

static int lcdReadStatus(void)
{
	unsigned char c;

	lcdSelectCommandRegister();
	lcdSelectReadMode();

	c = lcdReadStatus4() << 4;
	c |= lcdReadStatus4();

	lcdSelectWriteMode();
	lcdDataAsOutputs();

	return c;
}

static void lcdWaitWhileBusy(void)
{
	while (lcdReadStatus() & 0x80);
}

static void lcdDisplay(unsigned char display)
{
	lcdWaitWhileBusy();
	lcdWriteCommand(LCD_COMMAND_DISPLAY | (display & LCD_DISPLAY_MASK));
}

static void lcdMode(unsigned char mode)
{
	lcdWaitWhileBusy();
	lcdWriteCommand(LCD_COMMAND_MODE | (mode & LCD_MODE_MASK));
}

void lcdClear(void)
{
	lcdWaitWhileBusy();
	lcdWriteCommand(LCD_COMMAND_CLEAR);
}

static void lcdHome(void)
{
	lcdWaitWhileBusy();
	lcdWriteCommand(LCD_COMMAND_HOME);
}

//TODO: Popravi. velja le za dvovrsticne zaslone.
void lcdGotoXY(unsigned int x, unsigned int y)
{
	lcdWaitWhileBusy();
	lcdWriteCommand(LCD_COMMAND_DDRAM | (y ? 0x40 : 0x00) | (x & 0x0f));
	lcdWaitWhileBusy();
}
void lcdPutChar(unsigned char c)
{
	lcdWaitWhileBusy();
	lcdWriteData(c);
}

void lcdPutString(char *s){
	short i=0;
	while (s[i])
	{
		lcdPutChar(s[i]);
		i++;

	}
}

static void lcdDelayMs(unsigned int timeInMs)
{
	unsigned int i;
	for (i=1; i < timeInMs; i++){
		lcdDelay450ns();
		lcdDelay550ns();
	}
}

static void lcdControllerInit(void)
{
	lcdWriteCommand4((LCD_COMMAND_FUNCTION | LCD_FUNCTION_BUS_4) >> 4);
	lcdDelayMs(30);
	lcdWriteCommand4((LCD_COMMAND_FUNCTION | LCD_FUNCTION_BUS_4) >> 4);
	lcdDelayMs(30);
	lcdWriteCommand4((LCD_COMMAND_FUNCTION | LCD_FUNCTION_BUS_4) >> 4);
	lcdDelayMs(30);

	lcdWriteCommand(LCD_COMMAND_FUNCTION | LCD_FUNCTION_BUS_4 | LCD_FUNCTION_LINES_2 | LCD_FUNCTION_FONT_5X8);
	lcdDelayMs(30);
	lcdWriteCommand(LCD_COMMAND_FUNCTION | LCD_FUNCTION_BUS_4 | LCD_FUNCTION_LINES_2 | LCD_FUNCTION_FONT_5X8);
	lcdDelayMs(30);

	lcdDisplay(LCD_DISPLAY_DISPLAY_ON | LCD_DISPLAY_CURSOR_OFF | LCD_DISPLAY_BLINK_OFF);
	lcdClear();
	lcdMode(LCD_MODE_INCREMENT | LCD_MODE_SHIFT_NO);
	lcdGotoXY(0, 0);
}

void lcdInit(void)
{
	FIO0DIR |= (LCD_E | LCD_RS | LCD_RW);

	lcdEnableLow();
	lcdSelectWriteMode();
	lcdSelectCommandRegister();
	lcdDataAsOutputs();
	lcdDataToPort(0xff);
	lcdControllerInit();
}

#endif
