#include "core.h"
#include "utils.h"

	
#ifndef __INTELLISENSE__
PSP_MODULE_INFO("CLEO", 0x1000, 1, 1);
PSP_HEAP_SIZE_KB(0); // module-memory.c supplies the private 256 KiB heap.
#endif

#define STR(x) STR2(x)
#define STR2(x) #x

extern "C" const char VERSION[] = "[|VERSION]" VERSION_DATE ";" STR(VERSION_CODE) ";" VERSION_CODE_STR "[/VERSION|]";

int main(int argc, char **argv)
{
	core::initialize();
	sceKernelSleepThread();
	return 0;
}
