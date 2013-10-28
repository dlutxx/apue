#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 10000
#define MAX_INPUT 20000000
#define min(a, b) ((a)>(b) ? (b) : (a))
#define max(a, b) ((a)<(b) ? (b) : (a))
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef struct CircularBuffer {
    char** arr;
    unsigned int capacity;
    unsigned int head;
    unsigned int size;
} CircularBuffer;

int buffer_init(CircularBuffer* buff, int size)
{
    assert(size>0 && size<MAX_BUFFER_SIZE);
    buff->arr = calloc(sizeof(char*), size);
    if (NULL==buff->arr)
        return -1;
    buff->capacity = size;
    buff->head = 0;
    buff->size = 0;
    while (--size>=0) {
        buff->arr[size] = calloc(sizeof(char), 1024);
    }
    return 0;
}

int buffer_set(CircularBuffer*buff, unsigned int pos, char* str)
{
    assert(pos>=0 && pos<buff->capacity);
    int len = strlen(str);
    if (NULL == realloc(buff->arr[pos], len+1))
        return -1;

    memcpy(buff->arr[pos], str, len);
    buff->arr[pos][len+1] = '\0';
    return 0;
}

int buffer_append(CircularBuffer* buff, char* str)
{
    if (0>buffer_set(buff, buff->head, str))
        return -1;
    ++buff->head;
    buff->size = min(buff->size+1, buff->capacity);
    if (buff->head >= buff->capacity)
        buff->head = 0;
    return 0;
}

int buffer_remove(CircularBuffer* buff, unsigned int len)
{
    if (1>len)
        return 0;
    len = min(len, buff->size);
    buff->size -= len;
    if (len <= buff->head) {
        buff->head -= len;
    } else {
        buff->head += buff->capacity - len;
    }
    return 0;
}

int buffer_list(CircularBuffer* buff)
{
    int pos=0, s = buff->size;
    if (buff->size <= buff->head) {
        pos = buff->head - buff->size;
    } else {
        pos = buff->capacity + buff->head - buff->size;
    }
    while (s>0) {
        if (pos > buff->capacity)
            pos = 0;
        printf("%s\n", buff->arr[pos]);
        --s;
        ++pos;
    }
    return 0;
}

int buffer_free(CircularBuffer* buff)
{
    unsigned int i;
    for (i=0; i<buff->size; ++i)
        free(buff->arr[i]);
    if (NULL!=buff->arr)
        free(buff->arr);
    return 0;
}

int main(int argc, char* argv[])
{
    CircularBuffer buff;
    char* cs = malloc(1024);
    size_t size = 0;
    getline(&cs, &size, stdin);
    buffer_init(&buff, strtol(cs, NULL, 10));
    while (1) {
        size = 1024;
        getline(&cs, &size, stdin);
        //printf("You entered:%s*\n", cs);
        if (size<1 && cs[0]=='q')
            break;
        char cmd = toupper(cs[0]);
        if ('L'==cmd) {
            buffer_list(&buff);
        } else if ('Q'==cmd){
            break;
        } else {
            long op = strtol(cs+2, NULL, 10);
            if ('A'==cmd) {
                while (op>0) {
                    size = 1024;
                    getline(&cs, &size, stdin);
                    int l = strlen(cs);
                    if ('\n'==cs[l-1])
                        cs[l-1] = 0;
                    buffer_append(&buff, cs);
                    --op;
                }
            } else if ('R'==cmd) {
                buffer_remove(&buff, op);
            } else {
                fprintf(stderr, "unknow command: %c\n", cmd);
                buffer_free(&buff);
                exit(1);
            }
        }
    }
    return 0;
}
