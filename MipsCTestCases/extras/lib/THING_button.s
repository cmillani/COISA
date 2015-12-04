.text
.align 2
.globl init_button

init_button:
	li		$v0, 12		# $v0 = 12
	li		$v1, 21		# $a0 = 15
	la 		$t4, btogID
	syscall 
	jr		$31					# jump to $31

.data	
btogID: .asciiz "BTOG"
	