.data
	int1: .word 10051
	int2: .word 98712
.text
main:
	lw $t1, int1
	lw $t2, int2
	mul $a0, $t1,$t2
	li $v0,1
	syscall
	
	move $a1,$a0
	
	mtc1 $t1,$f1
	mtc1 $t2,$f2
	cvt.s.w $f1,$f1
	cvt.s.w $f2,$f2

	mul.s $f12,$f1,$f2
	
	
	li $v0,2
	syscall
			
	li $v0,10
	syscall