#pragma once

#include "common.h"

// Alignment-safe accessors.
//
// Nothing read out of the game's memory is guaranteed to be naturally aligned for us.
// The script stream in particular: a command is [u16 opcode][u8 param type][4-byte value],
// so a jump/call offset sits at command + 3 - right after the type byte - and commands are
// 7 bytes long, which is why the next command can start on an odd address too.
//
// A plain lw/lh on such an address raises an Address Error on the PSP, and PPSSPP now
// reports it as an invalid memory access ("Interpreter: Add correct alignment checks to
// loads/stores" + "don't spin forever on a memory access that's set to be ignored") and
// substitutes 0, which silently corrupts the script ip and makes the game run into
// garbage. It only ever worked because the interpreter used to read misaligned addresses
// without checking.
//
// Both platforms are little-endian, so the byte-wise fallbacks below return exactly the
// same value an aligned load would.

inline uint16_t read_u16(const void *p)
{
	if ((cast<uint32_t>(p) & 1) == 0)
		return *cast<const uint16_t *>(p);

	const uint8_t *b = cast<const uint8_t *>(p);
	return (uint16_t)(b[0] | (b[1] << 8));
}

inline uint32_t read_u32(const void *p)
{
	if ((cast<uint32_t>(p) & 3) == 0)
		return *cast<const uint32_t *>(p);

	const uint8_t *b = cast<const uint8_t *>(p);
	return (uint32_t)b[0] | ((uint32_t)b[1] << 8) |
		   ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}

inline int32_t read_i32(const void *p) { return (int32_t)read_u32(p); }

inline void write_u16(void *p, uint16_t v)
{
	if ((cast<uint32_t>(p) & 1) == 0)
	{
		*cast<uint16_t *>(p) = v;
		return;
	}

	uint8_t *b = cast<uint8_t *>(p);
	b[0] = (uint8_t)v;
	b[1] = (uint8_t)(v >> 8);
}

inline void write_u32(void *p, uint32_t v)
{
	if ((cast<uint32_t>(p) & 3) == 0)
	{
		*cast<uint32_t *>(p) = v;
		return;
	}

	uint8_t *b = cast<uint8_t *>(p);
	b[0] = (uint8_t)v;
	b[1] = (uint8_t)(v >> 8);
	b[2] = (uint8_t)(v >> 16);
	b[3] = (uint8_t)(v >> 24);
}

// Generic form, for the types without an explicit helper above. memcpy is the portable way to
// do a possibly misaligned access: the compiler emits byte-wise loads/stores for it, never a
// plain lw/lh.
template <typename T> inline T read_unaligned(const void *p)
{
	T v;
	memcpy(&v, p, sizeof(T));
	return v;
}

template <typename T> inline void write_unaligned(void *p, T v)
{
	memcpy(p, &v, sizeof(T));
}
