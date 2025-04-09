#include <xinu.h>

syscall registercbk( void (* fcbk) (void) )
{
    intmask mask;            // Saved interrupt mask
    syscall status;          // Return status

    mask = disable();        // Disable interrupts


    // Check if a callback is already registered
    if (proctab[currpid].prasyncipc == 1)
        status = SYSERR;     // Return error code
    else
    {
        if(fcbk == NULL)
        // Check for NULL function pointer
            status = SYSERR;
        else
        {
            // Register the callback function
            proctab[currpid].prasyncipc = 1;
            proctab[currpid].prrecvcbk = fcbk;
            status = OK;
        }
    }
    
    restore(mask);           // Restore interrupts           */
    return status;
}