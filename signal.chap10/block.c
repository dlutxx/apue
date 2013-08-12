#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "lib.h"

static int sigCount = 0;
static void handle(int sig)
{
    printf("signal caught:%d, sigCount=%d\n", sig, ++sigCount);
    sleep(5);
}

int main(int argc, char* argv[])
{
    if (signal(SIGQUIT, &handle) == SIG_ERR)
        err_sys("cant capture SIGQUIT");
    printf("pid=%d\n", getpid());
    for(;;)
        pause();
    return 0;
}

