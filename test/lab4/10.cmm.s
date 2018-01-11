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

gcd1:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 236
  lw $t0, 0($fp)
  sw $t0, -244($fp)
  lw $t0, 4($fp)
  sw $t0, -240($fp)
  lw $t0, -244($fp)
  lw $t1, -240($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -196($fp)
  lw $t0, -196($fp)
  lw $t1, -240($fp)
  mul $t2, $t0, $t1
  sw $t2, -200($fp)
  lw $t0, -244($fp)
  lw $t1, -200($fp)
  sub $t2, $t0, $t1
  sw $t2, -208($fp)
  lw $t0, -208($fp)
  sw $t0, -232($fp)
label1:
  lw $t0, -232($fp)
  li $t1, 0
  bne $t0, $t1, label2
  j label3
label2:
  lw $t0, -240($fp)
  sw $t0, -244($fp)
  lw $t0, -232($fp)
  sw $t0, -240($fp)
  lw $t0, -244($fp)
  lw $t1, -240($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -152($fp)
  lw $t0, -152($fp)
  lw $t1, -240($fp)
  mul $t2, $t0, $t1
  sw $t2, -156($fp)
  lw $t0, -244($fp)
  lw $t1, -156($fp)
  sub $t2, $t0, $t1
  sw $t2, -164($fp)
  lw $t0, -164($fp)
  sw $t0, -232($fp)
  j label1
label3:
  lw $t0, -240($fp)
  sw $t0, -236($fp)
  lw $v0, -236($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 236
  addi $sp, $sp, 8
  jr $ra

gcd2:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 236
  lw $t0, 0($fp)
  sw $t0, -228($fp)
  lw $t0, 4($fp)
  sw $t0, -224($fp)
  li $t0, 0
  sw $t0, -220($fp)
  lw $t0, -228($fp)
  lw $t1, -224($fp)
  bgt $t0, $t1, label4
  j label5
label4:
  lw $t0, -228($fp)
  lw $t1, -224($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -104($fp)
  lw $t0, -104($fp)
  lw $t1, -224($fp)
  mul $t2, $t0, $t1
  sw $t2, -108($fp)
  lw $t0, -228($fp)
  lw $t1, -108($fp)
  sub $t2, $t0, $t1
  sw $t2, -116($fp)
  lw $t0, -116($fp)
  sw $t0, -220($fp)
  lw $t0, -220($fp)
  li $t1, 0
  beq $t0, $t1, label7
  j label8
label7:
  lw $v0, -224($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 236
  addi $sp, $sp, 8
  jr $ra
  j label9
label8:
  subu $sp, $sp, 8
  lw $t0, -220($fp)
  sw $t0, 4($sp)
  lw $t0, -224($fp)
  sw $t0, 0($sp)
  jal gcd2
  sw $v0, -76($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 8
  lw $v0, -76($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 236
  addi $sp, $sp, 8
  jr $ra
label9:
  j label6
label5:
  lw $t0, -224($fp)
  lw $t1, -228($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -60($fp)
  lw $t0, -60($fp)
  lw $t1, -228($fp)
  mul $t2, $t0, $t1
  sw $t2, -64($fp)
  lw $t0, -224($fp)
  lw $t1, -64($fp)
  sub $t2, $t0, $t1
  sw $t2, -72($fp)
  lw $t0, -72($fp)
  sw $t0, -220($fp)
  lw $t0, -220($fp)
  li $t1, 0
  beq $t0, $t1, label10
  j label11
label10:
  lw $v0, -228($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 236
  addi $sp, $sp, 8
  jr $ra
  j label12
label11:
  subu $sp, $sp, 8
  lw $t0, -220($fp)
  sw $t0, 4($sp)
  lw $t0, -228($fp)
  sw $t0, 0($sp)
  jal gcd2
  sw $v0, -32($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 8
  lw $v0, -32($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 236
  addi $sp, $sp, 8
  jr $ra
label12:
label6:

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 236
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -28($fp)
  lw $t0, -28($fp)
  sw $t0, -216($fp)
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -212($fp)
  subu $sp, $sp, 8
  lw $t0, -212($fp)
  sw $t0, 4($sp)
  lw $t0, -216($fp)
  sw $t0, 0($sp)
  jal gcd1
  sw $v0, -20($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 8
  lw $t0, -20($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  subu $sp, $sp, 8
  lw $t0, -212($fp)
  sw $t0, 4($sp)
  lw $t0, -216($fp)
  sw $t0, 0($sp)
  jal gcd2
  sw $v0, -16($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 8
  lw $t0, -16($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 236
  addi $sp, $sp, 8
  jr $ra

