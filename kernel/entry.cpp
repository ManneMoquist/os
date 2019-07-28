#include "vga.h"

void terminal_init()
{
	VGATerminal terminal;
	terminal.setcolor(0x01, 0x0f);
	terminal.writestring("HELLO WORLD \n");
}

extern "C"
{
	void kernel_main(void)
	{
		terminal_init();
	}
}
