#include <xinu.h>

void shybrid(void)
{
    pid32 pid;
    int i;
    
    // Spawn many I/O-bound processes
    for(i=1;i<=50;i++)
    {
        pid=create(ioproc, 1024, 4, "ioproc", 1, i*100);
        resume(pid);
    }
    
    // Spawn a few CPU-bound processes
    for(i=1;i<=2;i++)
    {
        pid=create(cpuproc, 1024, 4, "cpuproc", 1, (i+50)*100);
        resume(pid);
    }
    
    XINUTEST_PRINT("Skewed hybrid workload generator: spawned 50 ioproc and 2 cpuproc processes.\n");
}