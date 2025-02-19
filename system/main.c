/*  main.c  - main */

#include <xinu.h>

extern uint32 clkcounterfine;

extern int addfour(int, int, int, int);
extern int testaddfourC(void);

void test(void)
{
    pid32 curr_pid,parent_pid,invalid_result,idle_result;

    // Test 1: Get parent's ID for the current process
    curr_pid = getpid();
    kprintf("Current process id: %d\n", curr_pid);

    parent_pid = getppid(curr_pid);
    kprintf("Parent process id of %d: %d\n", curr_pid, parent_pid);

    // Test 2: Call getppid() with an invalid PID
    invalid_result = getppid(NPROC);
    if (invalid_result == SYSERR)
        kprintf("getppid(NPROC) correctly returned SYSERR for invalid pid\n");
    else
        kprintf("Error: getppid(NPROC) returned %d instead of SYSERR\n", invalid_result);

    // Test 3: Call getppid() for the idle process
    idle_result = getppid(0);
    kprintf("getppid(0) returned: %d \n", idle_result);
}

void sndch(char ch)
{
    while(1)
        kputc(ch);
}

process	main(void)
{
    
    kprintf("NPROC = %d \n", NPROC);

    /*pid32 pid; // PID of the created process
    int i;

    // Create a process using createminpid
    for(i=0;i<5;i++)
    {
        pid=createminpid(shell, 1024, 20, "TestProcess", 0);
        if(pid==SYSERR)
            kprintf("Failed to create process %d\n", i);
        else
            kprintf("Created process %d with PID %d\n", i, pid);

        // Sleep for a moment to let the process run
        sleepms(200);

        // Kill the process to test PID reuse
        if(pid!=SYSERR)
        {
            kill(pid);
            kprintf("Killed process with PID %d\n", pid);
        }

        // Create another process and check its PID
        pid=createminpid(shell, 1024, 20, "TestProcess", 0);
        if(pid==SYSERR)
            kprintf("Failed to create new process after killing\n");
        else
            kprintf("Created new process with PID %d after killing previous\n", pid);
    }*/
    
    /*pid32 testPID=create(test, 1024, 20, "testProc", 0);
    resume(testPID);
    */

    /*pid32 pidA,pidB,pidC;

    pidA = create(sndch, 1024, 20, "send A", 1, 'A');
    pidB = create(sndch, 1024, 20, "send B", 1, 'B');
    pidC = create(sndch, 1024, 20, "send C", 1, 'C');

    resume(pidA);
    resume(pidB);
    resume(pidC);*/

    /*int i;

    asm("cli");

    for(i=1;i<=100000000;i++) {}
    
    kprintf("clkcounterfine = %u\n", clkcounterfine);
    kprintf("clktime = %u seconds\n", clktime);

    asm("sti");*/

    //kprintf("About to return from main\n");


    /*int a=1,b=2,c=3,d=4;
    int result = addfour(a, b, c, d);
    kprintf("Result = %d, b = %d \n", result, b);*/

    /*int result = testaddfourC();
    kprintf("Result = %d\n", result);*/

    /*pid32 pidA,pidB,pidC;

    pidA = creates(sndch, 'A');
    pidB = creates(sndch, 'B');
    pidC = creates(sndch, 'C');


    resume(pidA);
    resume(pidB);
    resume(pidC);*/

    sleepms(1000);


	return OK;
    
}
