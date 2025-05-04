/* clkdisp.S - clkdisp (x86) */

/*------------------------------------------------------------------------
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */
#include <icu.s>
        .text
        .globl  clkdisp         # Clock interrupt dispatcher
        .globl  makedetouralrm  # Import the detour flag
        .globl  currpid         # Import current process ID
        .globl  proctab         # Import process table

/* Constants */
#define PRCBSZ  68      /* Size of procent structure */
#define PRCBOFF 60      /* Offset of prcbf in procent */

clkdisp:
        # Normal interrupt handling
        pushal
        pushfl
        cli
        movb    $EOI,%al
        outb    %al,$OCW1_2

        call    clkhandler

        # Check if we need to call the callback
        movw    makedetouralrm, %ax
        testw   %ax, %ax
        jz      skip_callback

        # Reset the flag
        movw    $0, makedetouralrm

        # Get the callback function
        movl    currpid, %eax
        imull   $PRCBSZ, %eax
        addl    $proctab, %eax
        movl    PRCBOFF(%eax), %ebx  # Callback function ptr

        # Call the callback directly
        call    *%ebx

skip_callback:
        # Normal return
        popfl
        popal
        iret