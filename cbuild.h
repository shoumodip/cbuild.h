#ifndef CBUILD_H
#define CBUILD_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

long last_modified(const char *file_path)
{
    struct stat attr;
    stat(file_path, &attr);
    return attr.st_mtime;
}

#ifndef CC
#define CC "cc"
#endif

#ifndef CFLAGS
#define CFLAGS "-Wall", "-Wextra", "-std=c11", "-pedantic"
#endif

#define rebuild(argc, argv)                 \
    do {                                    \
        rebuild_impl(argc, argv, __FILE__); \
    } while (0)

void rebuild_impl(int argc, char **argv, char *file)
{
    assert(argc);

    if (last_modified(file) > last_modified(argv[0])) {
        int child = fork();

        if (child == 0) {
            char *compile[] = {CC, CFLAGS, "-o", argv[0], file, NULL};

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
                execvp(argv[0], argv);
            }
        }

        exit(1);
    }
}

#endif // CBUILD_H
