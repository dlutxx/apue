#include "lib.h"
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

extern int errno;
typedef void (*SigHandler)(int);

void sigHandler(int signo)
{
    printf("caught signal: %d\n", signo);
}

void saferead(int fd, void* buff, ssize_t size)
{
    SigHandler handle = signal(SIGINT, &sigHandler);
    int n;
    if (SIG_ERR==handle)
        err_sys("cant catch SIGINT");
    while (0<size) {
        do {
            n = read(fd, buff, size);
        }while ( n<0 && errno==EINTR);
        if (n<0) {
            perror("read error");
            exit(1);
        }
        buff += n;
        size -= (ssize_t)n;
    }
    if (SIG_ERR==signal(SIGINT, handle))
        err_sys("cant restore sighandlder");
}

int main(int argc, char* argv[])
{
    #define LEN 4
    char buff[LEN];
    printf("main pid: %d, sizeof(ssize_t)=%lu, sizeof(int)=%lu\n", getpid(), sizeof(ssize_t), sizeof(int));
    saferead(STDIN_FILENO, buff, LEN-1);
    buff[LEN-1] = '\0';
    printf("read: *%s*\n", buff);
    sleep(10);
    return 0;
}

