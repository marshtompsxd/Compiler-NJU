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
  subu $sp, $sp, 80
  li $t0, 0
  sw $t0, -88($fp)
  li $t0, 1
  sw $t0, -84($fp)
  li $t0, 0
  sw $t0, -80($fp)
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -52($fp)
  lw $t0, -52($fp)
  sw $t0, -76($fp)
label1:
  lw $t0, -80($fp)
  lw $t1, -76($fp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -88($fp)
  lw $t1, -84($fp)
  add $t2, $t0, $t1
  sw $t2, -40($fp)
  lw $t0, -40($fp)
  sw $t0, -72($fp)
  lw $t0, -84($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -84($fp)
  sw $t0, -88($fp)
  lw $t0, -72($fp)
  sw $t0, -84($fp)
  lw $t0, -80($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -20($fp)
  lw $t0, -20($fp)
  sw $t0, -80($fp)
  j label1
label3:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 80
  addi $sp, $sp, 8
  jr $ra

