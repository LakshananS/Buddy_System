#ifndef LIST
#define LIST

typedef struct Node {
    int size;
    void *loc;
    struct Node *next;
} Node;

typedef struct List {
    Node *start;
} List;

void *get_hole(List *l, int size);
void insert_hole(List *l, int size, void *loc);
void *get_adjecent_hole(List *l, void *loc, int size);

#endif
