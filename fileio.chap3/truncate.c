#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define KB 1024
#define MB 1024*KB
#define GB 1024*MB

int main(int argc, char* argv[])
{
    long off = strtol(argv[2], NULL, 10);
    char unit = toupper(argv[2][strlen(argv[2])-1]);
    switch(unit)
    {
        case 'K': off *= KB; break;
        case 'M': off *= MB; break;
        case 'G': off *= GB; break;
        default: unit=' ';
    }
    printf("truncating %s to %li\n", argv[1], off);
    if (truncate(argv[1], off)<0)
    {
        perror("truncate error");
        return 1;
    }
    return 0;
}

