#ifndef CBUILD_H
#define CBUILD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include <limits.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/wait.h>

#ifndef CC
#define CC "cc"
#endif

#ifndef CFLAGS
#define CFLAGS "-Wall", "-Wextra", "-std=c11", "-pedantic"
#endif

char rebuild_source_buffer[PATH_MAX];
char rebuild_binary_buffer[PATH_MAX];

bool rebuild_modified(void)
{
    struct stat source, binary;
    stat(rebuild_source_buffer, &source);
    stat(rebuild_binary_buffer, &binary);
    return source.st_mtime > binary.st_mtime;
}

#define rebuild(argc, argv)                 \
    do {                                    \
        rebuild_impl(argc, argv, __FILE__); \
    } while (0)

void rebuild_impl(int argc, char **argv, char *file)
{
    assert(argc);

    realpath(file, rebuild_source_buffer);
    realpath(argv[0], rebuild_binary_buffer);

    if (rebuild_modified()) {
        int child = fork();

        if (child == 0) {
            char *compile[] = {CC, CFLAGS, "-o", rebuild_binary_buffer, rebuild_source_buffer, NULL};

            printf("CMD: ");
            for (size_t i = 0; compile[i]; ++i) {
                printf("%s ", compile[i]);
            }
            puts("");

            execvp(compile[0], compile);
        } else {
            int status;
            wait(&status);

            if (WEXITSTATUS(status) == 0) {
                execvp(rebuild_binary_buffer, argv);
            }
        }

        exit(1);
    }
}

#endif // CBUILD_H
