//uio readv, writev
#include <sys/uio.h>
#include <stdio.h> // can not mix uio and stdio
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h> // for STDOUT_FILENO


// merging all arguments
int main(int argc, char* argv[])
{
    if (argc < 2)
        return 0;

    struct iovec *iovs = malloc(argc);
    assert(iovs != NULL);
    int i;
    size_t cnt=1;

    for (i=0; i<argc-1; ++i) {
        iovs[i].iov_base = argv[i+1];
        iovs[i].iov_len = strlen(argv[i+1]);
        cnt += iovs[i].iov_len;
    }
    iovs[i].iov_base = "\n";
    iovs[i].iov_len = 1;
    assert(cnt == writev(STDOUT_FILENO, iovs, i+1));
    return 0;
}
