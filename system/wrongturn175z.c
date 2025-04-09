#include <xinu.h>

#define USER_EBP_OFFSET          9
#define SLEEPMS_RET_ADDR_OFFSET  1

void delphiz(void);

void wrongturn175z(pid32 traveler)
{
    intmask mask;
    uint32 *stkptr;
    uint32 *user_ebp;
    
    mask = disable();
    
    stkptr = proctab[traveler].prstkptr;
    
    user_ebp = (uint32 *)stkptr[USER_EBP_OFFSET];
    
    // Save the original return address for later use in delphiz
    proctab[traveler].prsleepret = user_ebp[SLEEPMS_RET_ADDR_OFFSET];

    // Modify the return address to jump to delphiz instead
    user_ebp[SLEEPMS_RET_ADDR_OFFSET] = (uint32)delphiz;
    
    restore(mask);
}