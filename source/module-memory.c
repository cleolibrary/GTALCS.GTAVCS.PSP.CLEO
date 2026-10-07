/* Newlib still owns its malloc/free implementation and locks. Only its backing
 * storage changes: it can never grow outside this PRX's reservation. */
#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <pspthreadman.h>

#define CLEO_HEAP_BYTES (256u * 1024u)
static unsigned char heap[CLEO_HEAP_BYTES] __attribute__((aligned(16)));
static size_t committed;
extern SceLwMutexWorkarea __sbrk_mutex;

void* _sbrk(ptrdiff_t increment)
{
    void* result = (void*)-1;
    sceKernelLockLwMutex(&__sbrk_mutex, 1, 0);
    size_t next = committed;
    if (increment >= 0) {
        if ((size_t)increment <= sizeof(heap) - committed)
            next += (size_t)increment;
        else { errno = ENOMEM; goto done; }
    } else {
        /* Avoid negating PTRDIFF_MIN. */
        size_t decrease = (size_t)(-(increment + 1)) + 1;
        if (decrease <= committed) next -= decrease;
        else { errno = ENOMEM; goto done; }
    }
    result = heap + committed;
    committed = next;
done:
    sceKernelUnlockLwMutex(&__sbrk_mutex, 1);
    return result;
}
