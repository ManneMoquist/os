#include"terminal.h"

VGATerminal term;

VGATerminal* GetTerminal()
{
	return &term;
}

int TerminalPutchar(int character)
{
	term.putchar(character);
	return 1;
}
