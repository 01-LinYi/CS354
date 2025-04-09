#include <xinu.h>


void mysender(pid32 receiver, umsg32 msg)
{
    // Sleep a bit to make sure receiver is set up
    sleepms(300);
    
    // Send message to receiver
    if(send(receiver, msg) == SYSERR)
    {
        XINUTEST_PRINT("Sender (PID %d) failed to send message to PID %d\n", 
                currpid, receiver);
        return;
    }
    

    XINUTEST_PRINT("Sender (PID %d) sent message %u to PID %d\n", 
            currpid, msg, receiver);
    
    
    // Infinite loop to keep process alive
    while(1)
    {
        // Simulate CPU-bound work
        int i,sum=0;
        for(i=0;i<1000000;i++)
            sum += i;
        
        // Sleep periodically to give other processes a chance
        sleepms(500);
    }
}