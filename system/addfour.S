/* Simple code to add four integers passed to addfour() coded
	in AT&T assembly. Assumes caller follows CDECL. */

        .text
        .globl addfour

addfour:
        pushl   %ebp
        movl    %esp,%ebp

        pushl   %ebx
        
        movl    8(%ebp),%eax
        movl    12(%ebp),%ebx
        movl    16(%ebp),%ecx
        movl    20(%ebp),%edx
        addl    %ebx,%eax
        addl    %ecx,%eax
        addl    %edx,%eax

        popl    %ebx

        popl    %ebp
        
        /*movl    (%esp),%ebp
        add     $4,%esp*/
        
        ret
