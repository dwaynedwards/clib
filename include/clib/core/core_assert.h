//
// Created by Dwayne Edwards on 2026-11-08.
//

#ifndef CLIB_CORE_ASSERT_H
#define CLIB_CORE_ASSERT_H

#include "clib/core/core_base.h"


#if COMPILER_CLANG
#define Trap() __builtin_trap()
#else
#error Unknown trap intrinsic for this compiler.
#endif

#define AssertAlways(x)                                                                                                \
  do                                                                                                                   \
  {                                                                                                                    \
    if (!(x))                                                                                                          \
    {                                                                                                                  \
      Trap();                                                                                                          \
    }                                                                                                                  \
  } while (0)
#ifdef DEBUG
#define Assert(x) AssertAlways(x)
#else
#define Assert(x) (void)(x)
#endif

#endif // CLIB_CORE_ASSERT_H
