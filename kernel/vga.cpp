#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>
#include"vga.h"

size_t strlen(const char* str)
{
	size_t len = 0;
	while(str[len])
		len++;
	return len;
}//should be moved to C-library as soon as possible

VGATerminal::VGATerminal()
{
	row = 0;
	column = 0;
	offset = 0;
	uint8_t foregroundColor = VGA_WHITE;
	uint8_t backgroundColor = VGA_BLACK;
	color = foregroundColor | (backgroundColor << 4);
	buffer = (uint16_t*) 0xB8000;

	for(size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			buffer[index] = vga_entry(' ', color);
		}
	}

	writestring("VGA TERMINAL INITIATED \n");
}

VGATerminal::~VGATerminal()
{
	setcolor(VGA_WHITE, VGA_BLACK);
	writestring("VGA TERMINAL TERMINATED \n");
}

void VGATerminal::putchar(char c)
{
	if(c == '\n')
	{
		if(row == 24)
		{
			scroll();
			column = 0;
			return;
		}
		row++;
		column = 0;
		return;
	}
	const size_t index = row * VGA_WIDTH + column;
	buffer[index] = vga_entry(c,color);
	++column;
	
}

void VGATerminal::write(const char* data, size_t size)
{
	for(size_t i = 0; i < size; i++)
	{
			putchar(data[i]);
	}
}

void VGATerminal::scroll()
{
	for(unsigned int row = 1; row < VGA_HEIGHT; row++)
	{
		for(unsigned int col = 0; col < VGA_WIDTH; col++)
		{
			const size_t oldIndex = row * VGA_WIDTH + col;
			const size_t newIndex = (row - 1) * VGA_WIDTH + col;
			buffer[newIndex] = buffer[oldIndex];
		}
	}
}

void VGATerminal::writestring(const char* string)
{
	write(string, strlen(string));
}

void VGATerminal::setcolor(uint8_t foreground, uint8_t background)
{
	color = foreground | (background << 4);
}
