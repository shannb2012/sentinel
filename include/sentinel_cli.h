#ifndef SENTINEL_CLI_H
#define SENTINEL_CLI_H

int sentinel_cli_validate_path(const char *path);
int sentinel_cli_parse(int argc, char *argv[], const char **path_out);

#endif
