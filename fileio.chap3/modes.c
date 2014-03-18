#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// sudo chmod a+s a.out
// ./a.out
int main(int argc, char* argv[])
{
    uid_t uid, euid;
    gid_t gid, egid;
    uid = getuid();
    euid = geteuid();
    gid = getgid();
    egid = getegid();
    printf(" uid = %lu,  gid = %lu \n"
           "euid = %lu, egid = %lu\n",
           uid, gid, euid, egid);
    return 0;
}
