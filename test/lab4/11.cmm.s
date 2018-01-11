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

squaRever:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 384
  lw $t0, 0($fp)
  sw $t0, -392($fp)
  li $t0, 0
  sw $t0, -388($fp)
  li $t0, 0
  sw $t0, -372($fp)
  li $t0, -384
  add $t0, $t0, $fp
  sw $t0, -348($fp)
  lw $t0, -348($fp)
  sw $t0, -356($fp)
  lw $t0, -392($fp)
  li $t1, 100
  div $t0, $t1
  mflo $t2
  sw $t2, -336($fp)
  lw $t0, -336($fp)
  lw $t1, -356($fp)
  sw $t0, 0($t1)
  li $t0, -384
  add $t0, $t0, $fp
  sw $t0, -316($fp)
  lw $t0, -316($fp)
  li $t1, 4
  add $t2, $t0, $t1
  sw $t2, -308($fp)
  lw $t0, -308($fp)
  sw $t0, -324($fp)
  lw $t0, -392($fp)
  li $t1, 10
  div $t0, $t1
  mflo $t2
  sw $t2, -300($fp)
  li $t0, -384
  add $t0, $t0, $fp
  sw $t0, -268($fp)
  lw $t0, -268($fp)
  sw $t0, -276($fp)
  lw $t0, -276($fp)
  lw $t0, 0($t0)
  sw $t0, -280($fp)
  li $t0, 10
  lw $t1, -280($fp)
  mul $t2, $t0, $t1
  sw $t2, -296($fp)
  lw $t0, -300($fp)
  lw $t1, -296($fp)
  sub $t2, $t0, $t1
  sw $t2, -304($fp)
  lw $t0, -304($fp)
  lw $t1, -324($fp)
  sw $t0, 0($t1)
  li $t0, -384
  add $t0, $t0, $fp
  sw $t0, -248($fp)
  lw $t0, -248($fp)
  li $t1, 8
  add $t2, $t0, $t1
  sw $t2, -240($fp)
  lw $t0, -240($fp)
  sw $t0, -256($fp)
  li $t0, -384
  add $t0, $t0, $fp
  sw $t0, -200($fp)
  lw $t0, -200($fp)
  sw $t0, -208($fp)
  lw $t0, -208($fp)
  lw $t0, 0($t0)
  sw $t0, -212($fp)
  li $t0, 100
  lw $t1, -212($fp)
  mul $t2, $t0, $t1
  sw $t2, -220($fp)
  lw $t0, -392($fp)
  lw $t1, -220($fp)
  sub $t2, $t0, $t1
  sw $t2, -232($fp)
  li $t0, -384
  add $t0, $t0, $fp
  sw $t0, -172($fp)
  lw $t0, -172($fp)
  li $t1, 4
  add $t2, $t0, $t1
  sw $t2, -164($fp)
  lw $t0, -164($fp)
  sw $t0, -180($fp)
  lw $t0, -180($fp)
  lw $t0, 0($t0)
  sw $t0, -184($fp)
  li $t0, 10
  lw $t1, -184($fp)
  mul $t2, $t0, $t1
  sw $t2, -228($fp)
  lw $t0, -232($fp)
  lw $t1, -228($fp)
  sub $t2, $t0, $t1
  sw $t2, -236($fp)
  lw $t0, -236($fp)
  lw $t1, -256($fp)
  sw $t0, 0($t1)
  li $t0, -384
  add $t0, $t0, $fp
  sw $t0, -144($fp)
  lw $t0, -144($fp)
  sw $t0, -152($fp)
  lw $t0, -152($fp)
  lw $t0, 0($t0)
  sw $t0, -160($fp)
  li $t0, -384
  add $t0, $t0, $fp
  sw $t0, -124($fp)
  lw $t0, -124($fp)
  li $t1, 8
  add $t2, $t0, $t1
  sw $t2, -116($fp)
  lw $t0, -116($fp)
  sw $t0, -132($fp)
  lw $t0, -132($fp)
  lw $t0, 0($t0)
  sw $t0, -156($fp)
  lw $t0, -160($fp)
  lw $t1, -156($fp)
  bne $t0, $t1, label1
  j label2
label1:
  li $t0, 0
  sw $t0, -388($fp)
  j label3
label2:
label4:
  lw $t0, -372($fp)
  li $t1, 12
  blt $t0, $t1, label5
  j label6
label5:
  lw $t0, -372($fp)
  lw $t1, -372($fp)
  mul $t2, $t0, $t1
  sw $t2, -92($fp)
  lw $t0, -92($fp)
  lw $t1, -392($fp)
  sub $t2, $t0, $t1
  sw $t2, -100($fp)
  lw $t0, -100($fp)
  li $t1, 0
  beq $t0, $t1, label7
  j label8
label7:
  li $t0, 1
  sw $t0, -388($fp)
label8:
  lw $t0, -372($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -72($fp)
  lw $t0, -72($fp)
  sw $t0, -372($fp)
  j label4
label6:
label3:
  lw $t0, -388($fp)
  li $t1, 1
  beq $t0, $t1, label9
  j label10
label9:
  li $v0, 1
  lw $fp, -8($fp)
  addi $sp, $sp, 384
  addi $sp, $sp, 8
  jr $ra
  j label11
label10:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 384
  addi $sp, $sp, 8
  jr $ra
label11:

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 384
  li $t0, 100
  sw $t0, -368($fp)
label12:
  lw $t0, -368($fp)
  li $t1, 150
  blt $t0, $t1, label13
  j label14
label13:
  subu $sp, $sp, 4
  lw $t0, -368($fp)
  sw $t0, 0($sp)
  jal squaRever
  sw $v0, -32($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 4
  lw $t0, -32($fp)
  li $t1, 1
  beq $t0, $t1, label15
  j label16
label15:
  lw $t0, -368($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
label16:
  lw $t0, -368($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -368($fp)
  j label12
label14:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 384
  addi $sp, $sp, 8
  jr $ra

