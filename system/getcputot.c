#include <xinu.h>

extern uint32 currcputime;

int32 getcputot(pid32 pid) 
{
    if(pid<0 || pid>=NPROC)
        return SYSERR;

    if(proctab[pid].prstate == PR_FREE)
        return SYSERR;

    if(pid == currpid) 
        /* For the running process, add the current running time */
        return (int32)(proctab[pid].prcputotusage + currcputime);
    else
        /* For a process not currently running, return its recorded total */
        return (int32)(proctab[pid].prcputotusage);
}