//
// Created by Dwayne Edwards on 2026-11-08.
//

#include "clib/core/core_base.h"

#include <unity.h>


void
setUp(void)
{
}

void
tearDown(void)
{
}

static void
test_core_defines(void)
{
  TEST_ASSERT_EQUAL_INT(SizeOf(B32), 4);
  TEST_ASSERT_EQUAL_INT(SizeOf(S8), 1);
  TEST_ASSERT_EQUAL_INT(SizeOf(S16), 2);
  TEST_ASSERT_EQUAL_INT(SizeOf(S32), 4);
  TEST_ASSERT_EQUAL_INT(SizeOf(S64), 8);
  TEST_ASSERT_EQUAL_INT(SizeOf(U8), 1);
  TEST_ASSERT_EQUAL_INT(SizeOf(U16), 2);
  TEST_ASSERT_EQUAL_INT(SizeOf(U32), 4);
  TEST_ASSERT_EQUAL_INT(SizeOf(U64), 8);
  TEST_ASSERT_EQUAL_INT(SizeOf(F32), 4);
  TEST_ASSERT_EQUAL_INT(SizeOf(F64), 8);
  TEST_ASSERT_EQUAL_INT(SizeOf(USize), 8);
  TEST_ASSERT_EQUAL_INT(SizeOf(SSize), 8);

  U64 array[10];
  TEST_ASSERT_EQUAL_INT(CountOf(array), 10);

  const char str[] = "What is the length of this string?";
  TEST_ASSERT_EQUAL_INT(LengthOf(str), 34);
}

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_core_defines);

  return UNITY_END();
}
