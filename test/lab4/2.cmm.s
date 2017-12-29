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

fact:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 72
  sw $a0, -80($fp)
  lw $t0, -80($fp)
  li $t1, 1
  beq $t0, $t1, label1
  j label2
label1:
  lw $v0, -80($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 72
  addi $sp, $sp, 8
  jr $ra
  j label3
label2:
  lw $t0, -80($fp)
  sw $t0, -48($fp)
  lw $t0, -80($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -40($fp)
  lw $t0, -40($fp)
  move $a0, $t0
  jal fact
  sw $v0, -44($fp)
  lw $ra, -4($fp)
  lw $t0, -48($fp)
  lw $t1, -44($fp)
  mul $t2, $t0, $t1
  sw $t2, -52($fp)
  lw $v0, -52($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 72
  addi $sp, $sp, 8
  jr $ra
label3:

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 72
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -28($fp)
  lw $t0, -28($fp)
  sw $t0, -76($fp)
  lw $t0, -76($fp)
  li $t1, 1
  bgt $t0, $t1, label4
  j label5
label4:
  lw $t0, -76($fp)
  move $a0, $t0
  jal fact
  sw $v0, -16($fp)
  lw $ra, -4($fp)
  lw $t0, -16($fp)
  sw $t0, -72($fp)
  j label6
label5:
  li $t0, 1
  sw $t0, -72($fp)
label6:
  lw $t0, -72($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 72
  addi $sp, $sp, 8
  jr $ra

