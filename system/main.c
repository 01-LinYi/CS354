#include <xinu.h>


// process_no_free - allocate memory but don't free it
process process_no_free(void)
{
    char *mem;
    
    XINUTEST_PRINT("Process %d: Allocating 4096 bytes\n", currpid);
    mem = getmem(4096);
    XINUTEST_PRINT("Process %d: Allocated memory at %08X\n", currpid, (uint32)mem);
    XINUTEST_PRINT("Process %d: Exiting without freeing memory\n", currpid);
    
    return OK;
}


// process_multiple_allocs - allocate multiple memory blocks
process process_multiple_allocs(void)
{
    char *mem1, *mem2, *mem3;
    
    XINUTEST_PRINT("Process %d: Allocating three memory blocks\n", currpid);
    mem1 = getmem(1024);
    mem2 = getmem(2048);
    mem3 = getmem(4096);
    
    XINUTEST_PRINT("Process %d: Allocated memory at %08X, %08X, %08X\n", 
            currpid, (uint32)mem1, (uint32)mem2, (uint32)mem3);
    XINUTEST_PRINT("Process %d: Exiting without freeing memory\n", currpid);
    
    return OK;
}


// process_mixed_free - mix of freed and unfreed memory
process process_mixed_free(void)
{
    char *mem1, *mem2, *mem3;
    
    XINUTEST_PRINT("Process %d: Allocating three memory blocks\n", currpid);
    mem1 = getmem(1024);
    mem2 = getmem(2048);
    mem3 = getmem(4096);
    
    XINUTEST_PRINT("Process %d: Allocated memory at %08X, %08X, %08X\n", 
            currpid, (uint32)mem1, (uint32)mem2, (uint32)mem3);
    
    XINUTEST_PRINT("Process %d: Freeing one block at %08X\n", currpid, (uint32)mem2);
    freemem(mem2, 2048);
    
    XINUTEST_PRINT("Process %d: Exiting with two unfreed blocks\n", currpid);
    
    return OK;
}




// alarm_callback - Callback function for XALARM
void alarm_callback(void)
{
    XINUTEST_PRINT("Ring, ring! Alarm triggered at time: %u\n", clkcounterfine);
}

// test_alarm_process - Test process that registers an alarm
process test_alarm_process(uint32 msecs)
{
    XINUTEST_PRINT("Process %d: Setting alarm for %u ms\n", currpid, msecs);
    
    // Register alarm callback
    int result = xinualarm(msecs, alarm_callback);
    
    if (result == SYSERR)
	{
        XINUTEST_PRINT("Process %d: Failed to set alarm\n", currpid);
        return OK;
    }
    
    XINUTEST_PRINT("Process %d: Alarm set, now waiting\n", currpid);
    
	int i,j=0;
	for(i=1;i<=100000000;i++)
		j++;
    
    XINUTEST_PRINT("Process %d: Awake\n", currpid);
    return OK;
}


// multiple_alarms_process - Test process that registers multiple alarms
process multiple_alarms_process(uint32 msecs1,uint32 msecs2)
{
    XINUTEST_PRINT("Process %d: Setting alarm for %u ms\n", currpid, msecs1);
    
    // Register alarm callback
    int result = xinualarm(msecs1, alarm_callback);
    
    if (result == SYSERR)
	{
        XINUTEST_PRINT("Process %d: Failed to set alarm\n", currpid);
        return OK;
    }
    
    XINUTEST_PRINT("Process %d: Alarm set, now waiting\n", currpid);
    


    XINUTEST_PRINT("Process %d: Setting alarm for %u ms\n", currpid, msecs2);
    
    // Register alarm callback
    result = xinualarm(msecs2, alarm_callback);
    
    if (result == SYSERR)
	{
        XINUTEST_PRINT("Process %d: Failed to set alarm\n", currpid);
        return OK;
    }
    
    XINUTEST_PRINT("Process %d: Alarm set, now waiting\n", currpid);


	int i,j=0;
	for(i=1;i<=100000000;i++)
		j++;
    
    XINUTEST_PRINT("Process %d: Awake\n", currpid);
    return OK;
}


// bonus_multiple_alarms_process - Test process that registers multiple alarms
process bonus_multiple_alarms_process(uint32 msecs1,uint32 msecs2)
{
    XINUTEST_PRINT("Process %d: Registering alarm\n", currpid);

    // Register alarm callback
    int result = xalrmreg(alarm_callback);
    
    if (result == SYSERR)
	{
        XINUTEST_PRINT("Process %d: Failed to set alarm\n", currpid);
        return OK;
    }



    XINUTEST_PRINT("Process %d: Setting alarm for %u ms\n", currpid, msecs1);
    
    result = xalrmset(msecs1);

    if (result == SYSERR)
	{
        XINUTEST_PRINT("Process %d: Failed to set alarm\n", currpid);
        return OK;
    }
    
    XINUTEST_PRINT("Process %d: Alarm set, now waiting\n", currpid);
    


    XINUTEST_PRINT("Process %d: Setting alarm for %u ms\n", currpid, msecs2);
    
    result = xalrmset(msecs2);

    if (result == SYSERR)
	{
        XINUTEST_PRINT("Process %d: Failed to set alarm\n", currpid);
        return OK;
    }
    
    XINUTEST_PRINT("Process %d: Alarm set, now waiting\n", currpid);


	int i,j=0;
	for(i=1;i<=100000000;i++)
		j++;
    
    XINUTEST_PRINT("Process %d: Awake\n", currpid);
    return OK;
}


process main(void)
{
	/*
	// Test garbage collection
	
    uint32 i;
    pid32 pid;
    char *mem1, *mem2, *mem3;
    
    // Print system info
    XINUTEST_PRINT("Memory Garbage Collection Test\n");
    XINUTEST_PRINT("-----------------------------\n");
    XINUTEST_PRINT("Initial free memory: %u bytes\n", memlist.mlength);
    

    // Test 1: Allocate memory and exit without freeing
    XINUTEST_PRINT("\nTest 1: Process allocates memory and exits without freeing\n");
    
    pid = create(process_no_free, 1024, 20, "process1", 0);
    resume(pid);
    
    sleepms(1000);
    
    XINUTEST_PRINT("After Test 1: Free memory: %u bytes\n", memlist.mlength);
    

    // Test 2: Multiple memory allocations in one process
    XINUTEST_PRINT("\nTest 2: Process with multiple memory allocations\n");
    
    pid = create(process_multiple_allocs, 1024, 20, "process2", 0);
    resume(pid);
    
    sleepms(1000);
    
    XINUTEST_PRINT("After Test 2: Free memory: %u bytes\n", memlist.mlength);
    

    // Test 3: Mix of freed and unfreed memory
    XINUTEST_PRINT("\nTest 3: Process with mix of freed and unfreed memory\n");
    
    pid = create(process_mixed_free, 1024, 20, "process3", 0);
    resume(pid);
    
    sleepms(1000);
    
    XINUTEST_PRINT("After Test 3: Free memory: %u bytes\n", memlist.mlength);
    */

	//XINUDEBUG_PRINT("Size of procent structure: %d bytes\n", sizeof(struct procent));
    //XINUDEBUG_PRINT("Offset of prcbf: %d bytes\n", (unsigned long)&(((struct procent *)0)->prcbf));
    

	pid32 pid;
    
    
    // Print system info
    XINUTEST_PRINT("XALARM Asynchronous Timer Test\n");
    XINUTEST_PRINT("-----------------------------\n");
    XINUTEST_PRINT("Current time: %u\n", clkcounterfine);
    
/*	
    // Test 1: Basic alarm functionality
    XINUTEST_PRINT("\nTest 1: Basic alarm functionality (500ms)\n");
    pid = create(test_alarm_process, 2048, 20, "test1", 1, 500);
    resume(pid);
    

    sleepms(2000);
*/    


  
    

/*
    // Test 2: Error conditions
    XINUTEST_PRINT("\nTest 2: Error conditions\n");
    
    // Create process with invalid alarm time (0ms)
    pid = create(test_alarm_process, 2048, 20, "test2a", 1, 0);
    resume(pid);
    
    sleepms(500);
    
    // Create process with invalid alarm time (over 15s)
    pid = create(test_alarm_process, 2048, 20, "test2b", 1, 16000);
    resume(pid);
    
    sleepms(500);
*/

/*
    // Test 3: Error conditions
    XINUTEST_PRINT("\nTest 3: Error conditions\n");
    
    // Create process with multiple alarms time
    pid = create(multiple_alarms_process, 2048, 20, "test3a", 2, 500, 1000);
    resume(pid);
    
    sleepms(500);

*/    

    // Bonus (b) Test: Error conditions
    XINUTEST_PRINT("\nBonus (b) Test\n");
    
    // Create process with multiple alarms time
    pid = create(bonus_multiple_alarms_process, 2048, 20, "bonusTest", 2, 500, 1000);
    resume(pid);
    
    sleepms(500);

	
    return OK;
}