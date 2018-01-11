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
  subu $sp, $sp, 176
  lw $t0, 0($fp)
  sw $t0, -184($fp)
  li $t0, 1
  sw $t0, -180($fp)
  li $t0, 1
  sw $t0, -176($fp)
label1:
  lw $t0, -176($fp)
  lw $t1, -184($fp)
  ble $t0, $t1, label2
  j label3
label2:
  lw $t0, -180($fp)
  lw $t1, -176($fp)
  mul $t2, $t0, $t1
  sw $t2, -128($fp)
  lw $t0, -128($fp)
  sw $t0, -180($fp)
  lw $t0, -176($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -116($fp)
  lw $t0, -116($fp)
  sw $t0, -176($fp)
  j label1
label3:
  lw $v0, -180($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 176
  addi $sp, $sp, 8
  jr $ra

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 176
  li $t0, 0
  sw $t0, -152($fp)
  li $t0, 5
  sw $t0, -148($fp)
label4:
  lw $t0, -152($fp)
  lw $t1, -148($fp)
  blt $t0, $t1, label5
  j label6
label5:
  li $t0, -172
  add $t0, $t0, $fp
  sw $t0, -76($fp)
  lw $t0, -152($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -72($fp)
  lw $t0, -76($fp)
  lw $t1, -72($fp)
  add $t2, $t0, $t1
  sw $t2, -68($fp)
  lw $t0, -68($fp)
  sw $t0, -84($fp)
  lw $t0, -152($fp)
  li $t1, 2
  add $t2, $t0, $t1
  sw $t2, -64($fp)
  lw $t0, -64($fp)
  lw $t1, -84($fp)
  sw $t0, 0($t1)
  li $t0, -172
  add $t0, $t0, $fp
  sw $t0, -36($fp)
  lw $t0, -152($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -32($fp)
  lw $t0, -36($fp)
  lw $t1, -32($fp)
  add $t2, $t0, $t1
  sw $t2, -28($fp)
  lw $t0, -28($fp)
  sw $t0, -44($fp)
  lw $t0, -44($fp)
  lw $t0, 0($t0)
  sw $t0, -48($fp)
  subu $sp, $sp, 4
  lw $t0, -48($fp)
  sw $t0, 0($sp)
  jal fact
  sw $v0, -52($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 4
  lw $t0, -52($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -152($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -152($fp)
  j label4
label6:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 176
  addi $sp, $sp, 8
  jr $ra

