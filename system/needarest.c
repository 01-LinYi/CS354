#include <xinu.h>

void needarest(void)
{
    XINUTEST_PRINT("Need a rest\n");
    sleepms(500);


    // If wrongturn175() is successful, the code below will never execute.
    while(1)
    {
        XINUTEST_PRINT("Rested and ready\n");
        sleepms(500);
    }
}