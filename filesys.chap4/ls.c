#include "lib.h"
#include <sys/stat.h>

#define pf printf

void ls(char* path);

int main(int argc, char* argv[])
{
    int i;
    for (i=1; i<argc; ++i)
        ls(argv[i]);
    return 0;
}

void ls(char* path)
{
    static struct stat buff;
    if (lstat(path, &buff)<0) {
        perror("lstat error");
        return ;
    }
    pf("%s: ", path);
    if (S_ISREG(buff.st_mode))
        pf("REGULAR");
    else if (S_ISDIR(buff.st_mode))
        pf("DIRECTORY");
    else if (S_ISLNK(buff.st_mode))
        pf("SYMLINK");
    else if (S_ISFIFO(buff.st_mode))
        pf("FIFO");
    else if (S_ISBLK(buff.st_mode))
        pf("BLOCK");
    else if (S_ISCHR(buff.st_mode))
        pf("CHAR");
    else if (S_ISSOCK(buff.st_mode))
        pf("SOCKET");
    else
        pf("*UNKNOW*");

    if (buff.st_mode & S_ISUID)
        pf(" SETUID");
    if (buff.st_mode & S_ISGID)
        pf(" SETGID");
    pf(" ");
    if (S_IRUSR & buff.st_mode) pf("r"); else pf("-");
    if (S_IWUSR & buff.st_mode) pf("w"); else pf("-");
    if (S_IXUSR & buff.st_mode) pf("x"); else pf("-");
    if (S_IRGRP & buff.st_mode) pf("r"); else pf("-");
    if (S_IWGRP & buff.st_mode) pf("w"); else pf("-");
    if (S_IXGRP & buff.st_mode) pf("x"); else pf("-");
    if (S_IROTH & buff.st_mode) pf("r"); else pf("-");
    if (S_IWOTH & buff.st_mode) pf("w"); else pf("-");
    if (S_IXOTH & buff.st_mode) pf("x"); else pf("-");
    pf("\n");
}

