#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MAXRETRY 4
#define BUFLEN 1024

int retry_connect(int af, int type, int proto, struct sockaddr* addr, socklen_t slen);
void request(int sfd);

int main(int argc, char* argv[])
{
    if (argc!=3) {
        fprintf(stderr, "Usage: %s host service\n", argv[0]);
        exit(1);
    }

    setbuf(stderr, NULL);
    setbuf(stdout, NULL);
    struct addrinfo hint, *ailist, *aip;
    int err, sfd;
    memset(&hint, 0, sizeof(hint));

    if ((err=getaddrinfo(argv[1], argv[2], &hint, &ailist))!=0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err));
        exit(1);
    }
    for (aip=ailist; aip!=NULL; aip=aip->ai_next) {
        if ((sfd=retry_connect(aip->ai_family, SOCK_STREAM, 0, (struct sockaddr*)aip->ai_addr, aip->ai_addrlen))>=0) {
            request(sfd);
            fprintf(stderr, "request done\n");
            exit(0);
        }
    }
    freeaddrinfo(ailist);
    fprintf(stderr, "cant connect\n");
    return 1;
}

void request(int sfd)
{
    char buff[BUFLEN];
    int err;
    size_t n, cnt=0;
    while ((n=fread(buff, 1, BUFLEN, stdin))>0) {
        send(sfd, buff, n, 0);
    }
    fprintf(stderr, "sending request\n");
    while ((n=recv(sfd, buff, BUFLEN, 0))>0) {
        fwrite(buff, 1, n, stdout);
        fprintf(stderr, "recved %zu bytes\n", n);
        cnt += n;
        if (n<BUFLEN) break;
    }
    fprintf(stderr, "total bytes received: %zu\n", cnt);
    if (n<0) perror("recv error");
    fclose(stdout);
    close(sfd);
}

int retry_connect(int af, int type, int proto, struct sockaddr* addr, socklen_t slen)
{
    int sfd, retry, err;
    if ((sfd=socket(af, type, proto))<0) {
        perror("cant init socket");
        exit(1);
    }
    for (retry=0; retry<MAXRETRY; ++retry) {
        if (0!=connect(sfd, addr, slen)) {
            err = errno;
            close(sfd);
            errno = err;
            sleep(1<<retry);
        } else
            return sfd;
    }
    return -1;
}

