#include "sentinel_cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifndef S_ISREG
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif

int sentinel_cli_validate_path(const char *path)
{
    if (!path || !*path) {
        return 0;
    }

    struct stat st;
    if (stat(path, &st) != 0) {
        return 0;
    }

    return S_ISREG(st.st_mode);
}

int sentinel_cli_parse(int argc, char *argv[], const char **path_out)
{
    if (argc > 2) {
        fprintf(stderr, "Only one path argument is supported.\nUsage: sentinel <path>\n");
        return EXIT_FAILURE;
    }

    if (argc < 2) {
        printf("Please enter path to be scanned.\n");
        return EXIT_FAILURE;
    }

    *path_out = argv[1];
    return EXIT_SUCCESS;
}
