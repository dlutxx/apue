#include "lib.h"
#include <pthread.h>
#include <time.h>

typedef struct {
    int val;
    pthread_mutex_t lock;
} Entry;
Entry ent = {0, PTHREAD_MUTEX_INITIALIZER};
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int entry_get(Entry* ent);
void entry_set(Entry* ent, int val);
void* producer(void* arg);
void* consumer(void* arg);

int main(int argc, char* argv[])
{
    pthread_t p1, c1, c2;
    pthread_create(&p1, NULL, &producer, NULL);
    pthread_create(&c1, NULL, &consumer, NULL);
    pthread_create(&c2, NULL, &consumer, NULL);

    pthread_join(p1, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);
    return 0;
}

int entry_get(Entry* ent)
{
    return 0;
}

void entry_set(Entry*ent, int val)
{
}
void* producer(void* arg)
{
    int cnt = 0;
    while (++cnt<101) {
        pr("producer waiting for lock\n");
        pthread_mutex_lock(&ent.lock);
        //pthread_cond_wait(&cond, &ent.lock);
        ++ent.val;
        pthread_mutex_unlock(&ent.lock);
        pthread_cond_signal(&cond);
    }
    return NULL;
}
void* consumer(void* arg)
{
    int v;
    while (1) {
        pr("consumer waiting for lock\n");
        pthread_mutex_lock(&ent.lock);
        while (ent.val<1)
            pthread_cond_wait(&cond, &ent.lock);
        v = --ent.val;
        pthread_mutex_unlock(&ent.lock);
        printf("%d\n", ent.val);
    }
}

