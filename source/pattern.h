#pragma once
#include "common.h"
bool __FindPatternAddressCompact(void*& result, const char* signature, int index = 0);
template<class T> inline bool __FindPatternAddress(T& result, const char* signature, int index = 0)
{
    static_assert(sizeof(T) == sizeof(uint32_t), "Guest addresses are 32-bit");
    void* address = nullptr;
    if (!__FindPatternAddressCompact(address, signature, index)) return false;
    memcpy(&result, &address, sizeof(result));
    return true;
}
template<class T> inline bool __FindPatternAddressCompact(T& result, const char* signature, int index = 0)
{ return __FindPatternAddress(result, signature, index); }
