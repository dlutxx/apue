#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("pgid=%u, pid=%u\n", getpgrp(), getpid());
    pid_t pid;

    if ((pid=fork()) < 0) {
        perror("fork error");
        exit(10);
    } else if (pid == 0) {
        printf("child pgid=%u, pid=%u\n", getpgrp(), getpid());
        if (setpgid(0, getppid()) < 0) {
        // if (setpgid(0, 10+getpid()) < 0) {
            perror("setpid error");
            exit(10);
        }
        printf("child pgid=%u, pid=%u\n", getpgrp(), getpid());
        if (setsid() < 0) {
            perror("child setsid error");
            exit(10);
        }
        printf("child after setsid sid=%u, pgid=%u, pid=%u\n", getsid(0), getpgrp(), getpid());
    } else {
        printf("parent pgid=%u, pid=%u\n", getpgrp(), getpid());
        wait(NULL);
        if (setsid() < 0) {
            perror("setsid error");
            exit(10);
        }
        printf("parent after setsid, pgid=%u, pid=%u\n", getpgrp(), getpid());
    }
    return 0;
}

