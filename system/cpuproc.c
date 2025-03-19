#include <xinu.h>

void cpuproc(int delay)
{    
    uint32 start_time = clkcounterfine;

    while(clkcounterfine<STOPTIME) {}
    
    sleepms(delay);
    
    XINUTEST_PRINT("PID %d: cpuproc finished. clkcounterfine=%d, CPU usage=%d, avg resp time=%d, prstarvecount=%d\n",
                currpid, clkcounterfine, proctab[currpid].prcputotusage,
                meanresponsetime(currpid), proctab[currpid].prstarvecount);
}