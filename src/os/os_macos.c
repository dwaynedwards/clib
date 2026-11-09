//
// Created by Dwayne Edwards on 2026-11-08.
//

#include "clib/core/core_base.h"

#ifdef OS_MACOS

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>


void
os_abort(U64 exit_code)
{
  exit(Cast(int, exit_code));
}

U64
os_pagesize(void)
{
  return getpagesize();
}

void*
os_reserve(U64 size)
{
  void* mem = mmap(0, size, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
  if (mem == MAP_FAILED)
  {
    mem = 0;
  }
  return mem;
}

B32
os_commit(void* ptr, U64 size)
{
  return mprotect(ptr, size, PROT_READ | PROT_WRITE) == 0;
}

B32
os_decommit(void* ptr, U64 size)
{
  return madvise(ptr, size, MADV_DONTNEED) == mprotect(ptr, size, PROT_NONE) == 0;
}

void
os_release(void* ptr, U64 size)
{
  munmap(ptr, size);
}

#endif // OS_MACOS
