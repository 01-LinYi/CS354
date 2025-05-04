#include <xinu.h>


void kheapinsert(struct perprocmem *header, char *memptr, uint32 msz)
{
    struct perprocmem *curr, *prev, *newnode;
    
    // Set flag to indicate kheapinsert is calling getmem
    kheapflag = 1;
    
    // Allocate a new node for the memory block list
    newnode = (struct perprocmem *)getmem(sizeof(struct perprocmem));
    
    // Fill in the new node details
    newnode->memptr = memptr;
    newnode->memsize = msz;
    
    // Insert into the sorted list (by increasing memptr address)
    if(header->memnext == NULL)
    {
        // First entry in the list
        newnode->memnext = NULL;
        header->memnext = newnode;
        return;
    }
    

    prev = header;
    curr = header->memnext;
    
    while(curr!=NULL && curr->memptr<memptr)
    {
        prev=curr;
        curr=curr->memnext;
    }
    
    // Insert new node between prev and curr
    newnode->memnext = curr;
    prev->memnext = newnode;
}