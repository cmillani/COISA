.text
.align 2
.globl read_encoder_counter
.globl read_encoder_time
.globl start_encoder

read_encoder_counter:
	li		$v0, 12		# $v0 = 11
	li		$v1, 5		# $a0 = 0
	la 		$t4, encdID
	syscall 
	jr		$31					# jump to $31
	
read_encoder_time:
	li		$v0, 12		# $v0 = 11
	li		$v1, 6		# $a0 = 0
	la 		$t4, encdID
	syscall 
	jr		$31					# jump to $31

start_encoder:
	li		$v0, 12		# $v0 = 11
	li		$v1, 7		# $a0 = 0
	la 		$t4, encdID
	syscall 
	jr		$31					# jump to $31

.data
encdID: .asciiz "ENCD"
