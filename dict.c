#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

typedef struct Dict Dict;
typedef struct dictEntry dictEntry;
struct dictEntry {
    char* key;
    long val;
    dictEntry* next;
};
typedef struct Dict {
    dictEntry * slots;
    uint64_t len;
} Dict;

int  dict_init(Dict* dict, int len);
int  dict_set(Dict* dict, char* key, long val);
long dict_get(Dict* dict, char* key);
int  dict_unset(Dict* dict, char* key);
uint64_t dict_hash(Dict* dict, char* key);
int  dict_contains(Dict* dict, char* key);
void dict_destroy(Dict* dict);

int main(int argc, char* argv[])
{
}

/**
 * return 0 on success, -1 otherwise
 */
int dict_init(Dict* dict, uint64_t len)
{
    assert(dict!=NULL, "null dict");
    assert(len > 0, "illegal dict length");
    dict->len = 0;
    dict->slots = calloc(sizeof(dictEntry), len);
    if (NULL==dict->slots) {
        return -1;
    }
    dict->len = len;
    return 0;
}
int dict_set(Dict* dict, char* key, long val)
{
    uint64_t hash = dict_hash(dict, key);
    dictEntry* ent = dict->slots[hash], *nent=ent->next;
    char found = 0;
    while (nent!=NULL) {
        int cmp = strcmp(key, nent->key);
        if (0==cmp) {
            ent = nent;
            found = 1;
            break;
        } else if (0<cmp) {
            ent = nent;
            nent = ent->next;
        } else {
            break;
        }
    }
    if (found) {
        ent->val = val;
        return 0;
    }
    dictEntry* newEntry = calloc(sizeof(dictEntry), 1);
    if (NULL==newEntry)
        return -1;
    newEntry->next = nent;
    ent->next = newEntry;
    return 0;
}
uint64_t dict_hash(Dict* dict, char* key)
{
    uint64_t v=0;
    while (*key!='\0') {
        ++key;
        v = v*29 + *key;
    }
    return v>0 ? v%dict->len : 0;
}

void dict_destroy(Dict* dict)
{
    if (dict->len < 1)
        return;
    uint64_t i;
    dictEntry* ent, fr;
    for (i=0; i<dict->len; ++i) {
        ent = dict->slots[i]->next;
        while (ent != NULL) {
            fr = ent;
            ent = ent->next;
            free(fr);
        }
    }
    free(dict->slots);
    dict->len = 0;
}


