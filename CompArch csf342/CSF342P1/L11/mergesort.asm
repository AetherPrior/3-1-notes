.data
array: .word 1,2,3,6,4
arraySize: .word 5
c: .word 0:100 
main:
	la $a0, array
	addi $a1, $0, 0
	addi $a2, $0, 4
	jal mergesort
	#la $a0, sorted_array #nah 

	jal Print #print array
	
	li $v0, 10
	syscall
	
mergesort:
	blt $a1, $a2, ret
	
	addi $sp, $sp, -16 
	sw $ra, 12($sp)
	sw $a1, 8($sp)
	sw $a2, 4($sp)
	
	add $s0, $a1, $a2
	sra $s0, $s0, 1
	sw $s0, 0($sp) 
	
	## stored ra, left, right, mid
	
	#high = mid
	add $a2, $s0, $zero
	
	jal mergesort
	
	#restore from stack
	lw $s0, 0($sp)
	lw $a2, 4($sp)
	lw $a1, 8($sp)
	
	#low = mid+1
	add $a1, $s0, 1
	jal mergesort
	
	#restore from stack again
	#restore from stack
	lw $a3, 0($sp) #A3 IS NOW MID
	lw $a2, 4($sp)
	lw $a1, 8($sp)
	
	jal merge #merge em together
	
	lw $ra, 12($sp)
	addi $sp, $sp , 16
ret:
	jr $ra
	
merge:
	#we have two arrays now
	#we need to merge em
	#keep a new location for array 'c'
	add $s0, $a1, $0 #low i
	add $s1, $a1, $0 #low k
	add $s2, $a3, 1 #mid+1 j
	
while1:
	blt $a3, $s0, while2
	blt $a2, $s2, while2 #we don't want a far jump :P, we goto while3 from while2 RIP
	j if

if:	
	sll $t0, $s0, 2		#conversion to word from byte
	add $t0, $t0 , $a0 	#a0 is base
	lw  $t1, 0($t0) #load *(int*)(a+i)value
	sll $t2, $s2,2  
	add $t2, $t2, $a0 # (int*)(a+j)
	lw $t3, 0($t2) #dereference
	
	la $t4, c 
	sll $t5, $s1, 2
	add $t4, $t4, $t5 #c[k]
	
	blt $t3, $t1, else #A[j] < A[i]
	
    sw $t1, 0($t4) #c[k] = a[i]
    addi $s1, $s1, 1 #k++
    addi $s0, $s0, 1 #i++
    j while1
else:
    #t3 stored
    sw $t3, 0($t4) #c[k] = a[i]
    addi $s1, $s1, 1
    addi $s2, $s2, 1 #j++
    j while1
    
while2:
	##copycontents
	blt $a3, $a0, while3 #if mid < i
	sll $t0, $s0, 2		# # $t0 = i*4
	add $t0, $a0, $t0	# add offset to the address of a[0]; now $t0 = address of a[i]
	
	lw $t1, 0($t0)		# load value of a[i] into $t7
	la  $t2, c		    # Get start address of c
	sll $t3, $s1, 2     # k*4
	add $t3, $t3, $t2	# $t3 = c[k]
	sw $t1, 0($t3) 		# saving $t1 (value of a[i]) into address of $t3, which is c[k]
	addi $s1, $s1, 1   	# k++
	addi $s0, $s0, 1   	# i++
	j while2		# Go to next iteration
	
while3:
    ##copycontents again
    blt  $a2,  $s1, For_Initializer	#if high < j then go to For loop
	sll $t2, $s2, 2    	# $t2 = j*4
	add $t2, $t2, $a0  	# add offset to the address of a[0]; now $t2 = address of a[j]
	lw $t3, 0($t2)     	# $t2 = value in a[j]
	
	la  $t4, c		# Get start address of c
	sll $t5, $s1, 2	   	# k*4
	add $t4, $t4, $t5  	# $t4 is address of c[k]
	sw $t3, 0($t4)     	# $t3 => c[k];
	addi $s1, $s1, 1   	# k++
	addi $s2, $s2, 1   	# j++
	j While3		# Go to next iteration

For_Initializer:
	add  $t0, $a1, $zero	# t0 = low
	addi $t1, $a2, 1 	# t1 = high+1
	la   $t4, c		# t4 = c	
	j    For
For:
	bge $t0, $t1, sortEnd	# if t0 >= t1, go to sortEnd
	sll $t2, $t0, 2   	# ptr offset now in $t2 ptr from low to high+1
	add $t3, $t2, $a0	# add the offset to the address of a => a[ptr]
	add $t5, $t2, $t4	# add the offset to the address of c => c[ptr]
	lw  $t6, 0($t5)		# loads value of c[i] into $t6
	sw $t6, 0($t3)   	# a[i] = c[i]
	addi $t0, $t0, 1 	# increment $t0 by 1 for the i++ part of For loop
	j For 			# Go to next iteration
	
sortEnd:
	jr $ra			# return to calling routine		
Print:
	add $t0, $a1, $zero 	# initialize $t0 to low
	add $t1, $a2, $zero	# initialize $t1 to high
	la  $t4, array2		# load the address of the array into $t4
	
Print_Loop:
	blt  $t1, $t0, Exit	# if $t1 < $t0, go to exit
	sll  $t3, $t0, 2	# $t0 * 4 to get the offset
	add  $t3, $t3, $t4	# add the offset to the address of array to get array[$t3]
	lw   $t2, 0($t3)	# load the value at array[$t0] to $t2
	move $a0, $t2		# move the value to $a0 for printing
	li   $v0, 1		# the MIPS call for printing the numbers
	syscall
	
	addi $t0, $t0, 1	# increment $t0 by 1 for the loop 
	la   $a0, Space		# prints a comma and space between the numbers
	li   $v0, 4		# MIPS call to print a prompt
	syscall
	j    Print_Loop		# Go to next iteration of the loop
	
Exit:
	jr $ra			# jump to the address in $ra; Go back to main
	
