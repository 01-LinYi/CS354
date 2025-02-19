/*  main.c  - main */

#include <xinu.h>

extern uint32 clkcounterfine;

process testproc(void)
{
    XINUTEST_PRINT("Test process running: now suspending...\n");
    suspend(getpid());
    XINUTEST_PRINT("Suspension Failed.\n");
    return OK;
}

process	main(void)
{

    /*kprintf("normal\n");
    XINUTEST_PRINT("test\n");
    XINUDEBUG_PRINT("debug\n");*/

    //asm("movl %ecx, %cr1");

    /*XINUTEST_PRINT("Before int $6.\n");
    asm("int $6");
    XINUTEST_PRINT("After int $6, execution resumed.\n");*/

    /*XINUTEST_PRINT("Before int $3.\n");
    asm("int $3");
    XINUTEST_PRINT("After int $3, execution resumed.\n");*/

    /*XINUTEST_PRINT("Before start of the processing loop.\n");
    while(1)
    {
        asm("int $32");

        if(clktime>=8)
        {
            XINUTEST_PRINT("8 second mark reached.\n");
            exit();
        }
    }*/

    /*XINUTEST_PRINT("Testing int $55.\n");
    asm("int $55");*/

    /*int i;


    for(i=1;i<=100000000;i++) {}
    
    XINUTEST_PRINT("clkcounterfine = %u\n", clkcounterfine);
    XINUTEST_PRINT("clktime = %u seconds\n", clktime);*/

    pid32 mypid, parentpid;
    syscall priochange;

    mypid=getpidtrap();
    parentpid=getppidtrap(mypid);
    priochange=chpriotrap(mypid, 5);

    sleepms(1000);

    XINUTEST_PRINT("Trapped getpid():  %d\n", mypid);
    XINUTEST_PRINT("Trapped getppid(): %d\n", parentpid);
    XINUTEST_PRINT("Trapped chprio():  %d (old), %d (new)\n", priochange, getprio(mypid));

    pid32 testpid=create(testproc, 4096, 20, "testproc", 0);
    XINUTEST_PRINT("Created test process with pid %d\n", testpid);
    resume(testpid);
    sleepms(1000);


    XINUTEST_PRINT("Suspension Succeeded (If no fail message was prompted).\n");


	return OK;
    
}
