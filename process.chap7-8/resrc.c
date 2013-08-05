#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("%ld\n", sysconf(_SC_CHILD_MAX));
    struct rlimit rl;
    getrlimit(RLIMIT_NPROC, &rl);
    printf("%ld, %ld\n", rl.rlim_cur, rl.rlim_max);
    return 0;
}

