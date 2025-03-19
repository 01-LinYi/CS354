#include <xinu.h>

uint32 meanresponsetime(pid32 pid)
{
    if(pid<0 || pid>=NPROC)
        return SYSERR;

    if(proctab[pid].prstate == PR_FREE)
        return SYSERR;

    if(proctab[pid].prnumready==0)
        return SYSERR;

    uint32 mean=(proctab[pid].prsumresponse+(proctab[pid].prnumready/2))
                /proctab[pid].prnumready;
    
    return mean;
}