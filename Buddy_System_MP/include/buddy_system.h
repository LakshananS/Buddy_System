#ifndef BUDDY_SYS
#define BUDDY_SYS

void make_mem(int max_size);
int allocate_page(int pid, int size);
int free_page(int pid);
void *get_process(int pid);
void print_stat();

#endif
