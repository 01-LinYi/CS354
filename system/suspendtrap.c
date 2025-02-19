#include <xinu.h>

syscall suspendtrap(pid32 pid)
{
    syscall ret;

    __asm__ volatile (
        "movl %[pid], %%ebx \n\t" 
        "movl %[syscall], %%edx \n\t" /* Put system call number (23) in EDX */
        "int $35 \n\t"  /* Trap to kernel via interrupt 35 */
        : "=a"(ret)
        : [pid] "r" (pid),
          [syscall] "r" (SYS_suspend)  
        : "ebx", "edx"
    );

    return ret;
}