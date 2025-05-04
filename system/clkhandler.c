/* clkhandler.c - clkhandler */

#include <xinu.h>


/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	clkcounterfine++;

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


	// Check if the current process has a timer alarm set 
    
    if(proctab[currpid].pralrmcounter>0 && proctab[currpid].prcbf!=NULL)
	{
        // Check if alarm has expired
        if (clkcounterfine>=proctab[currpid].pralrmcounter)
		{
            // Set the detour flag for clkdisp.S
            makedetouralrm = 1;
            
            // Reset alarm counter to prevent multiple callbacks
            proctab[currpid].pralrmcounter = 0;
        }
    }

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}
