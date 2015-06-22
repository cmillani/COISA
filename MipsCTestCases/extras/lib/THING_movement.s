.text
.align 2
.globl ahead
.globl turn_left
.globl turn_right

ahead:
	li		$v0, 12		# $v0 = 11
	li		$v1, 15		# $a0 = 1
	syscall 
	jr		$31					# jump to $31
	
turn_right:
	li		$v0, 12		# $v0 = 11
	li		$v1, 16		# $a0 = 1
	syscall 
	jr		$31					# jump to $31

turn_left:
	li		$v0, 12		# $v0 = 11
	li		$v1, 17		# $a0 = 1
	syscall 
	jr		$31					# jump to $31
