#ifndef SENTINEL_LOG_H
#define SENTINEL_LOG_H

typedef enum sentinel_log_level {
    SENTINEL_LOG_DEBUG = 0,
    SENTINEL_LOG_INFO,
    SENTINEL_LOG_WARN,
    SENTINEL_LOG_ERROR
} sentinel_log_level_t;

void sentinel_log_set_level(sentinel_log_level_t level);
sentinel_log_level_t sentinel_log_get_level(void);
void sentinel_log_write(sentinel_log_level_t level, const char *file, int line, const char *func, const char *fmt, ...)
    __attribute__((format(printf, 5, 6)));

#define sentinel_log_debug(...) sentinel_log_write(SENTINEL_LOG_DEBUG, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define sentinel_log_info(...)  sentinel_log_write(SENTINEL_LOG_INFO,  __FILE__, __LINE__, __func__, __VA_ARGS__)
#define sentinel_log_warn(...)  sentinel_log_write(SENTINEL_LOG_WARN,  __FILE__, __LINE__, __func__, __VA_ARGS__)
#define sentinel_log_error(...) sentinel_log_write(SENTINEL_LOG_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)

#endif
