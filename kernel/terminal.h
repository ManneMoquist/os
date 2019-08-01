#pragma once
#include"vga.h"

VGATerminal* GetTerminal();

extern "C"
{
	int TerminalPutchar(int character);
}
