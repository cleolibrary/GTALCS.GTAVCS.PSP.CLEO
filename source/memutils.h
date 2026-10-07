#pragma once

#include "common.h"

namespace memutils
{
	void mem_write_arr(uint8_t *addr, uint8_t *arr, uint32_t size, bool protect = true);
	// true when [addr, addr + size) lies in cached PSP RAM
	bool mem_is_readable(const void *addr, uint32_t size);


	// read addr from mips jmp/call
	ptr mem_read_mips_jmp(uint8_t *addr);
	// addrFrom must divide by 4 without remainder
	void mem_write_mips_jmp(uint8_t *addrFrom, uint8_t *addrTo, bool withNop);
	// addrFrom must divide by 4 without remainder
	void mem_write_mips_call(uint8_t *addrFrom, uint8_t *addrTo, bool withNop);

}