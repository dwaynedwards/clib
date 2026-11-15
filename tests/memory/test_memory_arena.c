//
// Created by Dwayne Edwards on 2026-11-08.
//

#include <unity.h>

#include "clib/memory/arena.h"


Internal struct Arena arena;

void
setUp(void)
{
  arena_create(&arena);
}

void
tearDown(void)
{
  arena_destroy(&arena);
}

static void
test_arena_size(void)
{
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(48, SizeOf(struct Arena), "SizeOf(struct Arena) should be 48 bytes");
}

static void
test_arena_create(void)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(arena.buf, "arena buf should not be null");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, arena_used(&arena), "arena memory used should be 0 bytes");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(65536, arena_available(&arena), "arena memory available should be 65536 bytes");
}

static void
test_arena_push(void)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(arena_push(&arena, U64), "data should not be null");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(8, arena_used(&arena), "arena memory used should be 48 bytes");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(65528, arena_available(&arena), "arena memory available should be 65528 bytes");
}

static void
scratch_arena_push(struct Arena* scratch)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(arena_push(scratch, U64, 3), "data should not be null");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(40, arena_used(scratch), "arena memory used should be 40 bytes");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(65496, arena_available(scratch), "arena memory available should be 65496 bytes");
}

static void
test_scratch_arena_push(void)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(arena_push(&arena, U64, 2), "data should not be null");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(16, arena_used(&arena), "arena memory used should be 16 bytes");
  struct Arena scratch = arena;
  scratch_arena_push(&scratch);
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(16, arena_used(&arena), "arena memory used should be 16 bytes");
  TEST_ASSERT_NOT_NULL_MESSAGE(arena_push(&arena, U64, 3), "data should not be null");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(40, arena_used(&arena), "arena memory used should be 40 bytes");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(65496, arena_available(&arena), "arena memory available should be 65496 bytes");
}

static void
test_arena_clear(void)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(arena_push(&arena, U64, 2), "data should not be null");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(16, arena_used(&arena), "arena memory used should be 16 bytes");
  arena_clear(&arena);
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, arena_used(&arena), "arena memory used should be 0 bytes");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(65536, arena_available(&arena), "arena memory available should be 65536 bytes");
}

static void
test_arena_destroy(void)
{
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, arena_used(&arena), "arena memory used should be 0 bytes");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(65536, arena_available(&arena), "arena memory available should be 65536 bytes");
  arena_destroy(&arena);
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, arena_used(&arena), "arena memory used should be 0 bytes");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, arena_available(&arena), "arena memory available should be 0 bytes");
  TEST_ASSERT_NOT_NULL_MESSAGE(arena_push(&arena, U64, 10), "data should not be null");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(80, arena_used(&arena), "arena memory used should be 80 bytes");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(65456, arena_available(&arena), "arena memory available should be 65456 bytes");
}

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_arena_size);
  RUN_TEST(test_arena_create);
  RUN_TEST(test_arena_push);
  RUN_TEST(test_scratch_arena_push);
  RUN_TEST(test_arena_clear);
  RUN_TEST(test_arena_destroy);

  return UNITY_END();
}
