#pragma once

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
#define vga_entry(c, color) (uint16_t)((uint16_t) c | (uint16_t) (color << 8)) 

class VGATerminal
{
public:
	VGATerminal();
	~VGATerminal();
private:
	size_t row, column, offset;
	uint8_t color;
  	uint16_t* buffer;
	void init();
	void putchar(char c);
	void write(const char* data, size_t size);
	void scroll();

public:
	void writestring(const char* string);
	void setcolor(uint8_t foreground, uint8_t background = 0x00);
private:
	uint16_t* getScreenBuffer();
		
};


