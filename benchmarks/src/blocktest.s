li	$v0, 11
syscall
jal	main
li	$v0, 10
syscall
main:
addiu	$sp,$sp,-4
sw	$ra,0($sp)
li	$v0, 12
li	$v1, 18
syscall
addiu	$sp,$sp,-8
sw	$s0,0($sp)
sw	$s1,4($sp)
li	$s0,0
li	$s1,2
repeatloop_1:
bge	$s0,$s1,endrepeat_1
  li	$v0, 12
  li	$v1, 15
  syscall
  li	$v0, 12
  li	$v1, 17
  syscall
addiu	$s0, $s0, 1
j	repeatloop_1
endrepeat_1:
lw	$s1,4($sp)
lw	$s0,0($sp)
addiu	$sp, $sp, 8
lw	$ra,0($sp)
addiu	$sp,$sp, 4
jr	$ra
