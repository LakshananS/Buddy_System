#include "buddy_system.h"
#include "list.h"
#include "memory.h"
#include "virtual_mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *mem;
int max_size;
List holes;

void make_mem(int max) {
    max_size = max;
    mem = calloc(max_size, sizeof(Chunk));
    ((Chunk *)mem)->size = max_size;
    ((Chunk *)mem)->pid = -1;
    insert_hole(&holes, max_size, mem);
}

static int alloc(int pid, int size) {
    Chunk *temp = (Chunk *)get_hole(&holes, size);

    if (temp == (Chunk *)-1) {
        return -1;
    }

    while (temp->size / 2 >= size) {
        insert_hole(&holes, temp->size / 2, (void *)((char *)temp + temp->size / 2));
        temp->size /= 2;
    }
    temp->pid = pid;
    return 0;
}

int allocate_page(int pid, int size) {
    int stat = alloc(pid, size);
    if (stat != 0) {
        stat = virtualMemoryEnqueue(pid, size);
    }
    return stat;
}

static int delloc(int pid) {
    Chunk *pos = (Chunk *)mem;
    while (pos < (Chunk *)((char *)mem + max_size)) {
        if (pos->pid == pid) {
            break;
        }
        pos = (Chunk *)((char *)pos + pos->size);
    }

    if (pos == (Chunk *)((char *)mem + max_size)) {
        return -1;
    }

    pos->pid = -1;
    Chunk *temp = (Chunk *)get_adjecent_hole(&holes, pos, pos->size);

    while (temp != (Chunk *)-1) {
        Chunk *loc = (Chunk *)((char *)pos < (char *)temp ? pos : temp);
        loc->size *= 2;
        pos = loc;
        temp = (Chunk *)get_adjecent_hole(&holes, loc, loc->size);
    }
    insert_hole(&holes, pos->size, pos);
    return 0;
}

int free_page(int pid) {
    int stat = delloc(pid);
    if (stat != 0) {
        Chunk *temp = get_process_virt_mem(pid);
        if (temp != (Chunk *)-1) {
            free(temp);
            stat = 0;
        }
    }
    return stat;
}

void *get_process(int pid) {
    Chunk *pos = (Chunk *)mem;
    while (pos < (Chunk *)((char *)mem + max_size)) {
        if (pos->pid == pid) {
            return pos;
        }
        pos = (Chunk *)((char *)pos + pos->size);
    }

    Chunk *temp = get_process_virt_mem(pid);
    if (temp == (Chunk *)-1) {
        return (void *)-1;
    }

    while (alloc(temp->pid, temp->size) != 0) {
        Chunk *t = (Chunk *)mem;
        virtualMemoryEnqueue(t->pid, t->size);
        delloc(t->pid);
    }

    return get_process(pid);
}

void print_stat() {
    printf("Main memory status:\n");
    Chunk *temp = (Chunk *)mem;
    int size = 0;
    while (size < max_size) {
        printf("%d:%d\t", temp->pid, temp->size);
        size += temp->size;
        temp = (Chunk *)((char *)temp + temp->size);
    }
    printf("\n");
    display_virtual_memory();
}
