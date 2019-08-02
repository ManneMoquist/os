#include<string.h>

int	 strcmp(const char *str1, const char *str2)
{
	return memcmp(str1,str2,strlen(str1));
}
