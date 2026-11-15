//
// Created by Dwayne Edwards on 2026-11-14.
//

#ifndef CLIB_CONTAINERS_LIST_H
#define CLIB_CONTAINERS_LIST_H

#include "clib/core/base.h"
#include "clib/memory/arena.h"


struct ListHeader
{
  USize length;
  USize capacity;
};

#define list_header(l, a) CastPtr(struct ListHeader, (CastPtr(void, l) - AlignPow2(SizeOf(struct ListHeader), (a))))
#define list_push(arena, l, v)                                                                                         \
  *CastPtr(TypeOf(**l), list_push_(arena, CastPtr(void*, l), SizeOf(**l), AlignOf(**l))) = v
#define list_pop(l)      *CastPtr(TypeOf(*l), list_pop_(l, SizeOf(*l), AlignOf(*l)))
#define list_peek(l)     *CastPtr(TypeOf(*l), list_peek_(l, SizeOf(*l), AlignOf(*l)))
#define list_clear(l)    list_header(l, AlignOf(*l))->length = 0
#define list_length(l)   list_header(l, AlignOf(*l))->length
#define list_capacity(l) list_header(l, AlignOf(*l))->capacity

void*
list_push_(struct Arena* arena, void** list, USize size, USize align);

void*
list_pop_(void* list, USize size, USize align);

void*
list_peek_(void* list, USize size, USize align);

#endif // CLIB_CONTAINERS_LIST_H
