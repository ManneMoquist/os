#include<stdio.h>
#include<../../kernel/terminal.h>

int putchar(int character)
{
	TerminalPutchar(character);
	return 0;
}
