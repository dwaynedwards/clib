//
// Created by Dwayne Edwards on 2026-11-14.
//

#include "clib/containers/list.h"
#include "clib/core/base.h"
#include "clib/core/log.h"


Internal void*
list_grow(struct Arena* arena, const void* list, USize size, USize align)
{
  USize length           = 0;
  USize capacity         = 1;
  USize list_copy_length = 0;

  if (list != 0)
  {
    const struct ListHeader* header = list_header(list, align);
    if (header->length < header->capacity)
    {
      return CastPtr(void, list);
    }

    length           = header->length;
    capacity         = header->capacity * 2;
    list_copy_length = size * header->length;
  }

  const USize        header_offset = AlignPow2(SizeOf(struct ListHeader), align);
  void*              data          = arena_push(arena, header_offset + (size * capacity), align, 1);
  struct ListHeader* header        = CastPtr(struct ListHeader, data);
  header->length                   = length;
  header->capacity                 = capacity;
  void* list_copy                  = data + header_offset;
  MemoryCopy(list_copy, list, list_copy_length);
  return list_copy;
}

void*
list_push_(struct Arena* arena, void** list, USize size, USize align)
{
  *list = list_grow(arena, *list, size, align);
  return *list + (size * list_header(*list, align)->length++);
}

void*
list_pop_(void* list, USize size, USize align)
{
  struct ListHeader* header = list_header(list, align);
  return list + (size * --list_header(list, align)->length);
}

void*
list_peek_(void* list, USize size, USize align)
{
  return list + (size * (list_header(list, align)->length - 1));
}
