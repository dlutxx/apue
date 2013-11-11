#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

void pr_addrinfo(struct addrinfo *ai);

int main(int argc, char* argv[])
{
    if (argc!=3) {
        fprintf(stderr, "Usage: %s host service\n", argv[0]);
        exit(1);
    }

    struct addrinfo hint, *ailist, *aip;
    int err;
    memset(&hint, 0, sizeof(hint));

    if ((err=getaddrinfo(argv[1], argv[2], &hint, &ailist))!=0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err));
        exit(1);
    }
    for (aip=ailist; aip!=NULL; aip=aip->ai_next) {
        pr_addrinfo(aip);
    }
    freeaddrinfo(ailist);
    return 0;
}

void pr_addrinfo(struct addrinfo *ai)
{
    printf("Family: ");
    switch (ai->ai_family) {
    case AF_INET: printf("AF_INET"); break;
    case AF_INET6: printf("AF_INET6"); break;
    case AF_UNIX: printf("AF_UNIX"); break;
    default: printf("*other*"); break;
    }
    printf(", Type: ");
    switch(ai->ai_socktype) {
    case SOCK_STREAM: printf("STREAM"); break;
    case SOCK_DGRAM: printf("DGRAM"); break;
    default: printf("*other*"); break;
    }
    printf(", Flags: ");
    if (ai->ai_flags == 0)
        printf(" 0");
    else {
        if (ai->ai_flags & AI_PASSIVE) printf(" PASSIVE");
        if (ai->ai_flags & AI_CANONNAME) printf(" CANON");
        if (ai->ai_flags & AI_NUMERICHOST) printf(" numhost");
        if (ai->ai_flags & AI_NUMERICSERV) printf(" numserv");
        if (ai->ai_flags & AI_ALL) printf(" ALL");
    }
    printf(", Protocol: ");
    switch(ai->ai_protocol) {
    case 0: printf(" default"); break;
    case IPPROTO_TCP: printf(" TCP"); break;
    case IPPROTO_UDP: printf(" UDP"); break;
    case IPPROTO_RAW: printf(" RAW"); break;
    default: printf(" *unknown-%d*", ai->ai_protocol); break;
    }
    printf(", Host: %s", ai->ai_canonname?ai->ai_canonname: "-");
    char* addr;
    char abuff[INET6_ADDRSTRLEN];
    if (AF_INET == ai->ai_family) {
        struct sockaddr_in *sin;
        sin = (struct sockaddr_in*)ai->ai_addr;
        addr = inet_ntop(AF_INET, &sin->sin_addr, abuff, INET_ADDRSTRLEN);
        printf(", IPv4 Address: %s", addr?addr:"*unkown*");
        printf(", Port: %d", ntohs(sin->sin_port));
    } else if (AF_INET6 == ai->ai_family) {
        struct sockaddr_in6 * sin6;
        sin6 = (struct sockaddr_in6*)ai->ai_addr;
        addr = inet_ntop(AF_INET6, &sin6->sin6_addr, abuff, INET6_ADDRSTRLEN);
        printf(", IPv6 Address: %s", addr? addr : "*unknown*");
        printf(", Port: %d", ntohs(sin6->sin6_port));
    }
    printf("\n");
}

