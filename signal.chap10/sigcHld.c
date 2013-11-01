#include <unistd.h>
#include "lib.h"
#include <sys/wait.h>
#include <signal.h>

void cldHandler(int signo)
{
    pr("%d caught SIGCLD: %d\n", signo, getpid());
}

void cHldHandler(int signo)
{
    pr("%d caught SIGCHLD: %d\n", signo, getpid());
}
void pinfo(char* msg)
{
    pr("%s pid: %d\n", msg, getpid());
}

int main(int argc, char* argv[])
{
    pinfo("main");
    if (SIG_ERR==signal(SIGCLD, cldHandler))
        err_sys("cant catch SIGCLD");
    if (signal(SIGCHLD, cHldHandler) == SIG_ERR)
        err_sys("cant catch SIGCHLD");
    pid_t pid;
    if (0==(pid=fork())) {
        pinfo("child sleeping");
        sleep(1);
        exit(0);
    } else if (pid<0) {
        err_sys("fork error");
    }
    int stat;
    printf("wait for %d\n", wait(&stat));
    do {
        pause();
    } while (1);

    return 0;
}

