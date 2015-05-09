	.globl	_start
	.align	2
	.section .crto0
_start:	
	li	$v0, 11
	syscall
	jal	main
	li	$v0, 10
	syscall      
