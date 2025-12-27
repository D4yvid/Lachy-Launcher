#pragma once

#include <cstdarg>
#include <cstdlib>
#include <string>

#define LogFuncDef(name, logLevel)                         \
  static void name(const char* tag, const char* text, ...) \
      __attribute__((format(printf, 2, 3)))                \
  {                                                        \
    va_list args;                                          \
    va_start(args, text);                                  \
    vlog(logLevel, tag, text, args);                       \
    va_end(args);                                          \
  }

enum class LogLevel
{
  LOG_TRACE,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR
};

class Log
{
 private:
  static LogLevel minLevel;
  static bool initialized;
  
 public:
  // Initialize the logging system (call once at startup)
  static void init();
  
  static inline const char* getLogLevelString(LogLevel lvl)
  {
    if (lvl == LogLevel::LOG_TRACE) return "TRACE";
    if (lvl == LogLevel::LOG_DEBUG) return "DEBUG";
    if (lvl == LogLevel::LOG_INFO) return " INFO";
    if (lvl == LogLevel::LOG_WARN) return " WARN";
    if (lvl == LogLevel::LOG_ERROR) return "ERROR";
    return "?????";
  }
  
  static void setMinLevel(LogLevel level);
  static LogLevel getMinLevel() { return minLevel; }

  static void vlog(LogLevel level, const char* tag, const char* text,
                   va_list args);

  static void log(LogLevel level, const char* tag, const char* text, ...)
  {
    va_list args;
    va_start(args, text);
    vlog(level, tag, text, args);
    va_end(args);
  }

  LogFuncDef(trace, LogLevel::LOG_TRACE) 
  LogFuncDef(debug, LogLevel::LOG_DEBUG)
  LogFuncDef(info, LogLevel::LOG_INFO) 
  LogFuncDef(warn, LogLevel::LOG_WARN)
  LogFuncDef(error, LogLevel::LOG_ERROR)
};

#undef LogFuncDef
