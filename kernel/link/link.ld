ENTRY(loader)

SECTIONS
{

	 . = 0xC0100000;
	 
	.multiboot ALIGN(4K) : AT(ADDR(.multiboot) - 0xC0000000)
	{
		*(.multiboot)
	}

	.text : AT(ADDR(.text) - 0xC0000000)
	{
		*(.text)
		*(.rodata*)
	}

	.data ALIGN(0x1000) : AT(ADDR(.data) - 0xC0000000)
	{
		*(.data)
	}

	.bss : AT(ADDR(.data) - 0xC0000000)
	{
		 _sbss = . ;
		*(COMMON)
		*(.bss)
		_ebss = . ;
	}
}
