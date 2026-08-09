#ifndef SENTINEL_SCAN_H
#define SENTINEL_SCAN_H

typedef enum sentinel_scan_result {
    SENTINEL_SCAN_CLEAN = 0,
    SENTINEL_SCAN_INFECTED = 1,
    SENTINEL_SCAN_ERROR = 2
} sentinel_scan_result_t;

sentinel_scan_result_t sentinel_scan_path(const char *path);

#endif
