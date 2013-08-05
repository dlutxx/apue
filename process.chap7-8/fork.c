#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef VFORK
    #define fm vfork
#else
    #define fm fork
#endif

int glob = 6;
int main(int argc, char* argv[])
{
    int var;
    pid_t pid;
    var = 88;
    printf("before forking\n");
    if ((pid=fm()) < 0) {
        perror("forking err");
        exit(1);
    } else if (pid == 0) {
        ++glob;
        ++var;
        _exit(0);
    }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
    return 0;
}


