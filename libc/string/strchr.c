#include<string.h>

char	 *strchr(const char *str, int c)
{
	return (char*)memchr(str,c,strlen(str));
}

