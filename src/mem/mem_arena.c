//
// Created by Dwayne Edwards on 2026-11-08.
//

#include "clib/mem/mem_arena.h"

#include "clib/core/core_assert.h"
#include "clib/core/core_base.h"
#include "clib/core/core_log.h"
#include "clib/mem/mem_base.h"


extern void*
os_reserve(U64 size);

extern B32
os_commit(void* ptr, U64 size);

extern B32
os_decommit(void* ptr, U64 size);

extern void
os_release(void* ptr, U64 size);

void
arena_create_(struct Arena* arena, struct ArenaConfig config)
{
  const U64 committed = AlignPow2(config.commit, os_pagesize());
  const U64 reserved  = AlignPow2(config.reserve, os_pagesize());

  arena->buf = os_reserve(reserved);
  os_commit(arena->buf, committed);

  if (arena->buf == 0)
  {
    LogPanic("Unexpected memory allocation failure.");
  }

  arena->offset         = 0;
  arena->committed      = committed;
  arena->config.commit  = committed;
  arena->config.reserve = reserved;
}

void
arena_destroy(struct Arena* arena)
{
  os_release(arena->buf, arena->config.reserve);
  arena->buf       = 0;
  arena->offset    = 0;
  arena->committed = 0;
}

void*
arena_push_(struct Arena* arena, SSize size, SSize align, U64 count, enum ArenaFlags flags)
{
  if (arena->buf == 0)
  {
    if (arena->config.reserve == 0)
    {
      arena_create(arena);
    }
    else
    {
      arena_create(arena, arena->config);
    }
  }

  const U64 pre_commit  = AlignPow2(arena->offset, align);
  const U64 post_commit = pre_commit + (size * count);

  const U64 zero_memory_size = Min(arena->committed, post_commit) - pre_commit;

  if (arena->committed < post_commit)
  {
    U64 commit_post_aligned = post_commit + arena->committed - 1;
    commit_post_aligned -= commit_post_aligned % arena->committed;
    const U64 commit_post_clamped = ClampTop(commit_post_aligned, arena->config.reserve);
    const U64 commit_size         = commit_post_clamped - arena->committed;
    U8*       commit_ptr          = arena->buf + arena->committed;
    os_commit(commit_ptr, commit_size);
    arena->committed = commit_post_clamped;
  }

  void* buf = 0;
  if (arena->committed >= post_commit)
  {
    buf           = arena->buf + pre_commit;
    arena->offset = post_commit;
    if (FLAG_IS_UNSET(flags, ARENA_NO_ZERO))
    {
      MemoryZero(buf, zero_memory_size);
    }
  }

  if (buf == 0 && FLAG_IS_SET(flags, ARENA_SOFT_FAIL))
  {
    LogPanic("Unexpected memory allocation failure.");
  }

  return buf;
}

void
arena_clear(struct Arena* arena)
{
  arena->offset = 0;
}

U64
arena_used(struct Arena arena)
{
  return arena.offset;
}

U64
arena_available(struct Arena arena)
{
  return arena.committed - arena.offset;
}
