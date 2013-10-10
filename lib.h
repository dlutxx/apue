/**
 * useage: gcc -Wall -I. threads.chap11/hello.c lib.o -lpthread
 */
#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

void err_sys(char*);
void xlog(char* fmt, ...);

void pr(char* fmt, ...);

int lockfile(int fd);

#endif
