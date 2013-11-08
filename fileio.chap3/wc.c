#include "lib.h"
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 64

typedef struct Node {
    char* word;
    unsigned int cnt;
} Node;

typedef struct Dict {
    unsigned int len;
    unsigned int* slots;
} Dict;

int main(int argc, char* argv[])
{

}


