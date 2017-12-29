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
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  li $t0, 0
  sw $t0, 0($gp)
  li $t0, 1
  sw $t0, 4($gp)
  li $t0, 0
  sw $t0, 8($gp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $t0, $v0
  sw $t0, 36($gp)
  lw $t0, 36($gp)
  sw $t0, 12($gp)
label1:
  lw $t0, 8($gp)
  lw $t1, 12($gp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, 0($gp)
  lw $t1, 4($gp)
  add $t2, $t0, $t1
  sw $t2, 48($gp)
  lw $t0, 48($gp)
  sw $t0, 16($gp)
  lw $t0, 4($gp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, 4($gp)
  sw $t0, 0($gp)
  lw $t0, 16($gp)
  sw $t0, 4($gp)
  lw $t0, 8($gp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, 68($gp)
  lw $t0, 68($gp)
  sw $t0, 8($gp)
  j label1
label3:
  li $v0, 0
  jr $ra

