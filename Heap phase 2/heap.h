#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

#define HEAP_SIZE (1024 * 1024 * 1024)  // 1 GB Heap Size
#define PAGE_SIZE 4096
#define ALLOC_METADATA sizeof(struct node)

struct node {
    unsigned int Blk_size;
    struct node* next;
    struct node* prev;
};

void* HmmAlloc(size_t size);  // Use size_t here
void HmmFree(void* ptr);
void vdDisplayFreeNode();
void vdDisplayPrgBrk();

#endif // HEAP_H
