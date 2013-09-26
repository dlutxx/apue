#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* forward declaration
 * just like function declaration
 */
typedef struct Node Node;
struct Node {
    int val;
    Node * next;
};

typedef struct List List;
struct List {
    int length;
    Node* head;
};

Node* node_new(int val)
{
    Node * n = calloc(1, sizeof(Node));
    assert( n!=NULL );
    n->val = val;
    n->next = NULL;
    return n;
}

List* list_init(List* ls)
{
    ls->head = NULL;
    ls->length = 0;
    return ls;
}

void list_add(List *ls, int val)
{
    Node* n = node_new(val);
    ++ls->length;
    if (NULL == ls->head) {
        ls->head = n;
        return ;
    }

    Node* tmp = ls->head;
    while (NULL!=tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = n;
}

void list_print(List* ls)
{
    Node* n = ls->head;
    while (n!=NULL) {
        printf("%d ", n->val);
        n = n->next;
    }
    printf("\n");
}

void list_reverse(List* ls)
{
    if (NULL==ls->head || NULL==ls->head->next)
        return;
    Node* n1=ls->head->next, *n2=NULL, *h=NULL;;
    while (n1 != NULL) {
        ls->head->next = h;
        h = ls->head;

        n2 = n1->next;
        n1->next = ls->head;
        ls->head = n1;
        n1 = n2;
    }
}

int main(int argc, char* argv[])
{
    List ls;
    list_init(&ls);
    list_add(&ls, 0);
    list_add(&ls, 1);
    list_add(&ls, 2);
    list_add(&ls, 3);
    list_add(&ls, 4);
    list_add(&ls, 5);
    list_add(&ls, 6);
    list_add(&ls, 7);

    list_print(&ls);

    list_reverse(&ls);

    list_print(&ls);

    return 0;
}

