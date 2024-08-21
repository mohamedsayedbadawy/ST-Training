#include "heap.h"
#include <stdio.h>
#include <string.h>

// Static variables for the heap memory and program break
static unsigned char heap[HEAP_SIZE];
static void* Prog_Brk = heap;
static struct node* free_list_head = NULL;
static struct node* free_list_tail = NULL;

void* HmmAlloc(unsigned int size) {
    if (size == 0) return NULL;

    // Align the size to PAGE_SIZE and include metadata
    size = ((size + ALLOC_METADATA + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE;

    // If the free list is empty, initialize it
    if (free_list_head == NULL) {
        free_list_head = (struct node*)Prog_Brk;
        free_list_head->Blk_size = HEAP_SIZE - size - ALLOC_METADATA;
        free_list_head->next = NULL;
        free_list_head->prev = NULL;
        free_list_tail = free_list_head;

        void* allocated_memory = Prog_Brk;
        Prog_Brk = (unsigned char*)Prog_Brk + size;
        return allocated_memory;
    }

    // Traverse the free list to find a suitable block
    struct node* current = free_list_head;
    while (current != NULL) {
        if (current->Blk_size >= size) {
            if (current->Blk_size - size > ALLOC_METADATA) {
                // Split the block
                struct node* newBlock = (struct node*)((unsigned char*)current + size + ALLOC_METADATA);
                newBlock->Blk_size = current->Blk_size - size - ALLOC_METADATA;
                newBlock->next = current->next;
                newBlock->prev = current;

                if (current->next) {
                    current->next->prev = newBlock;
                }
                current->next = newBlock;
                current->Blk_size = size;

                if (current == free_list_tail) {
                    free_list_tail = newBlock;
                }
            }

            // Remove the block from the free list
            if (current == free_list_head) {
                free_list_head = current->next;
            } else {
                current->prev->next = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            }

            return (void*)((unsigned char*)current + ALLOC_METADATA);
        }
        current = current->next;
    }

    // If no suitable block found, allocate from the program break
    if ((unsigned char*)Prog_Brk + size > heap + HEAP_SIZE) {
        return NULL; // Not enough memory
    }

    void* allocated_memory = Prog_Brk;
    Prog_Brk = (unsigned char*)Prog_Brk + size;
    return allocated_memory;
}

void HmmFree(void* ptr) {
    if (ptr == NULL) return;

    // Retrieve the block metadata
    struct node* block = (struct node*)((unsigned char*)ptr - ALLOC_METADATA);
    block->next = free_list_head;
    block->prev = NULL;

    if (free_list_head) {
        free_list_head->prev = block;
    }
    free_list_head = block;

    // Merge adjacent free blocks
    struct node* current = free_list_head;
    while (current->next) {
        if ((unsigned char*)current + current->Blk_size + ALLOC_METADATA == (unsigned char*)current->next) {
            current->Blk_size += current->next->Blk_size + ALLOC_METADATA;
            current->next = current->next->next;

            if (current->next) {
                current->next->prev = current;
            }
        } else {
            current = current->next;
        }
    }
}

void vdDisplayPrgBrk() {
    printf("Program break at: %p\n", Prog_Brk);
}
