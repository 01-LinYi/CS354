#include <xinu.h>


// xinualarm - Register a callback function for a timer alarm
syscall xinualarm(uint32 alarmmsec, void (*cbf) (void))
{
    intmask mask;   // Saved interrupt mask
    
    mask = disable();
    
    // Check if alarm time is valid
    if(alarmmsec==0 || alarmmsec>15000)
    {
        restore(mask);
        return SYSERR;
    }
    
    // Check if alarm already registered
    if(proctab[currpid].pralrmcounter!=0)
    {
        restore(mask);
        return SYSERR;
    }
    
    // Verify callback function pointer is in text segment
    extern int text, etext;  // Start and end of text segment
    if((uint32)cbf < (uint32)&text || (uint32)cbf > (uint32)&etext)
    {
        restore(mask);
        return SYSERR;
    }
    
    // Register callback function
    proctab[currpid].prcbf = cbf;
    
    // Set alarm to expire at current time + alarm time
    proctab[currpid].pralrmcounter = clkcounterfine + alarmmsec;
    
    restore(mask);
    return OK;
}