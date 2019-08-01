#include<string.h>

int	 memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char* cmp1 = (const unsigned char*)str1;
	const unsigned char* cmp2 = (const unsigned char*)str2;
	for(size_t i = 0; i < n; i++)
	{
		if(cmp1[i] < cmp2[i])
		{
			return -1;
		}
		else if(cmp2[i] < cmp1[i])
		{
			return 1;
		}
	}

	return 0;
}
