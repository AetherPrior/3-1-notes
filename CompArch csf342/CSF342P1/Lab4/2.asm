
.data
    even: .asciiz "Even"
    odd: .asciiz "Odd"
.text
main:
li $v0,5
syscall

move $t0,$v0
 
li $t1, 2
div $t0, $t1
mfhi $t0

#Find max $t0 and $t1
beqz $t0, ifblock

la $a0, odd
li $v0,4
syscall
bnez $t0, exit

ifblock:
la $a0, even
li $v0,4
syscall

exit:
li $v0,10
syscall


