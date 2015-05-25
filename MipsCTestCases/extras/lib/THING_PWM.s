.text
.align 2
.globl set_PWM

set_PWM:
	li		$v0, 12		# $v0 = 11
	li		$a0, 20		# $a0 = 1
	syscall 
	jr		$31					# jump to $31