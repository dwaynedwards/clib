//
// Created by Dwayne Edwards on 2026-11-08.
//

#ifndef CLIB_CORE_BASE_H
#define CLIB_CORE_BASE_H

#include "clib/platform/base.h"

#define Global   static
#define Internal static

#if COMPILER_CLANG
#define Inline       inline
#define ForceInline  inline __attribute__((always_inline))
#define StaticInline static inline
#endif

#define TypeOf(t)   __typeof__(t)
#define SizeOf(t)   (SSize)sizeof(t)
#define CountOf(a)  (SizeOf(a) / SizeOf(*(a)))
#define LengthOf(s) (CountOf(s) - 1)

#define KB(n) (((U64)(n)) << 10)
#define MB(n) (((U64)(n)) << 20)
#define GB(n) (((U64)(n)) << 30)
#define TB(n) (((U64)(n)) << 40)

#define Cast(t, x)    ((t)(x))
#define CastPtr(t, x) ((t*)(x))

#define Min(a, b)         (((a) < (b)) ? (a) : (b))
#define Max(a, b)         (((a) > (b)) ? (a) : (b))
#define ClampTop(a, x)    Min(a, x)
#define ClampBottom(x, b) Max(x, b)
#define Clamp(a, x, b)    (((x) < (a)) ? (a) : ((x) > (b)) ? (b) : (x))

#define FlagSet(f, v)     ((f) |= (v))
#define FlagUnset(f, v)   ((f) &= ~(v))
#define IsFlagSet(f, v)   ((f) & (v))
#define IsFlagUnset(f, v) !IsFlagSet(f, v)

#endif // CLIB_CORE_BASE_H
