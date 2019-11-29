	.text
	.globl	main
main:

	move $fp, $sp
	subu $sp, $sp, 60
	sw $ra, -4($fp)
	
	li $v1, 8
	move $s0 $v1
	move $a0 $s0 
	jal _halloc 
	move $s0 $v0 
	move $s0 $s0
	
	li $v1, 4
	move $s1 $v1
	move $a0 $s1 
	jal _halloc 
	move $s1 $v0

	la $s2, MT4_Change
	sw $s2, 4($s0)
	la $s2, MT4_Start
	sw $s2, 0($s0)
	sw $s0, 0($s1)

	move $s1 $s1
	
	lw $s0, 0($s1) 
	lw $s0, 0($s0) 

	li $s2, 1
	li $s3, 2
	li $s4, 3
	li $s5, 4
	li $s6, 5
	li $s7, 6
	sw $t0, 12($sp)
	sw $t1, 16($sp)
	sw $t2, 20($sp)
	sw $t3, 24($sp)
	sw $t4, 28($sp)
	sw $t5, 32($sp)
	sw $t6, 36($sp)
	sw $t7, 40($sp)
	sw $t8, 44($sp)
	sw $t9, 48($sp)
	move $a0 $s1
	move $a1 $s2
	move $a2 $s3
	move $a3 $s4
	sw $s5, 0($sp)
	sw $s6, 4($sp)
	sw $s7, 8($sp)
	jalr $s0
	lw $t0, 12($sp)
	lw $t1, 16($sp)
	lw $t2, 20($sp)
	lw $t3, 24($sp)
	lw $t4, 28($sp)
	lw $t5, 32($sp)
	lw $t6, 36($sp)
	lw $t7, 40($sp)
	lw $t8, 44($sp)
	lw $t9, 48($sp)
	move $s7 $v0
	move $a0 $s7
	jal _print
	lw $ra, -4($fp)
	addu $sp, $sp, 60
	jr $ra

	.text
	.globl	MT4_Start
MT4_Start:

	sw $fp, -8($sp)
	move $fp, $sp
	subu $sp, $sp, 92
	sw $ra, -4($fp)
	sw $s0, 24($sp)
	sw $s1, 28($sp)
	sw $s2, 32($sp)
	sw $s3, 36($sp)
	sw $s4, 40($sp)
	sw $s5, 44($sp)
	sw $s6, 48($sp)
	sw $s7, 52($sp)
	move $s0 $a0
	move $s1 $a1
	move $s2 $a2
	move $s3 $a3
	move $a0 $s1
	jal _print
	move $a0 $s2
	jal _print
	move $a0 $s3
	jal _print
	lw $v1, 0($fp)
	move $a0 $v1
	jal _print
	lw $v1, 4($fp)
	move $a0 $v1
	jal _print
	lw $v1, 8($fp)
	move $a0 $v1
	jal _print
	
	move $s0 $s0
	lw $s4, 0($s0) 
	lw $s4, 4($s4) 
	sw $t0, 56($sp)
	sw $t1, 60($sp)
	sw $t2, 64($sp)
	sw $t3, 68($sp)
	sw $t4, 72($sp)
	sw $t5, 76($sp)
	sw $t6, 80($sp)
	sw $t7, 84($sp)
	sw $t8, 88($sp)
	sw $t9, 92($sp)
	move $a0 $s0
	lw $v0, 8($fp)
	move $a1 $v0
	lw $v0, 4($fp)
	move $a2 $v0
	lw $v0, 0($fp)
	move $a3 $v0
	sw $s3, 0($sp)
	sw $s2, 4($sp)
	sw $s1, 8($sp)
	jalr $s4
	lw $t0, 56($sp)
	lw $t1, 60($sp)
	lw $t2, 64($sp)
	lw $t3, 68($sp)
	lw $t4, 72($sp)
	lw $t5, 76($sp)
	lw $t6, 80($sp)
	lw $t7, 84($sp)
	lw $t8, 88($sp)
	lw $t9, 92($sp)
	move $s4 $v0
	move $s4 $s4
	move $v0 $s4
	lw $s0, 24($sp)
	lw $s1, 28($sp)
	lw $s2, 32($sp)
	lw $s3, 36($sp)
	lw $s4, 40($sp)
	lw $s5, 44($sp)
	lw $s6, 48($sp)
	lw $s7, 52($sp)
	lw $ra, -4($fp)
	lw $fp, 84($sp)
	addu $sp, $sp, 92
	j $ra

	.text
	.globl	MT4_Change
MT4_Change:

	sw $fp, -8($sp)
	move $fp, $sp
	subu $sp, $sp, 40
	sw $ra, -4($fp)
	sw $s0, 12($sp)
	sw $s1, 16($sp)
	sw $s2, 20($sp)
	sw $s3, 24($sp)
	sw $s4, 28($sp)
	sw $s5, 32($sp)
	sw $s6, 36($sp)
	sw $s7, 40($sp)
	move $v1 $a0
	move $s0 $a1
	move $s1 $a2
	move $s2 $a3
	move $a0 $s0
	jal _print
	move $a0 $s1
	jal _print
	move $a0 $s2
	jal _print
	lw $v1, 0($fp)
	move $a0 $v1
	jal _print
	lw $v1, 4($fp)
	move $a0 $v1
	jal _print
	lw $v1, 8($fp)
	move $a0 $v1
	jal _print

	li $v1, 0
	move $s2 $v1
	move $v0 $s2
	lw $s0, 12($sp)
	lw $s1, 16($sp)
	lw $s2, 20($sp)
	lw $s3, 24($sp)
	lw $s4, 28($sp)
	lw $s5, 32($sp)
	lw $s6, 36($sp)
	lw $s7, 40($sp)
	lw $ra, -4($fp)
	lw $fp, 32($sp)
	addu $sp, $sp, 40
	j $ra

	.text
	.globl _halloc
_halloc:
	li $v0, 9
	syscall
	jr $ra

	.text
	.globl _print
_print:
	li $v0, 1
	syscall
	la $a0, newl
	li $v0, 4
	syscall
	jr $ra

	.data
	.align   0
newl:   .asciiz "\n" 
	.data
	.align   0
str_er:  .asciiz " ERROR: abnormal termination\n" 
