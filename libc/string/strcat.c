#include<string.h>

char	 *strcat(char *dest, const char *src)
{
	int startpos = strlen(dest);
	int sourcelen = strlen(src) + 1;
	for(int i = 0; i < sourcelen; i++)
	{
		dest[startpos + i] = src[i];
	}
	return dest;
}

