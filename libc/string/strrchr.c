#include<string.h>

char *strrchr(const char *str, int c)
{
	size_t n = strlen(str);
	char character = (char)c;
	while(n--)
	{
		if(str[n] == character)
		{
			return (char*)str + (char)n;
		}
	}
	return NULL;
}
