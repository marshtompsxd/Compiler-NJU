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

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 128
  li $t0, 0
  sw $t0, -124($fp)
  li $t0, 5
  sw $t0, -136($fp)
  lw $t0, -136($fp)
  lw $t1, -136($fp)
  mul $t2, $t0, $t1
  sw $t2, -108($fp)
  lw $t0, -136($fp)
  li $t1, 2
  add $t2, $t0, $t1
  sw $t2, -104($fp)
  lw $t0, -108($fp)
  lw $t1, -104($fp)
  mul $t2, $t0, $t1
  sw $t2, -112($fp)
  lw $t0, -112($fp)
  sw $t0, -132($fp)
  lw $t0, -132($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -132($fp)
  lw $t1, -136($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -80($fp)
  lw $t0, -80($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -84($fp)
  lw $t0, -84($fp)
  sw $t0, -128($fp)
  lw $t0, -128($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -136($fp)
  lw $t1, -132($fp)
  add $t2, $t0, $t1
  sw $t2, -52($fp)
  lw $t0, -128($fp)
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -48($fp)
  lw $t0, -52($fp)
  lw $t1, -48($fp)
  sub $t2, $t0, $t1
  sw $t2, -60($fp)
  lw $t0, -132($fp)
  lw $t1, -136($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -28($fp)
  lw $t0, -28($fp)
  li $t1, 4
  sub $t2, $t0, $t1
  sw $t2, -56($fp)
  lw $t0, -60($fp)
  lw $t1, -56($fp)
  add $t2, $t0, $t1
  sw $t2, -64($fp)
  lw $t0, -64($fp)
  sw $t0, -124($fp)
  lw $t0, -124($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 128
  addi $sp, $sp, 8
  jr $ra

