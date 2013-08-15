#include "lib.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char* file = "junk.txt";
    FILE* fp = fopen(file, "a+");
    setlinebuf(fp);
    int cnt = 0;
    while (1) {
        fprintf(fp, "tick #%d\n", ++cnt);
        fflush(fp);
        sleep(1);
    }
    return 0;
}

