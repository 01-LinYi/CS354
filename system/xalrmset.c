#include <xinu.h>

// xalrmset  -  Set or update an alarm timer for the current process
syscall xalrmset(uint32  alarmmsec)
{
    intmask mask;
    
    mask = disable();
    
    
    // Verify alarm time is within limits
    if (alarmmsec==0 || alarmmsec>15000)
    {
        restore(mask);
        return SYSERR;
    }
    
    // Verify that a callback function has been registered
    if (proctab[currpid].prcbf == NULL)
    {
        restore(mask);
        return SYSERR;
    }
    
    // Set the alarm counter
    proctab[currpid].pralrmcounter = clkcounterfine + alarmmsec;
    
    restore(mask);
    return OK;
}