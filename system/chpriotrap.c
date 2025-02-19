#include <xinu.h>

syscall chpriotrap(pid32 pid, pri16 newprio)
{
    syscall ret;
    uint32 newprio32 = (uint32)newprio; 

    __asm__ volatile (
        "movl %[pid], %%ebx \n\t"  
        "movl %[newprio], %%ecx \n\t"
        "movl %[syscall], %%edx \n\t" /* Put system call number (22) into EDX */
        "int $35 \n\t"   /* Trap to kernel via int $35 */
        : "=a"(ret)
        : [pid] "r" (pid),
          [newprio] "r" (newprio32),
          [syscall] "r" (SYS_chprio)
        : "ebx", "ecx", "edx"
    );

    return ret;
}