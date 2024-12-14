#include "list.h"
#include <stdlib.h>

void *get_hole(List *l, int size) {
    Node *temp = l->start, *prev = NULL;

    while (temp && temp->size < size) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) return (void *)-1;

    if (prev) prev->next = temp->next;
    else l->start = temp->next;

    void *loc = temp->loc;
    free(temp);
    return loc;
}

void insert_hole(List *l, int size, void *loc) {
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->size = size;
    newnode->loc = loc;
    newnode->next = NULL;

    if (!l->start || l->start->size > size) {
        newnode->next = l->start;
        l->start = newnode;
        return;
    }

    Node *temp = l->start;
    while (temp->next && temp->next->size <= size) {
        temp = temp->next;
    }
    newnode->next = temp->next;
    temp->next = newnode;
}

void *get_adjecent_hole(List *l, void *loc, int size) {
    Node *temp = l->start, *prev = NULL;

    while (temp && temp->size != size) {
        prev = temp;
        temp = temp->next;
    }

    while (temp && temp->size == size) {
        if ((char *)temp->loc + size == loc || loc + size == temp->loc) {
            if (prev) prev->next = temp->next;
            else l->start = temp->next;

            void *ret = temp->loc;
            free(temp);
            return ret;
        }
        prev = temp;
        temp = temp->next;
    }

    return (void *)-1;
}
