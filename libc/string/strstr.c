#include<string.h>

char	*strstr(const char *haystack, const char *needle)
{
	char *hayptr = (char*)haystack;
	char *needleptr = (char*)needle;
	while(*hayptr)
	{
		int i = 0;
		while(*(hayptr + i) == *needleptr)
		{
			needleptr++;
			if(*needleptr == '\0')
			{
				return hayptr;
			}
			i++;
		}
		hayptr++;
		needleptr = (char*)needle;
	}
	return (char*)NULL;
}
