#include <stdio.h>
#include <stdlib.h>
#include "sentinel_cli.h"
#include "sentinel_log.h"

int main(int argc, char* argv[])
{
    printf("Sentinel Antivirus\n");
    printf("Version 0.0.1\n");

    const char *path = NULL;
    if (sentinel_cli_parse(argc, argv, &path) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (!sentinel_cli_validate_path(path)) {
        printf("Invalid path: %s\n", path);
        return EXIT_FAILURE;
    }

    printf("Path is valid\n");
    return EXIT_SUCCESS;
}
