#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


#define SHMKEY 1234
#define SHMLEN 128

int create_shm(int key)
{
    int shmid = shmget(SHMKEY, SHMLEN, IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    return shmid;
}

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
    } else if (pid > 0) {
    } else {
        perror("fork");
        return 1;
    }
}
