#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

#define PAGER "/bin/more"
#define MAXLINE 1024

int main(int argc, char* argv[])
{
    int fds[2];
    FILE *fp=NULL;

    if (argc < 2) {
        printf("Usage %s <filename>\n", argv[0]);
        exit(1);
    }
    if ((fp=fopen(argv[1], "r")) == NULL) {
        perror("fopen error");
        exit(1);
    }

    if (pipe(fds) <0) {
        perror("pipe error");
        exit(1);
    }
    printf("fd0=%d, fd1=%d\n", fds[0], fds[1]);
    
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid>0) {
        close(fds[0]);
        char line[MAXLINE];
        int n=0;
        while(fgets(line, MAXLINE, fp) != NULL) {
            n = strlen(line);
            if(write(fds[1], line, n) != n) {
                perror("write error");
                exit(1);
            }
        }
        if (ferror(fp)) {
            perror("fgets error");
            exit(1);
        }
        fclose(fp);
        close(fds[1]);
        if (waitpid(pid, NULL, 0) < 0) {
            perror("waitpid error");
            exit(1);
        }
        exit(0);
    } else {
        close(fds[1]);
        if (fds[0] != STDIN_FILENO) {
            if (dup2(fds[0], STDIN_FILENO) != STDIN_FILENO) {
                perror("dup2 error");
                exit(1);
            }
        }
        char* pager = NULL;
        char* argv0 = NULL;
        if ((pager = getenv("PAGER")) == NULL)
            pager = PAGER;
        if ((argv0=strrchr(pager, '/')) != NULL) {
            ++argv0;
        } else {
            argv0 = pager;
        }

        if (execl(pager, argv0, (char *)NULL) < 0) {
            perror("execl error");
            exit(1);
        }
    }

    return 0;
}

