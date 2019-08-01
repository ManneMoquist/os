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
	}
	return 1;
}

int printf(const char * format, ...)
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
					{
						int tenths = 1;
						int numdigits = 0;
						int value = (int) va_arg(args, int);
						if(value == 0)
						{
							putchar('0');
						}
						else
						{
							if(value < 0)
							{
								putchar('-');
								value *= -1;
							}
							while(value >= tenths)
							{
								tenths *= 10;
								numdigits++;
							}
							char string[256];
							for(int i = 0; i < numdigits; i++)
							{
								tenths /= 10;
								string[i] = '0' + (value / tenths);
								value %= tenths;
							}
							string[numdigits] = '\0';
							size_t length = strlen(string);
							print(string, length);
						}
					}
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
					putchar((int)c);
					written++;
				} break;
				case 's':
				{
					const char* string = va_arg(args, const char*);
					size_t length = strlen(string);
					written += strlen(string);
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
		}
		else
		{
			putchar(*format);
			written++;
		}
		format++;
	}
	va_end(args);
	written = 1;
	return written;
}
