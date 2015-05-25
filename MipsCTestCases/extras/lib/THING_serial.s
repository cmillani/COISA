.text
.align 2
.globl send_byte
.globl configure_ultrassonic
.globl serial_configure

send_byte:
	li		$v0, 12		# $v0 = 11
	li		$a0, 10		# $a0 = 1
	syscall 
	jr		$31					# jump to $31
	
read_byte:
	li		$v0, 12		# $v0 = 12
	li		$a0, 11		# $a0 = 1
	syscall 
	jr		$31					# jump to $31

serial_configure:
	li		$v0, 12		# $v0 = 11
	li		$a0, 12		# $a0 = 1
	syscall 
	jr		$31					# jump to $31