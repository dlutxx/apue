#include <stdio.h>

#define len 100
static char buf[len];

int main(int argc, char* argv[])
{
    int n=0, idx=0;
    printf("say something: ");
    while (scanf("%d", &n) != EOF) {
        if (n > 31 && n < 127) {
            if (idx>=len-1)
                break;
            buf[idx++] = (char)n;
        }
    }
    printf("you entered: %s\n", buf);
    return 0;
}

