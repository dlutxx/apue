#include "lib.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int cnt = 0;
    while (1) {
        xlog("tick #%d", ++cnt);
        sleep(1);
    }
    return 0;
}

