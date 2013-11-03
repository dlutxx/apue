#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "lib.h"

int main(int argc, char* argv[])
{
    if (argc<2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    int fd;
    if ((fd=open(argv[1], O_RDWR|O_CREAT|O_APPEND|O_SYNC, 0664))<0) {
        err_sys("can't open file");
    }

    char msg[] = "appended message\n";
    if (write(fd, msg, strlen(msg))<strlen(msg)) {
        err_sys("write error");
    }
    int len=0;
    if ((len=pread(fd, msg, 3, 0))<0) {
        err_sys("pread error");
    }
    msg[len] = '\0';
    printf("first 3 chars: %s\n", msg);
    if (0>lseek(fd, 3, SEEK_SET))
        err_sys("lseek error");
    if ((len=read(fd, msg, 3))<0) {
        err_sys("read error");
    }
    msg[len] = '\0';
    printf("second 3 chars: %s\n", msg);
    if ((len=read(fd, msg, 3))<0) {
        err_sys("read error");
    }
    msg[len] = '\0';
    printf("third 3 chars: %s\n", msg);
    char msg2[] = "twice appending";
    if (write(fd, msg2, strlen(msg2))<strlen(msg2)) {
        err_sys("write error");
    }
    fsync(fd);
    close(fd);
    return 0;
}

