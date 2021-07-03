#ifndef _LIBC_STDIO_H
#define _LIBC_STDIO_H

#if defined (__cplusplus)
extern "C" {
#endif

/* defines */
#define EOF (-1)
#define NULL 0L

/* Formatted input output */
int printf(const char * format, ...);

/* Character input output */
int putchar(int character);
int puts(const char * str);

#if defined (__cplusplus)
}
#endif

#endif
