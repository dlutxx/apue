#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <signal.h>

#define BUFSZ 512

char servAddr[128];

void cleanup() {
    printf("unlinking %s\n", servAddr);
    unlink(servAddr);
}

int main(int argc, char* argv[])
{
    int sfd, slen;
    struct sockaddr_un addr;
    if (argc<2) {
        fprintf(stderr, "Where to bind?\n");
        exit(1);
    }

    if ((sfd=socket(AF_UNIX, SOCK_STREAM, 0))<0) {
        perror("socket");
        exit(1);
    }
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, argv[1]);
    strcpy(servAddr, argv[1]);
    atexit(&cleanup);
    printf("binding to %s\n", argv[1]);
    slen = offsetof(struct sockaddr_un, sun_path)+strlen(addr.sun_path);
    if (bind(sfd, (struct sockaddr*)&addr, slen)<0) {
        perror("bind");
        exit(1);
    }
    printf("binded to %s\n", argv[1]);
    if (argc>2)
        if (unlink(argv[1])<0) {
            perror("unlink sock path");
            exit(1);
        }

    if (listen(sfd, 1024)<0) {
        perror("listen");
        exit(1);
    }
    char buff[BUFSZ+1];
    buff[BUFSZ] = '\0';
    int cfd, err;
    while (1) {
        if ((cfd=accept(sfd, NULL, NULL))<0) {
            perror("accept");
            exit(1);
        }
        printf("new conn %d\n", cfd);
        while ((err=read(cfd, buff, BUFSZ))>0) {
            write(STDOUT_FILENO, buff, err);
        }
        printf("%d disconnected \n", cfd);
        close(cfd);
    }
    close(sfd);
    return 0;
}

