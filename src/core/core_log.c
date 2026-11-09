//
// Created by Dwayne Edwards on 2026-11-08.
//

#include "clib/core/core_log.h"


#include <stdarg.h>
#include <stdio.h>


Global enum LogLevel g_logLevel = LOG_LEVEL_ERROR;

Inline void
set_log_level(enum LogLevel level)
{
  g_logLevel = level;
}

Internal const char*
get_log_level_string(enum LogLevel level)
{
  switch (level)
  {
    case LOG_LEVEL_PANIC: return "PANIC";
    case LOG_LEVEL_DEBUG: return "DEBUG";
    case LOG_LEVEL_INFO: return "INFO";
    case LOG_LEVEL_WARN: return "WARN";
    case LOG_LEVEL_ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}

void
log_message_(enum LogLevel level, const char* file, U32 line, char* fmt, ...)
{
  if (level <= LOG_LEVEL_OFF || level > g_logLevel)
  {
    return;
  }

  printf("[%s] ", get_log_level_string(level));

  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);

  printf(" %s:%d\n", file, line);

  if (level != LOG_LEVEL_PANIC)
  {
    return;
  }

  os_abort(1);
}
