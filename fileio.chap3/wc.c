#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

#ifdef NDEBUG
    #define debug(...) fprintf(stderr, __VA_ARGS__)
#else
    #define debug(...) ((void)0)
#endif

#define MAXWORD  64
typedef struct Node {
    char* word;
    uint32_t cnt;
    struct Node* next;
} Node;
typedef Node* List;
int add_word(List*, char*);
void iter_list(List*, void (*fn)(char*, uint32_t));
void free_list(List*);
int read_word(FILE*, char*, int);
void pr_word(char*, uint32_t);

int main(int argc, char* argv[])
{
    List list = NULL;
    char word[MAXWORD];
    FILE * fp;
    if (argc>1) {
        fp = fopen(argv[1], "rb");
        if (NULL==fp) {
            perror("cant read file");
            exit(1);
        }
    } else {
        fp = stdin;
    }
    int n=0;
    while ((n=read_word(fp, word, MAXWORD))>-1) {
        if (n>0) {
            debug("read word= *%s*\n", word);
            if (add_word(&list, word)<0) {
                perror("cant add word");
                break;
            }
        }
    }
    debug("to iterate list\n");
    iter_list(&list, &pr_word);
    debug("to free list\n");
    free_list(&list);
    return 0;
}

Node* create_node(char* word)
{
    int len = strlen(word);
    Node* n = calloc(sizeof(Node), 1);
    if (NULL==n) return NULL;
    n->word = calloc(sizeof(char), len+1);
    if (NULL==n->word) {
        free(n);
        return NULL;
    }
    n->cnt = 1;
    n->next = NULL;
    memcpy(n->word, word, len);
    n->word[len] = '\0';
    return n;
}
int add_word(List* list, char* word)
{
    int len=strlen(word);
    if (len==0) return 0;
    Node* node = *list, *n2;
    /// /*
    while (NULL!=node) {
        int c = strcmp(word, node->word);
        debug("strcmp *%s* with *%s*, c=%d\n", word, node->word, c);
        if (0==c) {
            ++node->cnt;
            return 0;
        } else if (0<c) {
            if (NULL==node->next) {
                debug("'%s' %p  has no next\n", node->word, node->next);
                n2 = create_node(word);
                if (NULL==n2) return -1;
                node->next = n2;
                debug("'%s' next = %p\n", node->word, node->next);
                return 0;
            } else {
                c = strcmp(word, node->next->word);
                if (0>c) {
                    n2 = create_node(word);
                    if (NULL==n2) return -1;
                    n2->next = node->next;
                    node->next = n2;
                    return 0;
                }
                node = node->next;
            }
        } else {
            // head of list
            n2 = create_node(word);
            if (NULL==n2) return -1;
            n2->next = node;
            *list = n2;
            return 0;
        }
    } // */
    node = create_node(word);
    if (NULL==node) return -1;
    *list = node;
    return 0;
}
void iter_list(List* list, void (*fn)(char*, uint32_t))
{
    Node* n = *list;
    while (NULL!=n) {
        fn(n->word, n->cnt);
        n = n->next;
    }
}
void free_list(List* list)
{
    Node* n;
    while (NULL!=(n=*list)) {
        *list = n->next;
        free(n->word);
        free(n);
    }
}
int read_word(FILE* fp, char* buff, int size)
{
    int n, c;
    clearerr(fp);
    for (n=0; n<size-1; ++n) {
        c = fgetc(fp);
        if (!isalpha(c))
            break;
        buff[n] = c;
    }
    if (ferror(fp) || feof(fp))
        return -1;
    buff[n] = '\0';
    return n;
}
void pr_word(char* word, uint32_t cnt) 
{
    printf("%10s: %u\n", word, cnt);
}


