#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <string.h>


typedef void (*Task)(void* arg);

static pid_t *childPids;
static int childNum;

static void sigHandler(int signo)
{
    printf("proc %d caught signo %d\n", getpid(), signo);
    int i;
    for (i=0; i<childNum; ++i) {
        if (childPids[i]>0) {
            printf("Proc %d sending signo %d to proc %d\n", getpid(), SIGTERM, childPids[i]); 
            kill(childPids[i], SIGTERM);
            childPids[i] = 0;
        }
    }
    exit(1);
}

static void handleSIGCHLD(int signo)
{
    int noMoreChild = 1, i;
    pid_t pid;
    printf("proc %d caught SIGCHLD %d\n", getpid(), signo);
    // *only* one instance of SIGCHLD is queued
    while ((pid=waitpid((pid_t)-1, NULL, WNOHANG))>0) {
        for (i=0; i<childNum; ++i)
            if (childPids[i]==pid) {
                childPids[i] = 0;
                break;
            }
    }
    for (i=0; i<childNum; ++i)
        if (childPids[i]>0) {
            noMoreChild = 0;
            break;
        }
    if (noMoreChild)
        exit(0);
}

static void setupSignalHandler()
{
    if (signal(SIGTERM, sigHandler) == SIG_ERR) {
        perror("can not catch SIGTERM");
        exit(1);
    }
    assert(SIG_ERR != signal(SIGCHLD, handleSIGCHLD));
}

static pid_t spawn(Task t, void* arg)
{
    pid_t pid;
    pid = fork();
    if (pid<0) {
        perror("fork error");
        exit(1);
    } else if (pid==0) {
        t(arg);
        exit(0);
    }
    return pid;
}

void daemonize(Task task, void* arg, int workers)
{
    pid_t *pids;
    int c;
    setupSignalHandler();
    pids = calloc(sizeof(pid_t), workers);
    assert(pids != NULL);
    printf("Daemon pid %d\n", getpid());
    for (c=0; c<workers; ++c) {
        pids[c] = spawn(task, arg);
    }
    childPids = pids;
    childNum = c;
    while (1) {
        printf("main pausing...\n");
        pause();
        /* int pid = wait(NULL);
        if (pid<0) break;
        printf("waited for %d\n", pid);
        */
        // any children still alive?
    }
    printf("main exiting...\n");
}

void tick(void* arg)
{
    int i, n = (int)arg;
    for (i=0; i<n; ++i) {
        printf("proc %d arg %d\n", getpid(), i);
        sleep(1);
    }
}

int main(int argc, char* argv[])
{
    int n = 4;
    if (argc>1) {
        n = strtol(argv[1], NULL, 10);
    }
    daemonize(&tick, (void*)2, n);
    return 0;
}
