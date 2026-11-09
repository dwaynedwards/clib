//
// Created by Dwayne Edwards on 2026-11-08.
//

#ifndef CLIB_MEM_ARENA_H
#define CLIB_MEM_ARENA_H

#include "clib/core/core_base.h"


enum ArenaFlags
{
  ARENA_NONE      = 0,
  ARENA_NO_ZERO   = 1 << 0,
  ARENA_SOFT_FAIL = 1 << 1,
  ARENA_ALL       = (1 << 2) - 1
};

struct ArenaConfig
{
  U64 commit;
  U64 reserve;
};

struct Arena
{
  U8*                buf;
  U64                offset;
  U64                committed;
  struct ArenaConfig config;
};

#define arena_create(...)           arena_createx(__VA_ARGS__, arena_create2, arena_create1)(__VA_ARGS__)
#define arena_createx(a, b, c, ...) c
#define arena_create1(a)                                                                                               \
  arena_create_(a, (struct ArenaConfig){                                                                               \
                       .commit  = KB(64),                                                                              \
                       .reserve = MB(64),                                                                              \
                   })
#define arena_create2(a, c) arena_create_(a, c)

void
arena_create_(struct Arena* arena, struct ArenaConfig config);

void
arena_destroy(struct Arena* arena);

#define arena_push(...)                 arena_pushx(__VA_ARGS__, arena_push4, arena_push3, arena_push2)(__VA_ARGS__)
#define arena_pushx(a, b, c, d, e, ...) e
#define arena_push2(a, t)               CastPtr(t, arena_push_(a, SizeOf(t), AlignOf(t), 1, ARENA_NONE))
#define arena_push3(a, t, n)            CastPtr(t, arena_push_(a, SizeOf(t), AlignOf(t), n, ARENA_NONE))
#define arena_push4(a, t, n, f)         CastPtr(t, arena_push_(a, SizeOf(t), AlignOf(t), n, f))

void*
arena_push_(struct Arena* arena, SSize size, SSize align, U64 count, enum ArenaFlags flags);

void
arena_clear(struct Arena* arena);

U64
arena_used(struct Arena arena);

U64
arena_available(struct Arena arena);

#endif // CLIB_MEM_ARENA_H
