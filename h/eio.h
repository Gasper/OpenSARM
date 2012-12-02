#ifndef EIO_H_INCLUDED
#define EIO_H_INCLUDED

int printf(const char *format, ...);
int bprintf(const char *format, ...);
int sprintf(char *out, const char *format, ...);

#ifdef ONLY_USED
#include "eio.c"
#endif

#endif
