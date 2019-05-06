#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
size_t terminal_offset;
uint8_t terminal_color;
uint16_t* terminal_buffer;

#define vga_entry(c, color) (uint16_t)((uint16_t) c | (uint16_t) (color << 8))

size_t strlen(const char* str)
{
	size_t len = 0;
	while(str[len])
		len++;
	return len;
}

void terminal_init()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_offset = 0;
	terminal_color = 0 | 10;
	terminal_buffer = (uint16_t*) 0xB8000;
	for(size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
void terminal_scroll()
{
	for(unsigned int row = 1; row < VGA_HEIGHT; row++)
	{
		for(unsigned int col = 0; col < VGA_WIDTH; col++)
		{
			const size_t oldIndex = row * VGA_WIDTH + col;
			const size_t newIndex = (row - 1) * VGA_WIDTH + col;
			terminal_buffer[newIndex] = terminal_buffer[oldIndex];
		}
	}
}

void terminal_putchar(char c)
{
	if(c == '\n')
	{
		if(terminal_row == 24)
		{
			terminal_scroll();
			terminal_column = 0;
			return;
		}
		terminal_row++;
		terminal_column = 0;
		return;
	}
	const size_t index = terminal_row * VGA_WIDTH + terminal_column;
	terminal_buffer[index] = vga_entry(c,terminal_color);
	++terminal_column;
}

void terminal_write(const char* data, size_t size)
{
	for(size_t i = 0; i < size; i++)
	{
			terminal_putchar(data[i]);
	}
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

extern "C"
{
	void kernel_main(void)
	{
		terminal_init();
		const char newline = '\n';
		for(int i = 0; i < 30; i++)
		{
			const char c = (char)('A' + i);
			terminal_write(&c, 1);
			terminal_write(&newline, 1);
		}
	}
}
