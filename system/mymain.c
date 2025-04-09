#include <xinu.h>

#define TEST_ONE_SENDER 1     // Test with one sender
#define TEST_TWO_SENDERS 0    // Test with two senders

void mymain(void)
{
    /*XINUDEBUG_PRINT("Process table offsets:\n");
    XINUDEBUG_PRINT("- Size of struct procent: %d bytes\n", sizeof(struct procent));
    XINUDEBUG_PRINT("- Offset of prrecvcbk: %d bytes\n", 
            (uint32)&((struct procent*)0)->prrecvcbk);
    XINUDEBUG_PRINT("- Offset of prsleepret: %d bytes\n", 
            (uint32)&((struct procent*)0)->prsleepret);*/


    pid32 rec_pid, send_pid1, send_pid2;
        
    // Create and run receiver process
    rec_pid = create(myreceiver, 1024, 20, "receiver", 0);
    resume(rec_pid);
    
    // Test with one sender
    if(TEST_ONE_SENDER)
    {
        // Create and run sender process
        send_pid1 = create(mysender, 1024, 20, "sender1", 2, rec_pid, 22);
        resume(send_pid1);
    }
    
    /* Test with two senders */
    if(TEST_TWO_SENDERS)
    {
        // Wait before starting second sender
        sleepms(1000);
        
        // Create and run second sender process
        send_pid2 = create(mysender, 1024, 20, "sender2", 2, rec_pid, 44);
        resume(send_pid2);
    }
    
    // Keep the main process alive
    while(1)
        sleepms(5000);
}