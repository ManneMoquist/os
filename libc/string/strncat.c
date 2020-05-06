#include<string.h>

char	 *strncat(char *dest, const char *src, size_t n)
{
	size_t startpos = strlen(dest);
	for(size_t i = 0; i < n; i++)
	{
		dest[startpos + i] = src[i];
	}
	return dest;
}
