//
// Created by Dwayne Edwards on 2026-11-14.
//

#include "clib/containers/list.h"


#include <unity.h>

#include "clib/core/base.h"


Internal struct Arena arena;
Internal U64*         int_list;

void
setUp(void)
{
  arena_create(&arena);
}

void
tearDown(void)
{
  int_list = 0;
  arena_destroy(&arena);
}

static void
test_list_append(void)
{
  list_push(&arena, &int_list, 10);
  list_length(int_list);
  TEST_ASSERT_EQUAL_UINT64(10, int_list[0]);
  TEST_ASSERT_EQUAL_UINT64(1, list_length(int_list));
  TEST_ASSERT_EQUAL_UINT64(1, list_capacity(int_list));
}

static void
test_list_append_grow(void)
{
  list_push(&arena, &int_list, 20);
  TEST_ASSERT_EQUAL_UINT64(20, int_list[0]);
  TEST_ASSERT_EQUAL_UINT64(1, list_length(int_list));
  TEST_ASSERT_EQUAL_UINT64(1, list_capacity(int_list));
  list_push(&arena, &int_list, 30);
  TEST_ASSERT_EQUAL_UINT64(30, int_list[1]);
  TEST_ASSERT_EQUAL_UINT64(2, list_length(int_list));
  TEST_ASSERT_EQUAL_UINT64(2, list_capacity(int_list));
  list_push(&arena, &int_list, 40);
  TEST_ASSERT_EQUAL_UINT64(40, int_list[2]);
  TEST_ASSERT_EQUAL_UINT64(3, list_length(int_list));
  TEST_ASSERT_EQUAL_UINT64(4, list_capacity(int_list));
}

static void
test_list_pop(void)
{
  list_push(&arena, &int_list, 50);
  list_push(&arena, &int_list, 60);
  list_push(&arena, &int_list, 70);
  const U64 value = list_pop(int_list);
  TEST_ASSERT_EQUAL_UINT64(70, value);
  TEST_ASSERT_EQUAL_UINT64(2, list_length(int_list));
  TEST_ASSERT_EQUAL_UINT64(4, list_capacity(int_list));
}

static void
test_list_peek(void)
{
  list_push(&arena, &int_list, 80);
  list_push(&arena, &int_list, 90);
  list_push(&arena, &int_list, 100);
  const U64 value = list_peek(int_list);
  TEST_ASSERT_EQUAL_UINT64(100, value);
  TEST_ASSERT_EQUAL_UINT64(3, list_length(int_list));
  TEST_ASSERT_EQUAL_UINT64(4, list_capacity(int_list));
}

static void
test_list_clear(void)
{
  list_push(&arena, &int_list, 110);
  list_push(&arena, &int_list, 120);
  list_push(&arena, &int_list, 130);
  list_clear(int_list);
  TEST_ASSERT_EQUAL_UINT64(0, list_length(int_list));
  TEST_ASSERT_EQUAL_UINT64(4, list_capacity(int_list));
}

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_list_append);
  RUN_TEST(test_list_append_grow);
  RUN_TEST(test_list_pop);
  RUN_TEST(test_list_peek);
  RUN_TEST(test_list_clear);

  return UNITY_END();
}
