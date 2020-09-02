.data
val1: .float 2.1
val2: .float 4.35

dv: .double 2.5
dv2: .double 7.1
.text
main:
	l.s $f1,val1
	l.s $f2, val2  
	add.s $f12,$f1,$f2
	#li $v0,2
	#syscall
	
	l.d $f0,dv
	l.d $f2, dv2
	add.d $f12,$f0,$f2
	#li $v0,3
	#syscall	
	
	l.d $f0,dv2
	l.d $f2,dv
	sub.d $f14,$f0,$f2
	neg.d $f2, $f2
	add.d $f12,$f0,$f2
	li $v0,3
	syscall
	
	mov.d $f12,$f14
	li $v0,3
	syscall
	
	l.s $f0,val2
	l.s $f1,val1
	sub.s $f13,$f0,$f1
	neg.s $f1, $f1
	add.s $f12,$f0,$f1
	li $v0,2
	syscall
	
	mov.s $f12, $f13
	li $v0,2
	syscall
	
	li $v0,10
	syscall
	
	
	
	