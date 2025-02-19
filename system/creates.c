#include <xinu.h>

pid32 creates(void (*procaddr)(void), char arg)
{
    int32 child_priority;
    pid32 pid;

    child_priority = proctab[currpid].prprio + 1;

    kputc(arg);
    kprintf("%d\n", child_priority);

    pid=create(procaddr, PROCSTACKSZ, child_priority, "NONAME", 1, arg);

    return pid;
}