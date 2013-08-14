#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

static void sig_handler(int signo)
{
    printf("SIG_QUIT caught, %d\n", signo);
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        fprintf(stderr, "cannt reset SIGQUIT\n");
}

int main(int argc, char* argv[])
{
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, &sig_handler) == SIG_ERR) {
        fprintf(stderr, "cannt catch SIGQUIT\n");
        exit(1);
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        fprintf(stderr, "sig block err\n");
        exit(1);
    }

    sleep(5);

    if (sigpending(&pendmask) < 0) {
        fprintf(stderr, "sigpending error\n");
        exit(1);
    }
    if (sigismember(&pendmask, SIGQUIT)) {
        printf("SIGQUIT pending\n");
    }

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "error setmask\n");
        exit(1);
    }

    printf("SIG_QUIT unblocked\n");
    sleep(5);
    return 0;
}

