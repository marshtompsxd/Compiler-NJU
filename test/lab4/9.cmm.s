.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

hanoi:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 128
  lw $t0, 0($fp)
  sw $t0, -136($fp)
  lw $t0, 4($fp)
  sw $t0, -132($fp)
  lw $t0, 8($fp)
  sw $t0, -128($fp)
  lw $t0, 12($fp)
  sw $t0, -124($fp)
  lw $t0, -136($fp)
  li $t1, 1
  beq $t0, $t1, label1
  j label2
label1:
  lw $t0, -132($fp)
  li $t1, 1000000
  mul $t2, $t0, $t1
  sw $t2, -104($fp)
  lw $t0, -104($fp)
  lw $t1, -124($fp)
  add $t2, $t0, $t1
  sw $t2, -108($fp)
  lw $t0, -108($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label3
label2:
  lw $t0, -136($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -88($fp)
  subu $sp, $sp, 16
  lw $t0, -128($fp)
  sw $t0, 12($sp)
  lw $t0, -124($fp)
  sw $t0, 8($sp)
  lw $t0, -132($fp)
  sw $t0, 4($sp)
  lw $t0, -88($fp)
  sw $t0, 0($sp)
  jal hanoi
  sw $v0, -76($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 16
  lw $t0, -132($fp)
  li $t1, 1000000
  mul $t2, $t0, $t1
  sw $t2, -68($fp)
  lw $t0, -68($fp)
  lw $t1, -124($fp)
  add $t2, $t0, $t1
  sw $t2, -72($fp)
  lw $t0, -72($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -136($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -52($fp)
  subu $sp, $sp, 16
  lw $t0, -124($fp)
  sw $t0, 12($sp)
  lw $t0, -132($fp)
  sw $t0, 8($sp)
  lw $t0, -128($fp)
  sw $t0, 4($sp)
  lw $t0, -52($fp)
  sw $t0, 0($sp)
  jal hanoi
  sw $v0, -40($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 16
label3:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 128
  addi $sp, $sp, 8
  jr $ra

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 128
  li $t0, 3
  sw $t0, -120($fp)
  li $t0, 1
  sw $t0, -28($fp)
  li $t0, 2
  sw $t0, -24($fp)
  li $t0, 3
  sw $t0, -20($fp)
  subu $sp, $sp, 16
  lw $t0, -20($fp)
  sw $t0, 12($sp)
  lw $t0, -24($fp)
  sw $t0, 8($sp)
  lw $t0, -28($fp)
  sw $t0, 4($sp)
  lw $t0, -120($fp)
  sw $t0, 0($sp)
  jal hanoi
  sw $v0, -16($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 16
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 128
  addi $sp, $sp, 8
  jr $ra

