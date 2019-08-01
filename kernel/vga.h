#ifndef VGA_TERMINAL_H
#define VGA_TERMINAL_H 1
#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
#define vga_entry(c, color) (uint16_t)((uint16_t) c | (uint16_t) (color << 8)) 

class VGATerminal
{
public:
	VGATerminal();
	~VGATerminal();
	enum VGA_COLORS
	{
		VGA_BLACK,
		VGA_BLUE,
		VGA_GREEN,
		VGA_CYAN,
		VGA_RED,
		VGA_MAGENTA,
		VGA_BROWN,
		VGA_LIGHT_GRAY,
		VGA_DARK_GRAY,
		VGA_LIGHT_BLUE,
		VGA_LIGHT_GREEN,
		VGA_LIGHT_CYAN,
		VGA_LIGHT_RED,
		VGA_LIGHT_MAGENTA,
		VGA_YELLOW,
		VGA_WHITE
	};
private:
	size_t row, column, offset;
	uint8_t color;
  	uint16_t* buffer;
	void init();
	void write(const char* data, size_t size);
	void scroll();

public:
	void putchar(char c);
	void writestring(const char* string);
	void setcolor(uint8_t foreground, uint8_t background = 0x00);
private:
	uint16_t* getScreenBuffer();
};

#endif
