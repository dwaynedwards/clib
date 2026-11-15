//
// Created by Dwayne Edwards on 2026-11-08.
//

#ifndef CLIB_MEMORY_ARENA_H
#define CLIB_MEMORY_ARENA_H

#include "clib/core/base.h"
#include "clib/memory/base.h"

enum ArenaFlags
{
  ARENA_NONE      = 0,
  ARENA_NO_ZERO   = 1 << 0,
  ARENA_SOFT_FAIL = 1 << 1,
  ARENA_ALL       = (1 << 2) - 1
};

struct ArenaConfig
{
  U64             commit;
  U64             reserve;
  enum ArenaFlags flags;
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
                       .flags   = ARENA_NONE,                                                                          \
                   })
#define arena_create2(a, c) arena_create_(a, c)

void
arena_create_(struct Arena* arena, struct ArenaConfig config);

void
arena_destroy(struct Arena* arena);

#define arena_push(...)                 arena_pushx(__VA_ARGS__, arena_push4, arena_push3, arena_push2)(__VA_ARGS__)
#define arena_pushx(a, b, c, d, e, ...) e
#define arena_push2(arena, t)           CastPtr(TypeOf(t), arena_push_(arena, SizeOf(t), AlignOf(t), 1))
#define arena_push3(arena, t, c)        CastPtr(TypeOf(t), arena_push_(arena, SizeOf(t), AlignOf(t), c))
#define arena_push4(arena, s, a, c)     CastPtr(void, arena_push_(arena, s, a, c))

void*
arena_push_(struct Arena* arena, USize size, USize align, U64 count);

const void*
arena_peek(const struct Arena* arena);

void
arena_clear(struct Arena* arena);

USize
arena_used(const struct Arena* arena);

USize
arena_available(const struct Arena* arena);

#endif // CLIB_MEMORY_ARENA_H
