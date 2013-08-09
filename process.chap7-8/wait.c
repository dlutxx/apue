#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void prexit(stat)
{
    if (WIFEXITED(stat))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(stat));
    else if (WIFSIGNALED(stat))
        printf("abnormal termination, signal = %d %s\n", WTERMSIG(stat),
    #ifdef WCOREDUMP
    WCOREDUMP(stat) ? "( core file generated )" : ""
    #else
    ""
    #endif
    );
    else if (WIFSTOPPED(stat))
        printf("child stopped, signal = %d\n", WSTOPSIG(stat));
    else if (WIFCONTINUED(stat))
        printf("child stopped, signal = %d\n", WSTOPSIG(stat));
}

int main(int argc, char* argv[])
{
    pid_t pid;
    int stat;

    if ((pid=fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (0 == pid)
        exit(7);
    if (wait(&stat) != pid) {
        perror("fork error");
        exit(1);
    }
    prexit(stat);

    if ((pid=fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (0 == pid)
        abort();
    if (wait(&stat) != pid) {
        perror("wait error");
        exit(1);
    }
    prexit(stat);

    if ((pid=fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (0 == pid)
        stat = 1/(1-1);
    if (wait(&stat) != pid) {
        perror("wait error");
        exit(1);
    }
    prexit(stat);

    if ((pid=fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (0 == pid) {
       printf("child pid is %d\n\n", getpid());
       // kill -STOP pid
       // kill -CONT pid
       int n=0;
       while (n++<30) {
           printf("child ticking: %d\n", n);
           sleep(1);
       }
       exit(0);
    }
    if (waitpid(pid, &stat, WCONTINUED|WUNTRACED) != pid) {
        perror("wait error");
        exit(1);
    }
    prexit(stat);
    printf("hahah\n");
    if (waitpid(pid, &stat, WCONTINUED|WUNTRACED) != pid) {
        perror("wait error");
        exit(1);
    }
    prexit(stat);

    return 0;
}


