#include "lib.h"
#include <stdarg.h>

#define XLOG_FILE "/var/tmp/xlog.log"
static FILE* fp = NULL;

void err_sys(char* s)
{
    perror(s);
    exit(127);
}

void xlog(char* fmt, ...)
{
    if (NULL == fp && (fp=fopen(XLOG_FILE, "a+")) == NULL)
        exit(120);
    va_list args;
    va_start(args, fmt);
    vfprintf(fp, fmt, args);
    fprintf(fp, "\n");
    va_end(args);
    fflush(fp);
}

void pr(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

