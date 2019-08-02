#include<string.h>

char 	*strpbrk(const char *str1, const char *str2)
{
	for(size_t i = 0; i < strlen(str1); i++)
	{
		for(size_t j = 0; j < strlen(str2); j++)
		{
			if(str1[i] == str2[j])
			{
				return ((char*)str1 + i);
			}
		}
	}
	return NULL;
}

