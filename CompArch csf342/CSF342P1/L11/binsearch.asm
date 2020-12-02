## binsearch
.data
array: .word 1,4,7,10,15
arraySize: .word 5
msg: .asciiz "Enter the number that you want to search for:\n"
.text
main:
	li $v0,4
	la $a0,msg
	syscall
	
	li $v0,5
	syscall
	
	move $t5, $v0
	la $s0, array
	
	xor $a0, $a0, $a0
	lw $a1, arraySize
	jal search
	##retval in $a0
	li $v0,1
	syscall
	
	li $v0,10
	syscall
	
search:
	blt $a1, $a0, notfound
	add $t1, $a0, $a1
	sra $t1, $t1, 1
	## mid in $t2
	mul $t2, $t1, 4 ## *(int*)(arr+mid)
	add $t2, $t2, $s0
	
	lw $t2, 0($t2)
	beq $t2, $t5, found
	blt $t2, $t5, left #t2 less than 
	
right:	move $a1, $t1
	sub $a1, $a1, 1 #right = mid-1
	j search
left:	
	move $a0, $t1 #left = mid+1
	add $a0, $a0, 1 
	j search
notfound:
	li $a0,-1
	jr $ra
found:
	move $a0, $t1
	jr $ra
	
	
	
