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
  subu $sp, $sp, 44
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -48($fp)
  lw $t0, -48($fp)
  sw $t0, -52($fp)
  lw $t0, -52($fp)
  li $t1, 0
  bgt $t0, $t1, label1
  j label2
label1:
  li $t0, 1
  sw $t0, -36($fp)
  lw $t0, -36($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label3
label2:
  lw $t0, -52($fp)
  li $t1, 0
  blt $t0, $t1, label4
  j label5
label4:
  li $t0, -1
  sw $t0, -24($fp)
  lw $t0, -24($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label6
label5:
  li $t0, 0
  sw $t0, -16($fp)
  lw $t0, -16($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
label6:
label3:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 44
  addi $sp, $sp, 8
  jr $ra

