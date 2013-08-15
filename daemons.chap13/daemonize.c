#include "lib.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int daemonize(char* cmd);

int main(int argc, char* argv[])
{
    if (argc>1) {
        daemonize(argv[1]);
    }

    return 0;
}

int daemonize(char* cmd)
{
    int i, fd0, fd1, fd2;
    pid_t pid=0;
    struct rlimit rl;
    struct sigaction sa;

    umask(0);

    if ((pid=fork()) < 0)
        err_sys("fork err");
    else if (pid > 0)
        exit(0);

    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_sys("cant catch SIGHUP");
    xlog("SIGHUP set");
    
    if ((pid=fork()) < 0) {
        err_sys("cant fork twice");
        xlog("cant fork twice");
        xlog(strerror(errno));
    }else if (pid > 0)
        exit(0);

    if (chdir("/") < 0)
        err_sys("cant chdir to /");
    xlog("chdir to /");

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_sys("cant get getrlimit ");
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i=0; i<rl.rlim_max; ++i)
        close(i);
    xlog("closed all fd");

    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(fd0);
    fd2 = dup(fd0);
    xlog("dup 3 fd");

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected fds: %d, %d, %d", fd0, fd1, fd2);
        exit(1);
    }
    if (execl(cmd, cmd, (char*)0) < 0) {
        exit(1);
    }
    return 0;
}

