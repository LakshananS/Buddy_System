#include "buddy_system.h"
#include <stdio.h>

int main() {
    make_mem(1024);

    allocate_page(1, 512);
    print_stat();

    allocate_page(2, 256);
    print_stat();

    allocate_page(3, 128);
    print_stat();

    free_page(1);
    print_stat();

    return 0;
}
