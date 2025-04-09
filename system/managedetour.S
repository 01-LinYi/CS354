/* managedetour.S - managedetour */

        .text
        .globl  managedetour


managedetour:
        /* Get process table entry for current process */
        movl    currpid, %eax
        imull   $68, %eax            /* Size of struct procent = 68 bytes */
        addl    $proctab, %eax       /* Add base address of proc table */
        
        /* Get callback function pointer */
        movl    60(%eax), %ecx       /* prrecvcbk is at offset 60 */
        
        /* Get original return address and store in register */
        movl    64(%eax), %edx       /* prsleepret is at offset 64 */
        
        /* Call the callback function */
        pushl   %edx                 /* Save original return addr */
        call    *%ecx                /* Call the callback function */
        popl    %edx                 /* Restore original return addr */
        
        /* Replace our return address with the original one */
        movl    %edx, (%esp)         /* Put original return addr on stack */
        
        ret                          /* Return to original caller */