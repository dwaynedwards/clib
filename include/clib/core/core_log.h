//
// Created by Dwayne Edwards on 2026-11-08.
//

#ifndef CLIB_CORE_LOG_H
#define CLIB_CORE_LOG_H

#include "clib/core/core_base.h"


enum LogLevel
{
  LOG_LEVEL_OFF,
  LOG_LEVEL_PANIC,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_COUNT,
};

#define Log(level, fmt, ...) log_message_(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LogPanic(fmt, ...)   Log(LOG_LEVEL_PANIC, fmt, ##__VA_ARGS__)
#define LogDebug(fmt, ...)   Log(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define LogInfo(fmt, ...)    Log(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LogWarn(fmt, ...)    Log(LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LogError(fmt, ...)   Log(LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)

Inline void
set_log_level(enum LogLevel level);

void
log_message_(enum LogLevel level, const char* file, U32 line, char* fmt, ...);

#endif // CLIB_CORE_LOG_H
