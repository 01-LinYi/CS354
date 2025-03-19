/* resched.c - resched, resched_cntl */

#include <xinu.h>

extern uint32 currcputime;
extern uint16 quantumts;
extern uint32 clkcounterfine;
extern struct xst xstds[8];


struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

    if(preempt==0)
    {
        ptold->prprio=xstds[ptold->prprio].xstqexp;
        ptold->prtimeslice=xstds[ptold->prprio].xstquantum;
    }
    else
    {
        if(ptold->prvoluntary==1)
        {
            ptold->prprio=xstds[ptold->prprio].xstslpret;
            ptold->prtimeslice=xstds[ptold->prprio].xstquantum;
            ptold->prvoluntary=0;
        }
        else
            ptold->prtimeslice=preempt;
    }


	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			preempt = QUANTUM; //LIN, Yi: Fresh time slice for continuing process
            return;
		}

		/* Old process will no longer remain current */

        ptold->prcputotusage+=currcputime;
        currcputime=0; // LIN, Yi: Accumulate CPU Time and reset
        ptold->prreadystart=clkcounterfine;

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];

    ptnew->prnumready++;
    ptnew->prsumresponse+=clkcounterfine-ptnew->prreadystart;

	ptnew->prstate = PR_CURR;
    
    ptnew->prstarvation=0;  // LIN, Yi: New process (not starving)
    
    //preempt = QUANTUM;		/* Reset time slice for process	*/
	preempt = quantumts; // LIN, Yi: New time slice
    ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
