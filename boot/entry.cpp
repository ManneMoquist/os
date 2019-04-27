#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
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
	terminal_color = 0 | 15 << 4;
	terminal_buffer = (uint16_t*) 0xB8000;
	for(size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry('a', terminal_color);
		}
	}
}

void terminal_putchar(char c)
{
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
		terminal_writestring("HELLO MOS");
	}
}
