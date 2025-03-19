/*  main.c  - main */

#include <xinu.h>

extern uint32 clkcounterfine;

extern uint32 meanresponsetime(pid32);

extern void cpuproc(int);
extern void ioproc(int);
extern void shybrid(void);
extern void rogue(int);



void test_proc(void)
{
    uint32 start_time = clktime; // Use clktime if available or another timer variable
    
    int i;
    for(i=1;i<=100000000;i++) {}
    
    int32 cputot = getcputot(currpid);
    XINUTEST_PRINT("Process %d finished. Total CPU usage: %d ms.\n", currpid, cputot);
}

void starved_proc(void)
{
    XINUTEST_PRINT("Starved process %d is now running.\n", currpid);
    XINUTEST_PRINT("prstarvation = %d, prstarvecount = %d\n",
    proctab[currpid].prstarvation, proctab[currpid].prstarvecount);
    
    int i;
    for(i=1;i<=100000000;i++) {}

    kprintf("Starved process %d completed.\n", currpid);    
}

void response_proc(void)
{
    int i;
    for(i=1;i<=100000000;i++) {}

    uint32 mean=meanresponsetime(currpid);

    if(mean==SYSERR)
        XINUTEST_PRINT("Process %d: Mean response time computing error\n", currpid);
    else
        XINUTEST_PRINT("Process %d: Mean response time is %u ms\n", currpid, mean);
}

void benchmark_a(void)
{
    pid32 a1=create(cpuproc, 1024, 4, "test_a", 1, 100);
    pid32 a2=create(cpuproc, 1024, 4, "test_a", 1, 200);
    pid32 a3=create(cpuproc, 1024, 4, "test_a", 1, 300);
    pid32 a4=create(cpuproc, 1024, 4, "test_a", 1, 400);

    resume(a1);resume(a2);resume(a3);resume(a4);

    XINUTEST_PRINT("Workload generator (Benchmark A) spawned 4 cpuproc processes.\n");
    
    return;
}

void benchmark_b(void)
{
    pid32 b1=create(ioproc, 1024, 4, "test_b", 1, 100);
    pid32 b2=create(ioproc, 1024, 4, "test_b", 1, 200);
    pid32 b3=create(ioproc, 1024, 4, "test_b", 1, 300);
    pid32 b4=create(ioproc, 1024, 4, "test_b", 1, 400);

    resume(b1);resume(b2);resume(b3);resume(b4);

    XINUTEST_PRINT("Workload generator (Benchmark B) spawned 4 ioproc processes.\n");
    
    return;
}

void benchmark_c(void)
{
    pid32 c1=create(cpuproc, 1024, 4, "test_c", 1, 100);
    pid32 c2=create(cpuproc, 1024, 4, "test_c", 1, 200);
    pid32 c3=create(ioproc, 1024, 4, "test_c", 1, 300);
    pid32 c4=create(ioproc, 1024, 4, "test_c", 1, 400);

    resume(c1);resume(c2);resume(c3);resume(c4);

    XINUTEST_PRINT("Workload generator (Benchmark C) spawned 2 cpuproc and 2 ioproc processes.\n");
    
    return;
}

void benchmark_d(void)
{
    shybrid();
}

void bonus(void)
{
    pid32 e1=create(cpuproc, 1024, 4, "test_e", 1, 100);
    pid32 e2=create(cpuproc, 1024, 4, "test_e", 1, 200);
    pid32 e3=create(cpuproc, 1024, 4, "test_e", 1, 300);
    pid32 e4=create(cpuproc, 1024, 4, "test_e", 1, 400);
    pid32 e5=create(rogue, 1024, 4, "test_e", 1, 500);

    resume(e1);resume(e2);resume(e3);resume(e4);resume(e5);

    XINUTEST_PRINT("Workload generator (Bonus) spawned 4 cpuproc and 1 rogue processes.\n");
    
    return;
}


int main(void)
{

    int i;

    /*pid32 test1Pid = create(test_proc, 1024, 4, "test_proc", 0);
    resume(test1Pid);

    pid32 test2Pid = create(test_proc, 1024, 4, "test_proc", 0);
    resume(test2Pid);*/


    /*pid32 starvedPid = create(starved_proc, 1024, 1, "starved_proc", 0);
    
    resume(starvedPid);

    for(i=1;i<=100000000;i++) {}

    XINUTEST_PRINT("Run the starved process.\n");

    //for(i=1;i<=100000000;i++) {}*/

    
    /*pid32 responsePid = create(response_proc, 1024, 10, "response_proc", 0);
    resume(responsePid);

    for(i=1;i<=100000000;i++) {}*/



    XINUTEST_PRINT("==========XINU Benchmark Testing Starts==========\n");

    /*pid32 a=create(benchmark_a, 1024, 4, "test_a", 0);
    resume(a);*/

    /*pid32 b=create(benchmark_b, 1024, 4, "test_b", 0);
    resume(b);*/

    /*pid32 c=create(benchmark_c, 1024, 4, "test_c", 0);
    resume(c);*/

    /*pid32 d=create(benchmark_d, 1024, 4, "test_d", 0);
    resume(d);*/

    pid32 e=create(bonus, 1024, 4, "test_e", 0);
    resume(e);

    return OK;
}