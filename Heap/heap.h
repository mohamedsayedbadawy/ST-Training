#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

#define HEAP_SIZE (1024 * 1024)
#define PAGE_SIZE 4096
#define ALLOC_METADATA sizeof(struct node)

struct node {
    unsigned int Blk_size;   // Size of the block
    struct node* next;       // Pointer to the next free block
    struct node* prev;       // Pointer to the previous free block
};

// Allocates memory of the specified size
void* HmmAlloc(unsigned int size);

// Frees the allocated memory
void HmmFree(void* ptr);

// Displays the current program break
void vdDisplayPrgBrk();

#endif // HEAP_H
