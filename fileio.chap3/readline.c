#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


#define BUFLEN 1024


int with_fgets();
int with_readline();

// gcc -Wall read.c -lreadline
int main(int argc, char* argv[])
{
    int (*fns[2])(void) = {&with_fgets, &with_readline};
    return fns[argc%2]();
}


int with_fgets()
{
    char line[BUFLEN];
    printf("say something:");
    if (NULL==fgets(line, BUFLEN, stdin)) {
        perror("read error");
        return 1;
    }
    printf("You said:*%s*\n", line);
    return 0;
}

int with_readline()
{
    char* line = NULL;
    if (NULL!=(line=readline("say something: "))) {
        printf("You said:*%s*\n", line);
        free(line);
        return 0;
    }
    perror("read error");
    return 1;
}
