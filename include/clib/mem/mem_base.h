//
// Created by Dwayne Edwards on 2026-11-08.
//

#ifndef CLIB_MEM_BASE_H
#define CLIB_MEM_BASE_H

#include <string.h>


#if COMPILER_CLANG
#define AlignOf(T) __alignof__(T)
#else
#error AlignOf not defined for this compiler.
#endif

#define AlignPow2(x, b) (((x) + (b) - 1) & (~((b) - 1)))

#define MemorySet(dst, byte, size) memset((dst), (byte), (size))
#define MemoryZero(ptr, size)      MemorySet((ptr), 0, (size))

#define MemoryCopy(dst, src, size) memcpy((dst), (src), (size))

#endif // CLIB_MEM_BASE_H
