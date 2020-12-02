#2018A7PS0172H
#Abhinav Sukumar Rao
#+91-9087260821
#f20180172@hyderabad.bits-pilani.ac.in
.data
msg1: .asciiz "Enter a: "
msg2: .asciiz "Enter b: "
output: .asciiz "Final value of a: "
cmp: .double 0.01
.text
main:
	la $a0, msg1
	li $v0,4
	syscall
	li $v0, 7
	syscall
	mov.d $f2,$f0 #f2 has a
	la $a0, msg2
	li $v0,4
	syscall
	li $v0, 7
	syscall
		#f0 has b
	l.d $f10, cmp
divloop:
	c.le.d  $f2, $f10
	bc1t res
	div.d $f2, $f2, $f0
	j divloop
res:
	la $a0, output
	li $v0, 4
	syscall
	
	mov.d $f12,$f2 
	li $v0,3
	syscall
	
	li $v0,10
	syscall
	
	
	