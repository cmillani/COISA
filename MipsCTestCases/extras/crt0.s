.globl	ev_handler
.globl	_start
.align	2
.section .crto0

_start:	
	li	$v0, 11
	syscall
	li	$v0, 9
	li	$v1, ev_handler
	syscall
	jal	main
	li	$v0, 10
	syscall
	
ev_handler:
	li	$v0, 11
	syscall
	li	$ra, event_end
	jr	$a0
	
event_end:
	li	$v0, 10
	syscall
	