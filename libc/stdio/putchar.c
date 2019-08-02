#include<stdio.h>
#ifdef __is_libk
#include<../../kernel/terminal.h>

int putchar(int character)
{
	TerminalPutchar(character);
	return 0;
}
#else

int putchar(int character)
{
	return 0;
}
#endif

