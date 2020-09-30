.data 
	str: .asciiz "Fact: "
.text
	main:
		li $a0,8
		li $a1,1
		jal fact
		#v0 has value now
		move $a0,$v0
		jal print_str
		li $v0,10
		syscall
		
	fact:
		addi $sp,$sp,-12
		sw  $a0,($sp)
		sw $a1,4($sp)
		sw $ra,8($sp) 
		
		beq $a0,0,end
		mul $a1,$a0,$a1
		addi $a0,$a0,-1
		jal fact
		j ret
	end:
		move $v0, $a1
	ret:
		lw $ra,8($sp)
		lw $a1, 4($sp)
		lw $a0,($sp)
		add $sp,$sp,12
		jr $ra
		
	print_str:
		addi $sp,$sp,-4
		sw $a0,($sp)
		
		la $a0, str
		li $v0,4 
		syscall
		
		lw $a0,($sp)
		li $v0,1
		syscall
		
		jr $ra
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
