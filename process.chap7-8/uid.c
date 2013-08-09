#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("uid:%d, euid:%d\n", getuid(), geteuid());
    // chmod a+s a.out
    setuid(1000);
    printf("uid:%d, euid:%d\n", getuid(), geteuid());
    return 0;
}

