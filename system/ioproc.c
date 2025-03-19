#include <xinu.h>

void ioproc(int delay)
{
    uint32 start_time = clkcounterfine;
    while(clkcounterfine<STOPTIME)
    {
        int j,k;
        for(j=1;j<=1000;j++)
        {
            k=j%7; // Do some arithmetic operations
        }
        sleepms(50);
    }
    
    sleepms(delay);
    
    XINUTEST_PRINT("PID %d: ioproc finished. clkcounterfine=%d, CPU usage=%d, avg resp time=%d, prstarvecount=%d\n",
                currpid, clkcounterfine, proctab[currpid].prcputotusage,
                meanresponsetime(currpid), proctab[currpid].prstarvecount);
}