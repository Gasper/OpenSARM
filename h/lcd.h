#ifndef _LCD_H_
#define _LCD_H_

void lcdGotoXY (unsigned int x, unsigned int y);
void lcdInit (void);
void lcdPutString (char *s);
void lcdClear (void);

#endif
