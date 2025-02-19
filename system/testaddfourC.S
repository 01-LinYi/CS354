        .text
        .globl  testaddfourC

testaddfourC:
        pushl   $2
        pushl   $2
        pushl   $3
        pushl   $2

        call    addfourC

        addl    $16, %esp
        
        ret