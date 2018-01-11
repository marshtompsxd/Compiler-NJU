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
  li $t0, 30
  sw $t0, -136($fp)
  li $t0, 0
  sw $t0, -132($fp)
  li $t0, 1
  sw $t0, -128($fp)
  li $t0, 1
  sw $t0, -124($fp)
label1:
  lw $t0, -124($fp)
  lw $t1, -136($fp)
  ble $t0, $t1, label2
  j label3
label2:
label4:
  lw $t0, -128($fp)
  lw $t1, -124($fp)
  ble $t0, $t1, label5
  j label6
label5:
  lw $t0, -124($fp)
  lw $t1, -128($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -80($fp)
  lw $t0, -80($fp)
  lw $t1, -128($fp)
  mul $t2, $t0, $t1
  sw $t2, -84($fp)
  lw $t0, -124($fp)
  lw $t1, -84($fp)
  beq $t0, $t1, label7
  j label8
label7:
  lw $t0, -132($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -64($fp)
  lw $t0, -64($fp)
  sw $t0, -132($fp)
label8:
  lw $t0, -128($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -52($fp)
  lw $t0, -52($fp)
  sw $t0, -128($fp)
  j label4
label6:
  lw $t0, -132($fp)
  li $t1, 2
  beq $t0, $t1, label9
  j label10
label9:
  lw $t0, -124($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
label10:
  li $t0, 1
  sw $t0, -128($fp)
  li $t0, 0
  sw $t0, -132($fp)
  lw $t0, -124($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -124($fp)
  j label1
label3:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 128
  addi $sp, $sp, 8
  jr $ra

