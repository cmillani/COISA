.text
.align 2
.globl send_byte
.globl configure_ultrassonic
.globl serial_configure
.globl printnum
.globl print

send_byte:
	li		$v0, 12		# $v0 = 11
	li		$v1, 10		# $a0 = 1
	la 		$t4, rxtxID
	syscall 
	jr		$31					# jump to $31
	
read_byte:
	li		$v0, 12		# $v0 = 12
	li		$v1, 11		# $a0 = 1
	la 		$t4, rxtxID
	syscall 
	jr		$31					# jump to $31

serial_configure:
	li		$v0, 12		# $v0 = 11
	li		$v1, 12		# $a0 = 1
	la 		$t4, rxtxID
	syscall 
	jr		$31					# jump to $31
printnum:
	li		$v0, 12		# $v0 = 11
	li		$v1, 13		# $a0 = 1
	la 		$t4, rxtxID
	syscall 
	jr		$31					# jump to $31
print:
	li		$v0, 12		# $v0 = 11
	li		$v1, 14		# $a0 = 1
	la 		$t4, rxtxID
	syscall 
	jr		$31					# jump to $31
	
.data
rxtxID: .asciiz "RXTX"
