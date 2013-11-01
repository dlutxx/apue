#include "lib.h"
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void sigintHandler(int signo)
{
    pr("caught signal: %d\n", signo);
}

int blocksig(int signo);
void* thr1(void* arg)
{
    pr("thr1 sleeping \n");
    blocksig(SIGUSR1);
    sigset_t sigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, SIGUSR1);
    int err=0, n=0;
    sigwait(&sigs, &n);
    pr("thr1 exiting err=%d, n=%d\n", err, n);
    return NULL;
}
void* thr2(void* arg)
{
    return NULL;
}

int blocksig(int signo)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, signo);
    return pthread_sigmask(SIG_BLOCK, &set, NULL);
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    int i;
    for (i=0; i<5; ++i) {
        pthread_create(&tid, NULL, &thr1, NULL);
    }
    if (SIG_ERR == (signal(SIGUSR1, &sigintHandler))) {
        pr("cant catch SIGINT\n");
        exit(1);
    }
    pr("main thread pid: %d\n", getpid());
    blocksig(SIGUSR1);
    //while (1)
    sleep(10);
    pr("main exiting\n");
    return 0;
}

