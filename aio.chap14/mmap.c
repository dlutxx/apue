#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("_SC_PAGE_SIZE is  %ld.\n", sysconf(_SC_PAGE_SIZE));
    return 0;
}

