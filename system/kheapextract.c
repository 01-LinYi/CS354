#include <xinu.h>


void kheapextract(struct perprocmem *header, char *memptr)
{
    struct perprocmem *curr, *prev;
    
    // If list is empty, nothing to extract
    if (header->memnext == NULL)
        return;

    
    // Find the node to remove
    prev = header;
    curr = header->memnext;
    
    while(curr!=NULL && curr->memptr!=memptr)
    {
        prev = curr;
        curr = curr->memnext;
    }
    
    // Node not found
    if (curr == NULL)
        return;
    
    
    // Remove node from list if found
    prev->memnext = curr->memnext;
    

    // Set flag to indicate kheapextract is calling freemem
    kheapflag = 1;

    // Free the node
    freemem((char *)curr, sizeof(struct perprocmem));
}