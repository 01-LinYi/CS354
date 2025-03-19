/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */

extern uint32 currcputime;
extern uint32 clkcounterfine;


void	clkhandler()
{
    int resched_needed=0;

    clkcounterfine++;

    if((clkcounterfine % (RECENTWIN * 1000)) == 0)
    {
        int i;
        for(i=0;i<NPROC;i++)
            if(proctab[i].prstate==PR_READY)
            {
                // Check if the process has been waiting too long                 */
                if((clkcounterfine-proctab[i].prreadystart)>=(RECENTWIN*1000))
                {
                    proctab[i].prstarvation=1;  // Process starving
                    proctab[i].prstarvecount++; // Increment starvation count
                }
            }
    }

    #if STARVATIONPREV
        // If starvation prevention is enabled, iterate once again to boost priorities.
        int i;
        for(i=0;i<NPROC;i++)
        {
            if(proctab[i].prstate==PR_READY && proctab[i].prstarvation==1)
            {
                if(proctab[i].prprio<7)
                {
                    if(modprioready(i,readylist,7)==OK)
                    {
                        proctab[i].prstarvation=0;
                        resched_needed=1;
                    }
                }
                else
                    proctab[i].prstarvation = 0;
            }
        }
        if(resched_needed)
        {
            resched();
            resched_needed=0;
        }
    #endif // STARVATIONPREV

	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

    currcputime++; // LIN, Yi: Increment CPU Time

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}
