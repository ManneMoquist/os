#include<string.h>

void	 *memchr(const void* ptr, int c, size_t n)
{
	unsigned char* pointer = (unsigned char*)ptr;
	unsigned char byte = (unsigned int)c;
	while(n--)
	{
		if(*pointer == byte)
		{
			return pointer;
		}
		pointer++;
	}
	return NULL;
}

