#include "lib.h"
#include <pthread.h>
#include <time.h>

void cleanup(void *arg)
{
    printf("cleanup: %s\n", (char*)arg);
}

void tinfo(const char* title)
{
    printf("%s pid:%lu tid:%lu\n", title, getpid(), pthread_self());
}

void * tick(void *args)
{
    printf("thread start\n");
    pthread_cleanup_push(&cleanup, "handler one");
    pthread_cleanup_push(&cleanup, "handler two");
    sleep(1);
    tinfo("thread");

    char* val = "hello";
    pthread_exit(val);

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit(val);
    // return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    int err;
    err = pthread_create(&tid, NULL, &tick, NULL);
    if (err!=0)
        err_sys("failed to create a thread");

    void* ret;
    err = pthread_join(tid, &ret);
    if (err)
        err_sys("join error");
    printf("thread ret: %s\n", (char*)ret);
    tinfo("main");

    return 0;
}

