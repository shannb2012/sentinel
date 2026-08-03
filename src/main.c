#include <stdio.h>
#include "sentinel_log.h"

int main(void)
{
    printf("Sentinel Antivirus\n");
    printf("Version 0.0.1\n");

    sentinel_log_debug("Log debug");
    sentinel_log_info("Log info");
    sentinel_log_warn("Log warn");
    sentinel_log_error("Log error");

    return 0;
}
