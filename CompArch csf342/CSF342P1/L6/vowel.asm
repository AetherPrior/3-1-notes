.data
	rets: .space 6
	str: .asciiz "hello"
	
	str1: .asciiz "world"
	
	vow: .asciiz "aeiou"
.text
	main:
		la $a0,str
		la $a1,rets
		jal vowel
		
		move $a0,$v0
		jal print_count
		
		la $a0,rets
		jal print_str
		
		la $a0,str1
		jal vowel
		
		move $a0,$v0
		jal print_count
		
		la $a0, rets
		jal print_str
		
		li $v0,10
		syscall
	vowel:
		add $sp, $sp, -16
		sw $ra, ($sp)
		sw $a0, 4($sp)
		sw $a1, 8($sp)
		
		move $t0,$a0
		move $t3,$a1
		li $s0,0
		
		loop:
			lb $t1, ($t0)
			
			sb $t1,12($sp)
			move $a0,$t1
			jal check_vow
			lb $t1,12($sp)
		
			beq $v0,2,endloop #end of loop
			beq $v0,1,addc#did match
		
			sb $t1,($t3)
			add $t3,$t3,1
			j cont
		addc:
			addi $s0,$s0,1
		cont:
			addi $t0, $t0,1
			j loop
	
	endloop:
		li $t1,0
		sb $t1,($t3) #null terminator
		
		lw $a1, 8($sp)	
		lw $a0, 4($sp)	
		lw $ra, ($sp)
		add $sp, $sp, 16
		move $v0, $s0
		jr $ra
	
	check_vow:
		li $t2,0
		beq $a0,0,end3
		loop2:
			beq $t2,5,end2
			lb $t1, vow+0($t2)
			beq $a0,$t1,end #match
			add $t2,$t2,1
			j loop2
		end: #match
			li $v0,1
			jr $ra
		end2: #dnm
			li $v0,0
			jr $ra
		end3: #eof
			li $v0,2
			jr $ra 
		
	print_count:
		li $v0,1
		syscall
		jr $ra
	print_str:
		li $v0,4
		syscall	
		jr $ra	
			
			
			
		
		
		
		
		
		
		
		
		
		
		
		
		
				