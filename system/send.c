/* send.c - send */

#include <xinu.h>

#define USER_EBP_OFFSET          9
#define SLEEPMS_RET_ADDR_OFFSET  1

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	send(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg) {
		restore(mask);
		return SYSERR;
	}
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/

    // If recipient has registered a callback function
	if(prptr->prasyncipc)
    {

		uint32 *stkptr = prptr->prstkptr;
		uint32 *user_ebp = (uint32 *)stkptr[USER_EBP_OFFSET];
		
		// Save the original return address for later restoration
		prptr->prsleepret = user_ebp[SLEEPMS_RET_ADDR_OFFSET];
		
		// Modify the return address to jump to managedetour()
		extern void managedetour(void);
		user_ebp[SLEEPMS_RET_ADDR_OFFSET] = (uint32)managedetour;
	}

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}

    //XINUTEST_PRINT("Send %d %u %u\n", currpid, clkcounterfine, msg);

	restore(mask);		/* Restore interrupts */
	return OK;
}
