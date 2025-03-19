#include <xinu.h>

static status remove(pid32 pid, qid16 qid)
{
    int32 prev, curr;
    
    prev=qid;
    curr=queuetab[prev].qnext;

    while(curr!=qid)
    {
        if(curr==pid)
        {
            // Unlink the element from the queue
            queuetab[prev].qnext=queuetab[curr].qnext;
            queuetab[queuetab[curr].qnext].qprev=prev;
            
            // Clear the removed node's links
            queuetab[curr].qnext = EMPTY;
            queuetab[curr].qprev = EMPTY;
            return OK;
        }
        prev=curr;
        curr=queuetab[curr].qnext;
    }
    return SYSERR; // Process not found in the queue
}

status modprioready(pid32 pid, qid16 qid, pri16 new_priority)
{
    if(pid<0 || pid>=NPROC)
        return SYSERR;
        
    if (proctab[pid].prstate!=PR_READY)
        return SYSERR;

    // Remove the process from the ready list
    if(remove(pid, qid)==SYSERR)
        return SYSERR;

    // Set the new priority
    proctab[pid].prprio=new_priority;

    // Reinsert it into the ready list so that it now appears at the right place
    insert(pid, qid, new_priority);

    return OK;
}