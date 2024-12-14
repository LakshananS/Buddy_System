#include "virtual_mem.h"
#include <stdio.h>
#include <stdlib.h>

static int capacity = 1024;
virtualMemoryQueue *front = NULL, *rear = NULL;

int virtualMemoryEnqueue(int pid, int size) {
    if (size > capacity) return -1;

    virtualMemoryQueue *newnode = (virtualMemoryQueue *)malloc(sizeof(virtualMemoryQueue));
    newnode->size = size;
    newnode->pid = pid;
    newnode->next = NULL;

    if (!rear) front = rear = newnode;
    else rear->next = newnode, rear = newnode;

    capacity -= size;
    return 0;
}

Chunk *get_process_virt_mem(int pid) {
    virtualMemoryQueue *temp = front, *prev = NULL;

    while (temp && temp->pid != pid) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) return (Chunk *)-1;

    if (prev) prev->next = temp->next;
    else front = temp->next;

    if (!temp->next) rear = prev;

    capacity += temp->size;

    Chunk *chunk = (Chunk *)malloc(sizeof(Chunk));
    chunk->pid = temp->pid;
    chunk->size = temp->size;

    free(temp);
    return chunk;
}

void display_virtual_memory() {
    printf("Virtual Memory: ");
    virtualMemoryQueue *temp = front;
    if (!temp) {
        printf("<EMPTY>\n");
        return;
    }
    while (temp) {
        printf("%d:%d\t", temp->pid, temp->size);
        temp = temp->next;
    }
    printf("\n");
}
