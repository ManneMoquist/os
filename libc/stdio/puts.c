#include<stdio.h>

int puts(const char *str)
{
	if(printf("%s\n",str))
		return 1;
	else
		return -1;
}

