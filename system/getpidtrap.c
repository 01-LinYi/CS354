#include <xinu.h>

pid32 getpidtrap(void)
{
    pid32 ret;
    
    __asm__ volatile (
        "movl %1, %%edx \n\t" /* Put system call number (20) in EDX */
        "int $35 \n\t"  /* Trap to kernel via interrupt 35 */
        : "=a"(ret) /* EAX holds the return value */
        : "r"(SYS_getpid) /* Input operand */
        : "edx" /* Clobbered register */
    );

    return ret;
}