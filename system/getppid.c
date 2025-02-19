#include <xinu.h>

pid32 getppid(pid32 pid)
{
	if(pid<0 || pid>=NPROC) // pid out of range
        return SYSERR;

    if(proctab[pid].prstate==PR_FREE) // process state field prstate has value PR_FREE
        return SYSERR;

    if(pid==0) // idle process
        return 0;

    pid32 ppid=proctab[pid].prparent;

    if(ppid<0 || ppid>=NPROC || proctab[ppid].prstate==PR_FREE) // Parent is invalid
        return SYSERR;

    return ppid;
}