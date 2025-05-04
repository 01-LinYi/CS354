#include <xinu.h>

extern int32 text,etext;        /* Start and end address of text segment */

// xalrmreg  -  Register a callback function for an alarm without activating it
syscall xalrmreg(void  (*cbf) (void))
{
    intmask mask;
    
    mask = disable();
    
    
    // Verify the callback function pointer is within text segment
    if((uint32)cbf<(uint32)&text || (uint32)cbf>(uint32)&etext)
    {
        restore(mask);
        return SYSERR;
    }
    
    // Register the callback function
    proctab[currpid].prcbf = cbf;
    
    // Initialize counter to 0, indicating no alarm is active
    proctab[currpid].pralrmcounter = 0;
    
    restore(mask);
    return OK;
}