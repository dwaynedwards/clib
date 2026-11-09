//
// Created by Dwayne Edwards on 2026-11-08.
//

#ifndef CLIB_PLATFORM_BASE_H
#define CLIB_PLATFORM_BASE_H

#include <stddef.h>
#include <stdint.h>


#if defined(__clang__)
#define COMPILER_CLANG 1
#else
#error Compiler not supported.
#endif

#if defined(__APPLE__) && defined(__MACH__)
#define PLATFORM_MACOS 1
#else
#error OS is not supported.
#endif

typedef int32_t   B32;
typedef int8_t    S8;
typedef int16_t   S16;
typedef int32_t   S32;
typedef int64_t   S64;
typedef uint8_t   U8;
typedef uint16_t  U16;
typedef uint32_t  U32;
typedef uint64_t  U64;
typedef float     F32;
typedef double    F64;
typedef size_t    USize;
typedef ptrdiff_t SSize;
typedef uintptr_t UPtr;

extern void
os_abort(U64 exit_code);

extern U64
os_pagesize(void);

extern void*
memory_reserve(U64 size);

extern B32
memory_commit(void* ptr, U64 size);

extern B32
memory_decommit(void* ptr, U64 size);

extern void
memory_release(void* ptr, U64 size);

#endif // CLIB_PLATFORM_BASE_H
