#include <xinu.h>

#define CTXSW_RET_ADDR_OFFSET  10

void delphi(void);

void wrongturn175(pid32 traveler)
{
    uint32 *stkptr = proctab[traveler].prstkptr;

    // Overwrite the saved return address with the address of delphi()
    stkptr[CTXSW_RET_ADDR_OFFSET] = (uint32)delphi;
}