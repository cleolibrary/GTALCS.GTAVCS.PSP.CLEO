#include "pattern.h"
#include "libres.h"
extern "C" {
#include "../external/injector/include/psp/patterns.h"
}
bool __FindPatternAddressCompact(void*& result, const char* signature, int index)
{
    if (index < 0) return false;
    const auto base = (uintptr_t)libres::getLoadAddress();
    for (const auto& section : libres::getExecutableSections()) {
        uintptr_t cursor = base + section.addr;
        size_t remaining = section.size;
        while (remaining) {
            uintptr_t address = range_pattern.get_first(cursor, remaining, signature, 0);
            if (!address) break;
            if (!index--) { result = (void*)address; return true; }
            size_t consumed = address - cursor + 1;
            cursor += consumed; remaining -= consumed;
        }
    }
    return false;
}
