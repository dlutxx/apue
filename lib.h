#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void err_sys(char*);
void xlog(char* fmt, ...);

void pr(char* fmt, ...);
#endif
