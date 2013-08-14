#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "lib.h"

static int slp(int n)
{
    return sleep(n);
}

static void sighandler(int sig)
{
    psignal(sig, "sig caught");
}

static void pse()
{
    pause();
}

int main(int argc, char* argv[])
{
    char* act="sleep";
    printf("pid=%d\n", getpid());
    if (argc>1 && argv[1][0]=='p') {
        act = "pause";
        if (signal(SIGUSR1, &sighandler) == SIG_ERR)
            err_sys("cant catch SIGUSR1");
        pse();
    } else
        slp(10);
    printf("after %s\n", act);
    return 0;
}

