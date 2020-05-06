#include<string.h>

void	 *memcpy(void *dest, const void *src, size_t n)
{
	unsigned char* destination = (unsigned char*)dest;
	const unsigned char* source = (const unsigned char*)src;
	while(n--)
	{
		*destination++ = *source++;
	}
	return dest;
}

