.text
.align 2
.globl ahead
.globl turn_left
.globl turn_right

ahead:
	li		$v0, 12		# $v0 = 12
	li		$v1, 15		# $a0 = 15
	la 		$t4, movmID
	syscall 
	jr		$31					# jump to $31
	
turn_right:
	li		$v0, 12		# $v0 = 12
	li		$v1, 16		# $a0 = 16
	la 		$t4, movmID
	syscall 
	jr		$31					# jump to $31

turn_left:
	li		$v0, 12		# $v0 = 12
	li		$v1, 17		# $a0 = 17
	la 		$t4, movmID
	syscall 
	jr		$31					# jump to $31
setup_movement:
	li		$v0, 12		# $v0 = 12
	li		$v1, 18		# $a0 = 18
	la 		$t4, movmID
	syscall 
	jr		$31					# jump to $31
	
movmID: .asciiz "MOVM"
	