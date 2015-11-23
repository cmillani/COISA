main:
addiu	$sp,$sp,-4
sw	$ra,0($sp)
li	$v0, 12
li	$v1, 18
la	$t4, movmID
syscall
li	$v0, 12
li	$v1, 15
la	$t4, movmID
syscall
li	$v0, 12
li	$v1, 16
la	$t4, movmID
syscall
lw	$ra,0($sp)
addiu	$sp,$sp, 4
jr	$ra
