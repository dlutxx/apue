#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

//extern int asprintf(char**, char*, ...);

int main(int argc, char* argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (fd<0) {
        perror("can't open");
        return 1;
    }
    int len = 1024, n=0;
    char buff[len];
    do {
        n = read(fd, buff, len-1);
        if (n>0) {
            buff[n] = '\0';
            printf("%s", buff);
        }
    } while (n<0 && EINTR==errno);
    if (n<0) {
        char* err=NULL;
        asprintf(&err, "cant read %s", argv[1]);
        perror(err);
        free(err);
        return 1;
    }

    printf("\n");
    return 0;
}

