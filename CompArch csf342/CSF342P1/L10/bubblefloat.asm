.data 
list: .double 17.2, 5.3, 92.21, 87.212, 41.1, 10.2, 23.1, 55.78, 72.05, 36.65
space: .asciiz " "
.text
main:
li $s7, 10
addi $s3, $s7,-1 #$s3 = stop = sz-1
## Loop swap code here
#s0 - curr
#s1 - next
#s2 - temp
#s3 - stop
outer_loop:
	xor $s0, $s0, $s0
	xor $s1,$s1, $s1
	#xor $s2, $s2, $s2
	beqz $s3, exit
	inner_loop:
		beq $s0, $s3, end_inloop
		addi $s1,$s0,1 
		
		#t2 - cur t3 - next t4- list t5, list[cur] , t6 - list[next] 
		move $t2,$s0 #t2 has offset of List(cur)
		move $t3,$s1 #t3 has offset of next
		sll $t2, $t2, 3 #make offset *8
		sll $t3,$t3,3 #make offset *8
		swap:	
			ldc1 $f0,list+0($t2)
			ldc1 $f2,list+0($t3)
			c.le.d $f0,$f2
			bc1f end_swap
			mov.d $f4, $f0
			mov.d $f0, $f2
			mov.d $f2, $f4
			sdc1 $f0, list+0($t2)
			sdc1 $f2, list+0($t3)
		end_swap:	
		addi $s0, $s0,1
		j inner_loop
	end_inloop:
	addi $s3, $s3, -1
	j outer_loop
exit: 
la $t0, list
li $t2, 0 #as a counter whle printing the list

print:
	ldc1 $f12,($t0) #load current word in $a0
	li $v0,3
	syscall		#print the current word
	la $a0, space
	li $v0,4
	syscall		#print space b/w words
	addi $t0,$t0,8	#pointer to next word
	addi $t2, $t2, 1#counter++
	blt $t2, $s7, print

li $v0,10
syscall
