#include <stdio.h>
#include <sys/utsname.h>

void pr_uname(FILE* fp)
{
    struct utsname buf;
    if (uname(&buf) == 0) {
        fprintf(fp, "sysname = %s\nnodename = %s\nrelease = %s\nversion = %s\nmachine = %s\n", 
            buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
        #ifdef _GNU_SOURCE
        fprintf(fp, "domainname=%s\n", buf.domainname);
        #endif
    } else
        perror("uname error");
}

int main(int argc, char* argv[])
{
    pr_uname(stdout);
    return 0;
}

