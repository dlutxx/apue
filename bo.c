/**
 * ex: gcc -Wall -I. bo.c lib.o && ./a.out
 */
#include <lib.h>

int main(int argc, char* argv[])
{
    int i = 0x04030201;
    char* p= (char*)(&i);

    pr("i=%0X, p[0]=%d, p[3]=%d\n", i, p[0], p[3]);
    return 0;
}

