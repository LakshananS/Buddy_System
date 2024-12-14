#ifndef VIRTUAL_MEM
#define VIRTUAL_MEM

#include "memory.h"

typedef struct processQueue {
    int size;
    int pid;
    struct processQueue *next;
} virtualMemoryQueue;

int virtualMemoryEnqueue(int pid, int processSize);
Chunk *get_process_virt_mem(int pid);
void *virtualMemoryDequeue(int freeMemory);
void display_virtual_memory();
void flushQueue();

#endif
