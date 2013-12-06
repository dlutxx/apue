#include <stdio.h>


#define BUFSIZE 1024
char buff[BUFSIZE];

int cat(FILE *fin, FILE *fout)
{
    int nb;
    while ((nb=fread(buff, sizeof(char), BUFSIZE, fin))>0) {
        buff[nb] = '\0';
        fwrite(buff, sizeof(char), nb, fout);
    }
    return ferror(fin) ? 1 : 0;
}

int main(int argc, char* argv[])
{
    if (argc==1) {
        cat(stdin, stdout);
    } else {
        FILE * fp;
        int i;
        for (i=1; i < argc; ++i) {
            printf("reding %s now.\n", argv[i]);
            fp = fopen(argv[i], "rb");
            if (NULL==fp) {
                perror("Cant't open file");
                continue;
            }
            cat(fp, stdout);
            fclose(fp);
        }
    }
    return 0;
}
