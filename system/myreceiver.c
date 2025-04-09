#include <xinu.h>

// Global message buffer
umsg32 mbuffer;


void mymsghandler(void)
{
    mbuffer = receive();  

    // Print receive information
    XINUTEST_PRINT("receive %d %u %u\n", currpid, clkcounterfine, mbuffer);
}


void myreceiver(void)
{
    // Register callback function
    if (registercbk(&mymsghandler) != OK)
    {
        XINUTEST_PRINT("Registration failed.\n");
        return;
    }
    
    XINUTEST_PRINT("Receiver (PID %d) registered callback\n", currpid);
    
    // Sleep to allow other processes to run
    sleepms(200);
    
    // Infinite loop to keep process alive
    while(1)
    {
        // Simulate CPU-bound work
        int i,sum=0;
        for(i=0;i<1000000;i++)
            sum += i;
        
        // Sleep periodically to give other processes a chance
        sleepms(500);
        
        XINUTEST_PRINT("Receiver (PID %d) still running, last msg: %u\n", 
                currpid, mbuffer);
    }
}