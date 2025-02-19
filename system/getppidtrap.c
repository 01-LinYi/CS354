#include <xinu.h>

pid32 getppidtrap(pid32 pid)
{
    pid32 ret;

    __asm__ volatile (
        "movl %[pid], %%ebx \n\t" 
        "movl %[syscall], %%edx \n\t" /* Put system call number (21) in EDX */
        "int $35 \n\t"  /* Trap to kernel via interrupt 35 */
        : "=a"(ret)
        : [pid] "r" (pid),
          [syscall] "r" (SYS_getppid)  
        : "ebx", "edx"
    );

    return ret;
}