.data 
    int1: .word 123
    int2: .word 234
    ma: .asciiz "Max is: "
    mi: .asciiz "Min is: "  
    newl: .asciiz "\n" 
.text
main:
    lw $t1, int1
    lw $t2, int2

    bge $t1,$t2, ifblock
    move $t0,$t2
    blt $t1,$t2, exit

    ifblock:
        move $t0,$t1

    exit:
        la $a0,ma
        li $v0,4 
        syscall

    move $a0, $t0 
    li $v0,1
    syscall
    
    la $a0,newl 
    li $v0,4
    syscall
    
    
    #Minimum
    
    ble $t1,$t2, ifblock1
    move $t0, $t2
    bgt $t1,$t2,exit2
    
    ifblock1:
        move $t0, $t1
    
    exit2:
        la $a0, mi
        li $v0,4
        syscall
        
        move $a0, $t0
        li $v0,1
        syscall
        
        
    li $v0, 10
    syscall
