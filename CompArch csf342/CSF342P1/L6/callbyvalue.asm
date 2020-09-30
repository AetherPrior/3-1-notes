# a0, a1,a2,a3
# OR
# f12,f14,stack,stack
# callee saves frame ptr, t0-t7, s0-s7 (and ra, if not a leaf procedure i.e. not recursive or no nested procedure)
# jal -> jump and link, moves PC to RA
# return values in v0-v1
# jr $ra
.data 
	line: .asciiz "\n"
	str:  .asciiz "value of $a0: "
.text
	main:
		li $a0, 10
		la $a1, str
		la $a2, line
		jal inc_val #do a0 += 10
		
		jal print_val #print after restoring
		
		li $v0,10 #exit
		syscall
	inc_val:
		# create a stack frame
		addi $sp, $sp, -8
		sw $a0,($sp) #call by value, so the actual register contents don't change later
		sw $ra, 4($sp) # non leaf function call
		addi $a0, $a0, 10 #a0+=10
		
		jal print_val #print the value
		
		lw $a0,($sp)	#restore value of a0
		lw $ra,4($sp) #restore return value
		addi $sp, $sp, 8 #restore the sp
		
		jr $ra
		
	print_val:
		#create a stack frame
		addi $sp, $sp, -8
		sw $a0,($sp)
		sw $ra, 4($sp)
		#print the string
		move $a0,$a1
		li $v0, 4
		syscall
		#print the value
		lw $a0,($sp)
		li $v0,1
		syscall
		#newline
		jal newl
		#restore
		lw $a0,($sp)
		lw $ra, 4($sp)
		addi $sp,$sp,8
		
		jr $ra
	newl:
		add $sp,$sp, -4
		sw $a0,($sp)
		
		la $a0, line
		li $v0,4
		syscall
		
		lw $a0,($sp)
		add $sp,$sp,4
		
		jr $ra	
		
		
		
		
		
		
		
		
		
		
		
			
		