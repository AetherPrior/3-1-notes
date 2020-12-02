.data
    array: .word 52, 21, 111, 10, 100, 43, 2
    space: .asciiz " "
    size: .word 7
.text
main: 			
sort_prep:
    la $t0, array 		# load array to $t0.
    lw $t1, size 		# load array size to $t1.
    li $t2, 1 			# loop runner, starting from 1.
sort_xloop:
    la $t0, array 			# load array to $t0.
    bge $t2, $t1, sort_xloop_end 		# while (t2 < $t1).
    move $t3, $t2		 	# copy $t2 to $t3.	
    sort_iloop:
        la $t0, array 			# load array to $t0.
        mul $t5, $t3, 4 			# multiply $t3 with 4, and store in $t5
        add $t0, $t0, $t5 			# add the array address with $t5, which is the index multiplied with 4.
        ble $t3, $zero, sort_iloop_end 	# while (t3 > 0).
        lw $t7, 0($t0) 			#load array[$t3] to $t7.
        lw $t6, -4($t0) 			# load array[$t3 - 1] to $t6.
        bge $t7, $t6, sort_iloop_end 		# while (array[$t3] < array[$t3 - 1]).
        lw $t4, 0($t0)
        sw $t6, 0($t0)
        sw $t4, -4($t0)
        subi $t3, $t3, 1
        j sort_iloop 	# jump back to the beginning of the sort_iloop.
    sort_iloop_end:
    addi $t2, $t2, 1	 # increment loop runner by 1.
    j sort_xloop 		# jump back to the beginning of the sort_xloop.
sort_xloop_end:     
    la $t0, array
    li $t2,0 		#as a counter while printing the list
    jal print

li $v0, 10
syscall 

print:
    lw $a0,($t0) 	#load current word in $a0
    li $v0,1
    syscall
    la $a0,space
    li $v0,4
    syscall
    addi $t0,$t0,4
    addi $t2,$t2,1
    blt $t2,$t1,print

    jr $ra