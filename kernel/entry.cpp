#include<stdio.h>
#include<string.h>

extern "C"
{
	int __cxa_atexit()
	{
		return 0;
	}
	void kernel_main(void)
	{
		char str1[20];
		char str2[20];
		strcpy(str1, "To be ");
		strcpy(str2, "or not to be");
		strncat(str1, str2, 6);
		printf(str1);
	}
}
