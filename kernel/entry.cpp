#include "vga.h"

VGATerminal term;

void helloworld()
{
	term.writestring("HELLO WORLD\n");
}

extern "C"
{
	int __cxa_atexit()
	{
		return 0;
	}
	void kernel_main(void)
	{
		helloworld();
	}
}
