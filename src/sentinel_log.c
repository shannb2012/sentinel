#include "sentinel_log.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#ifdef DEBUG
static sentinel_log_level_t g_min_level = SENTINEL_LOG_DEBUG;
#else
static sentinel_log_level_t g_min_level = SENTINEL_LOG_INFO;
#endif

void sentinel_log_set_level(sentinel_log_level_t level)
{
    g_min_level = level;
}

sentinel_log_level_t sentinel_log_get_level(void)
{
    return g_min_level;
}

static const char* level_name(sentinel_log_level_t level)
{
    static const char* names[] = { "DEBUG", "INFO", "WARN", "ERROR" };
    return names[level];
}

void sentinel_log_write(sentinel_log_level_t level, const char *file, int line, const char *func, const char *fmt, ...)
{
    #ifndef DEBUG
        (void)file;
        (void)line;
        (void)func;
    #endif

    if (level < g_min_level) {
        return;
    }

    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_now);

#ifdef DEBUG
    fprintf(stderr, "[%s] [%s] [%s:%d %s] ", timestamp, level_name(level), file, line, func);
#else
    fprintf(stderr, "[%s] [%s] ", timestamp, level_name(level));
#endif

va_list args;
va_start(args, fmt);
vfprintf(stderr, fmt, args);
va_end(args);

fputc('\n', stderr);

}
