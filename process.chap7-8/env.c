#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    extern char** environ;
    char** ptr=environ;
    while (*ptr != NULL) {
        printf("%s\n", *ptr);
        ++ptr;
    }
    return 0;
}

