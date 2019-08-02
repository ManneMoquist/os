#include<string.h>

char	 *strncpy(char *dest, const char *src, size_t n)
{
	char* destination = dest;
	const char* source = (const char*)src;
	while(n--)
	{
		*destination++ = *source++;
	}
	return dest;
}
