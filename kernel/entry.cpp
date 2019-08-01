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
		char* test = (char*)"ABCDEFGHIJKLMNOPQRSTUVXYZ";
		char* another = (char*)"MANNE";
		memcpy(test,another,7);
		printf("%s\n",test);
		memset(test, '$', 3);
		printf("%s\n",test);
	}
}
