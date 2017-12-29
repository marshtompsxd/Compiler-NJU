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
  sw $a0, 0($gp)
  lw $t0, 0($gp)
  li $t1, 1
  beq $t0, $t1, label1
  j label2
label1:
  lw $v0, 0($gp)
  jr $ra
  j label3
label2:
  lw $t0, 0($gp)
  sw $t0, 32($gp)
  lw $t0, 0($gp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, 40($gp)
