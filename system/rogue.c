#include <xinu.h>


void rogue(int delay) // Alternating between computations and brief sleeps
{
    int i,j=0;
    uint32 start_time = clkcounterfine;

    while(clkcounterfine<STOPTIME)
    {
        for(i=1;i<=200000000;i++) {}
        
        sleepms(1);
    }

    sleepms(delay);

    XINUTEST_PRINT("PID %d: rogue finished. clkcounterfine=%d, CPU usage=%d, avg resp time=%d, prstarvecount=%d\n",
                currpid, clkcounterfine, proctab[currpid].prcputotusage,
                meanresponsetime(currpid), proctab[currpid].prstarvecount);
}