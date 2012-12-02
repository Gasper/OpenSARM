#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

void lcdGotoXY (unsigned int x, unsigned int y);
void lcdInit (void);
void lcdPutString (char *s);
void lcdClear (void);

#ifdef ONLY_USED
#include "lcd.c"
#endif

#endif
