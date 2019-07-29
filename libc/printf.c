#include<limits.h>
#include<stdbool.h>
#include<stdarg.h>
#include<stdio.h>
#include<string.h>

static int print(const char * str, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if(putchar(str[i]) == -1)
		{
			return -1;
		}
		return 1;
	}
}

int printf(const char * restrict format, ...)
{
	int written = 0;
	va_list args;
	va_start(args, format);
	while(*format != '\0')
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
				case 'd':
				case 'i':
					// HANDLE INTEGER
					break;
				case 'u':
					// HANDLE UNSIGNED INTIGER
					break;
				case 'o':
				case 'x':
				case 'X':
				case 'f':
				case 'F':
				case 'e':
				case 'E':
				case 'g':
				case 'G':
				case 'a':
				case 'A':
				case 'c':
					{
					char c = (char)va_arg(args, int);
					putchar(c);
					} break;
				case 's':
				{
					const char* string = va_arg(args, const char*);
					size_t length = strlen(string);
					if(print(string, length) != 1)
					{
						return -1;
					}
				} break;
				case 'p':
					//HANDLE POINTER ADDRESS
					break;
				case 'n':
					//PRINT NOTHING
					break;
				case '%':
					//PRINT % SIGN
					break;
				default:
					//IS THIS THE RIGHT ACTION?
					return -1;
					break;
			}
			format++;
		}
	}
	va_end(args);
	written = 1;
	return written;
}
