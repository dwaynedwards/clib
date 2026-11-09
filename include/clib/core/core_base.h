//
// Created by Dwayne Edwards on 2026-11-08.
//

#ifndef CLIB_CORE_BASE_H
#define CLIB_CORE_BASE_H

#include <stddef.h>
#include <stdint.h>

#if defined(__clang__)
#define COMPILER_CLANG 1
#else
#error Compiler not supported.
#endif

#if defined(__APPLE__) && defined(__MACH__)
#define OS_MACOS 1
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

#define Global   static
#define Internal static

#if COMPILER_CLANG
#define Inline       inline
#define ForceInline  inline __attribute__((always_inline))
#define StaticInline static inline
#endif

#define SizeOf(x)   (SSize)sizeof(x)
#define CountOf(a)  (SizeOf(a) / SizeOf(*(a)))
#define LengthOf(s) (CountOf(s) - 1)

#define KB(n) (((U64)(n)) << 10)
#define MB(n) (((U64)(n)) << 20)
#define GB(n) (((U64)(n)) << 30)
#define TB(n) (((U64)(n)) << 40)

#define Cast(T, x)    ((T)(x))
#define CastPtr(T, x) ((T*)(x))

#define Min(a, b)         (((a) < (b)) ? (a) : (b))
#define Max(a, b)         (((a) > (b)) ? (a) : (b))
#define ClampTop(a, x)    Min(a, x)
#define ClampBottom(x, b) Max(x, b)
#define Clamp(a, x, b)    (((x) < (a)) ? (a) : ((x) > (b)) ? (b) : (x))

#define FLAG_SET(f, v)      (f |= v)
#define FLAG_UNSET(f, v)    (f &= ~v)
#define FLAG_IS_SET(f, v)   (f & v)
#define FLAG_IS_UNSET(f, v) !FLAG_IS_SET(f, v)

#endif // CLIB_CORE_BASE_H
