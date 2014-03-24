#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int fast_copy(char* from, char* to)
{
    int in=-1, out=-1;
    struct stat buf;
    in = open(from, O_RDONLY);
    if (in < 0) {
        perror(from);
        goto error;
    }
    if (0 > fstat(in, &buf)) {
        perror("fstat");
        goto error;
    }
    out = open(to, O_WRONLY | O_CREAT | O_EXCL, buf.st_mode);
    if (out < 0) {
        perror(to);
        goto error;
    }
    if (0 > sendfile(out, in, NULL, buf.st_size)) {
        perror("sendfile");
        goto error;
    }
    return 0;
    error:
    if (in > -1) close(in);
    if (out > -1) close(out);
    return -1;
}

// use sendfile to copy files
int main(int argc, char* argv[])
{
    if (argc<3) {
        printf("%s from to\n", argv[0]);
        return 1;
    }
    return -fast_copy(argv[1], argv[2]);
}

