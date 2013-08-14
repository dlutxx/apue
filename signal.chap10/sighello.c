#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef void (*sighand)(int);

static void handle(int sig)
{
    if (SIGUSR1 == sig) {
        printf("USR1 received\n");
        sleep(20);
    } else if (SIGUSR2 ==sig)
        printf("USR2 received\n");
    else 
        exit(0);
}

int main(int argc, char* argv[])
{
    printf("pid=%d\n", getpid());
    if (SIG_ERR == signal(SIGUSR1, &handle)){
        perror("signal error");
        exit(1);
    }

    if (SIG_ERR == signal(SIGUSR2, &handle)){
        perror("signal error");
        exit(2);
    }

    for(; ;)
        pause();
}


