.text
.align 2
.globl read_encoder_counter
.globl read_encoder_time

read_encoder_counter:
	li		$v0, 12		# $v0 = 11
	li		$a0, 5		# $a0 = 0
	syscall 
	jr		$31					# jump to $31
	
read_encoder_time:
	li		$v0, 12		# $v0 = 11
	li		$a0, 6		# $a0 = 0
	syscall 
	jr		$31					# jump to $31
