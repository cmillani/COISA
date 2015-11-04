.text
.align 2
.globl set_PWM

set_PWM:
	li		$v0, 12		# $v0 = 11
	li		$v1, 20		# $a0 = 1
	la 		$t4, pwmID
	syscall 
	jr		$31					# jump to $31

.data	
pwmID: .asciiz "PWMG"
