#include "sentinel_scan.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "sha256.h"

#define CHUNK_SIZE 65536

static const char *KNOWN_BAD_HASHES[] = {
    "275a021bbfb6489e54d471899f7db9d1663fc695ec2fe2a2c4538aabf651fd0f", /* EICAR standard test file */
};

#define KNOWN_BAD_COUNT (sizeof(KNOWN_BAD_HASHES) / sizeof(KNOWN_BAD_HASHES[0]))

static int is_known_bad(const char *hex_digest)
{
    for (size_t i = 0; i < KNOWN_BAD_COUNT; i++) {
        if (strcmp(hex_digest, KNOWN_BAD_HASHES[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static void digest_to_hex(const uint8_t digest[32], char hex_out[65])
{
    for (int i = 0; i < 32; i++) {
        snprintf(hex_out + i * 2, 3, "%02x", digest[i]);
    }
}

sentinel_scan_result_t sentinel_scan_path(const char *path)
{
    FILE *file;
#ifdef _WIN32
    fopen_s(&file, path, "rb");
#else
    file = fopen(path, "rb");
#endif
    if (file == NULL) {
        return SENTINEL_SCAN_ERROR;
    }

    sha256_ctx ctx;
    sha256_init(&ctx);

    char buffer[CHUNK_SIZE];
    size_t bytes_read = 0;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        sha256_update(&ctx, (uint8_t *)buffer, bytes_read);
    }

    if (ferror(file)) {
        fclose(file);
        return SENTINEL_SCAN_ERROR;
    }
    fclose(file);

    uint8_t digest[32];
    sha256_final(&ctx, digest);

    char hex_digest[65];
    digest_to_hex(digest, hex_digest);

    return is_known_bad(hex_digest) ? SENTINEL_SCAN_INFECTED : SENTINEL_SCAN_CLEAN;
}
