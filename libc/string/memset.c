#include<string.h>

void *memset(void *ptr, int c, size_t n)
{
	unsigned char* data = (unsigned char*)ptr;
	for(size_t i = 0; i < n; i++)
	{
		data[i] = (unsigned char)c;
	}
	return ptr;
}
