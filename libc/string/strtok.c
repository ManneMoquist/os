#include<string.h>

char 	*strtok(char *str, const char *delim)
{
	static char *last;
	if(str == NULL)
	{
		if(*last == '\0')
		{
			return NULL;
		}
		str = last;
	}
	char* string = str;
	string += strspn(string, delim);
	char* token = strpbrk(string,delim);
	*token = '\0';
	last = token+1;
	return string;
}
