#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace cleo {
struct ScriptMemory {
    const uint8_t* code;
    size_t size;
    bool contains(const void* pointer,size_t bytes) const {
        const uintptr_t start=reinterpret_cast<uintptr_t>(code);
        const uintptr_t address=reinterpret_cast<uintptr_t>(pointer);
        return address>=start && address-start<=size && bytes<=size-(address-start);
    }
    const uint8_t* label(int32_t offset) const {
        const uint32_t magnitude=offset<0 ? 0u-uint32_t(offset) : uint32_t(offset);
        return magnitude<size ? code+magnitude : nullptr;
    }
    size_t stringLength(const uint8_t* pointer) const {
        if (!contains(pointer,1)) return SIZE_MAX;
        const size_t remaining=size-(reinterpret_cast<uintptr_t>(pointer)-reinterpret_cast<uintptr_t>(code));
        const void* end=std::memchr(pointer,0,remaining);
        return end ? static_cast<const uint8_t*>(end)-pointer : SIZE_MAX;
    }
};
template<class T> T readUnaligned(const void* address) {
    T value;std::memcpy(&value,address,sizeof(value));return value;
}
}
