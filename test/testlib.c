#include "lib.h"
#include <stdio.h>

int i=100;
char* s = "hahaha";
float f = 123.4567;

static void test_pr()
{
    printf("pr something like this:\na num:%d, a string:%s, a float:%4.3f\n", i, s, f);
    pr("a num:%d, a string:%s, a float:%4.3f\n", i, s, f);
}

static void test_xlog()
{
    printf("xlog something like this:\na num:%d, a string:%s, a float:%4.3f\n", i, s, f);
    xlog("a num:%d, a string:%s, a float:%4.3f\n", i, s, f);
}

static void test_err_sys()
{
    printf("quit with the msg:%s\n", s);
    err_sys(s);
}

int main(int argc, char* argv[])
{
    test_pr();
    test_xlog();
    test_err_sys();
    return 0;
}

