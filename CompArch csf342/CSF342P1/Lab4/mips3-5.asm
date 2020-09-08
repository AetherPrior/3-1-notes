.data
	int1: .word 10051
	int2: .word 98712
	str: .asciiz "\n"
.text
main:
	lw $t1, int1
	lw $t2, int2
	
	#B

	mul $a0, $t1,$t2
	move $a1,$a0
#####################################3
#PRINT INTEGER
	li $v0,1
	syscall

	la $a0, str
	li $v0,4
	syscall	
	##########################33
	
	
	#C
	mtc1 $t1,$f1
	mtc1 $t2,$f2
	cvt.s.w $f1,$f1
	cvt.s.w $f2,$f2

	mul.s $f12,$f1,$f2
	
	#############################33
	#PRINT FLOAT
	li $v0,2
	syscall

	la $a0, str
	li $v0,4
	syscall
	#################################
	
	#D
	cvt.w.s $f12, $f12

	mfc1 $a0, $f12 
    move $a2,$a0
	###################################33
#PRINT INTEGER
	li $v0,1
	syscall

	la $a0, str
	li $v0,4
	syscall
########################################
	
	
	#Difference
	#####################################
	sub $a0, $a1,$a2
	li $v0, 1
	syscall
	
	la $a0, str
	li $v0,4
	syscall
	####################################
	#E
	lw $t1, int1
	lw $t2, int2
	mtc1 $t1,$f0
	mtc1 $t2,$f2

	cvt.d.w $f0,$f0
	cvt.d.w $f2,$f2

	mul.d $f12, $f0, $f2
	li $v0,3
	syscall
    la $a0, str
	li $v0,4
	syscall	
	#F
	cvt.w.d $f12, $f12
	mfc1 $a3, $f12
	move $a0, $a3
	li $v0,1
	syscall
	
    la $a0, str
	li $v0,4
	syscall

	sub $a0, $a3, $a1
	li $v0,1
	syscall
	
    la $a0, str
	li $v0,4
	syscall
	
	#G 
	sub $a0, $a3, $a2
	li $v0,1
	syscall
	
	li $v0,10
	syscall
