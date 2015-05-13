.text
.align 2
.globl read_ultrassonic
.globl configure_ultrassonic

read_ultrassonic:
	li		$v0, 12		# $v0 = 11
	li		$a0, 0		# $a0 = 1
	syscall 
	jr		$31					# jump to $31
	
configure_ultrassonic:
	li		$v0, 12		# $v0 = 11
	li		$a0, 1		# $a0 = 1
	syscall 
	jr		$31					# jump to $31
