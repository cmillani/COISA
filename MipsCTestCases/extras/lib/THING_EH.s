.text
.align 2
.globl eh_init
.globl register_handler
.globl remove_handler

eh_init:
	li		$v0, 13		# $v0 = 12
	syscall 
	jr		$31					# jump to $31

register_handler:
	li		$v0, 14		# $v0 = 12
	syscall 
	jr		$31					# jump to $31

remove_handler:
	li		$v0, 15		# $v0 = 12
	syscall 
	jr		$31					# jump to $31

.data
