.text
.align 2
.globl send_byte
.globl configure_ultrassonic

send_byte:
	li		$v0, 12		# $v0 = 11
	li		$a0, 10		# $a0 = 1
	syscall 
	jr		$31					# jump to $31
	
read_byte:
	li		$v0, 12		# $v0 = 11
	li		$a0, 11		# $a0 = 1
	syscall 
	jr		$31					# jump to $31
