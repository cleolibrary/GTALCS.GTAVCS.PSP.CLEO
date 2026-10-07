#include "mutex.h"

namespace mutex
{
	SceUID mutex[msize];

	void init()
	{
		memset(mutex, 0, sizeof(mutex));
		for (int i = 0; i < msize; i++)
		{
			char name[32];
			sprintf(name, "CleoMutex_%d", i);
			mutex[i] = sceKernelCreateSema(name, 0, 1, 1, NULL);
		}
	}

	void enter(eMutex m)
	{
		sceKernelWaitSema(mutex[m], 1, 0);
	}

	void leave(eMutex m)
	{
		sceKernelSignalSema(mutex[m], 1);
	}
}