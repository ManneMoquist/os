#include<string.h>

void *memmove(void *dest, const void *src, size_t n)
{
	unsigned char temp[n];
	memcpy(temp, src, n);
	memcpy(dest, temp, n);
	return dest;
}
