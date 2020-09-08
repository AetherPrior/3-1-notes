 
.data
input1: .asciiz "Enter val1: "
input2: .asciiz "Enter val2: "
output1: .asciiz "Max is: "
output2: .asciiz "Min is: "

.text
main:
    la $a0, input1
    li $v0,4
    syscall
    
    li $v0,6 #Accept floating point
    syscall
    mov.s $f1,$f0
    
    la $a0, input2
    li $v0,4
    syscall
    
    li $v0,6
    syscall
    mov.s $f2,$f0
    
    c.lt.s $f1,$f2
    bc1f ifblock
    mov.s $f4,$f2
    j exit
    
    ifblock:
        mov.s $f4, $f1
    
    exit:
        la $a0, output1
        li $v0,4
        syscall
        
        mov.s $f12,$f4
        li $v0, 2
        syscall
    
    c.le.s $f1,$f2
    bc1t ifblock1
    mov.s $f4,$f2
    j exit1
    
    ifblock1:
        mov.s $f4,$f1
    exit1:
        la $a0, output2
        li $v0, 4
        syscall
        
        mov.s $f12, $f4
        li $v0,2
        syscall
    
    li $v0, 10
    syscall
    
