#ifndef _HEAPMEM_H_
#define _HEAPMEM_H_

// Structure for tracking per-process allocated memory blocks
struct perprocmem
{
    uint32 memsize;                /* Size of memory allocated (multiple of 8 bytes) */
    char *memptr;                  /* Ptr to in-use memory */
    struct perprocmem *memnext;    /* Ptr to next list element */
};


void kheapinsert(struct perprocmem *ptr, char *memptr, uint32 msz);
void kheapextract(struct perprocmem *ptr, char *memptr);


// Global flag to track calls from kheap functions
extern uint16 kheapflag;

#endif