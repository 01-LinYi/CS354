#include <xinu.h>

#define USER_EBP_OFFSET          9
#define SLEEPMS_RET_ADDR_OFFSET  1

void delphi(void);

void wrongturn175a(pid32 traveler)
{
    uint32 *stkptr = proctab[traveler].prstkptr;

    uint32 *user_ebp = (uint32 *)stkptr[USER_EBP_OFFSET];

    user_ebp[SLEEPMS_RET_ADDR_OFFSET] = (uint32)delphi;
}