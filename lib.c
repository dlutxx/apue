#include "lib.h"

void err_sys(char* s)
{
    perror(s);
    exit(127);
}

