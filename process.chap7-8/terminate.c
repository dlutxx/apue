#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void hook()
{
    printf("in hook\n");
}

int main(int argc, char* argv[])
{
    atexit(&hook);
    printf("exiting out of main\n");
    // _Exit or _exit will not invoke hook, only exit will
    abort();
    // _exit(0);
    return 0;
}

