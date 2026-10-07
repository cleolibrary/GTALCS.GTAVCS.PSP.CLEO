#include "memutils.h"
#include "guest-hooks.h"

namespace memutils
{
    bool mem_is_readable(const void* addr, uint32_t size)
    {
        return psp_guest_ram_range((uintptr_t)addr, size) != 0;
    }

    void mem_write_arr(uint8_t* addr, uint8_t* arr, uint32_t size, bool protect)
    {
        if (!size) return;
        (void)protect;
        // Remove PPSSPP markers while their original words are still recoverable.
        auto interrupts = sceKernelCpuSuspendIntr();
        sceKernelIcacheInvalidateRange(addr, size);
        memmove(addr, arr, size);
        sceKernelDcacheWritebackRange(addr, size);
        sceKernelIcacheInvalidateRange(addr, size);
        sceKernelCpuResumeIntr(interrupts);
    }


	ptr mem_read_mips_jmp(uint8_t *addr)
	{
		uint32_t word;
		guest_hooks::initialize();
		guest_hooks::require(guest_hooks::backend.read(guest_hooks::backend.user, (uint32_t)(uintptr_t)addr, &word, 4) != 0, "read jump");
		return cast<ptr>(((word & 0x03FFFFFF) << 2) | (((uint32_t)(uintptr_t)addr + 4) & 0xF0000000));
	}

	void mem_write_mips_jmp(uint8_t *addrFrom, uint8_t *addrTo, bool withNop)
	{
		uint64_t code = 0x08000000 | ((cast<uint32_t>(addrTo) >> 2) & 0x03FFFFFF);
		guest_hooks::require(!((uintptr_t)addrFrom & 3) && !((uintptr_t)addrTo & 3) &&
		    ((((uintptr_t)addrFrom + 4) ^ (uintptr_t)addrTo) & 0xF0000000) == 0, "jump region");
		guest_hooks::write_code(addrFrom, (const uint32_t*)&code, withNop ? 8 : 4);
	}

	void mem_write_mips_call(uint8_t *addrFrom, uint8_t *addrTo, bool withNop)
	{
		uint64_t code = 0x0C000000 | ((cast<uint32_t>(addrTo) >> 2) & 0x03FFFFFF);
		guest_hooks::require(!((uintptr_t)addrFrom & 3) && !((uintptr_t)addrTo & 3) &&
		    ((((uintptr_t)addrFrom + 4) ^ (uintptr_t)addrTo) & 0xF0000000) == 0, "jump region");
		guest_hooks::write_code(addrFrom, (const uint32_t*)&code, withNop ? 8 : 4);
	}


}