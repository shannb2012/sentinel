#include <stdio.h>
#include <stdlib.h>
#include "sentinel_cli.h"
#include "sentinel_scan.h"

int main(int argc, char* argv[])
{
    printf("Sentinel Antivirus\n");
    printf("Version 0.0.1\n");

    const char *path = NULL;
    if (sentinel_cli_parse(argc, argv, &path) != EXIT_SUCCESS) {
        return SENTINEL_SCAN_ERROR;
    }

    if (!sentinel_cli_validate_path(path)) {
        fprintf(stderr, "Invalid path: %s\n", path);
        return SENTINEL_SCAN_ERROR;
    }

    sentinel_scan_result_t result = sentinel_scan_path(path);

    switch (result) {
        case SENTINEL_SCAN_CLEAN:
            printf("Clean: %s\n", path);
            break;
        case SENTINEL_SCAN_INFECTED:
            printf("Infected: %s\n", path);
            break;
        case SENTINEL_SCAN_ERROR:
        default:
            printf("Error scanning: %s\n", path);
            break;
    }

    /* verdict values are the exit codes by construction (see sentinel_scan.h) --
       usage/path errors above are folded into the same ERROR code so a script
       checking for exit code 1 unambiguously means "infected", never "bad args" */
    return (int)result;
}
