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
		printf("This is a number printed in the kernel_main funciton in entry.cpp: %d", 64);
	}
}
