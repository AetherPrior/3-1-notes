.data

msgi: .asciiz "Enter a number: "
msgo: .asciiz "Sum till n: "

.text
main:
    la $a0, msgi 
    li $v0,4
    syscall
    
    li $v0,5
    syscall
    
    move $a0, $v0
    
    li $t1,1
    li $t0,0
loop:
    bgt $t1,$a0,exit
    add $t0,$t0,$t1
    add $t1,$t1,1
    j loop
exit:
    la $a0, msgo
    li $v0,4
    syscall
    
    move $a0,$t0
    li $v0,1
    syscall
    
    li $v0,10
    syscall
    
