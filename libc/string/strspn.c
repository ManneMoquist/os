#include<string.h>

size_t strspn(const char *str1, const char *str2)
{
	size_t c = 0;
	while(str1[c])
	{
		bool contained = false;
		for(size_t i = 0; i < strlen(str2); i++)
		{
			if(str1[c] == str2[i])
			{
				contained = true;
				break;
			}
		}
		if(!contained)
		{
			return c;
		}
		c++;
	}
	return strlen(str1);
}
