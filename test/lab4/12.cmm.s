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

mod:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 456
  lw $t0, 0($fp)
  sw $t0, -464($fp)
  lw $t0, 4($fp)
  sw $t0, -460($fp)
  lw $t0, -464($fp)
  lw $t1, -460($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -388($fp)
  lw $t0, -388($fp)
  lw $t1, -460($fp)
  mul $t2, $t0, $t1
  sw $t2, -392($fp)
  lw $t0, -464($fp)
  lw $t1, -392($fp)
  sub $t2, $t0, $t1
  sw $t2, -400($fp)
  lw $t0, -400($fp)
  sw $t0, -456($fp)
  lw $t0, -456($fp)
  sw $t0, -452($fp)
  lw $v0, -456($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 456
  addi $sp, $sp, 8
  jr $ra

power:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 456
  lw $t0, 0($fp)
  sw $t0, -448($fp)
  lw $t0, 4($fp)
  sw $t0, -444($fp)
  li $t0, 1
  lw $t1, -444($fp)
  add $t2, $t0, $t1
  sw $t2, -360($fp)
  lw $t0, -360($fp)
  lw $t1, -444($fp)
  sub $t2, $t0, $t1
  sw $t2, -364($fp)
  lw $t0, -364($fp)
  sw $t0, -440($fp)
label1:
  lw $t0, -440($fp)
  lw $t1, -440($fp)
  sub $t2, $t0, $t1
  sw $t2, -312($fp)
  lw $t0, -312($fp)
  li $t1, 90
  add $t2, $t0, $t1
  sw $t2, -320($fp)
  lw $t0, -320($fp)
  li $t1, 89
  sub $t2, $t0, $t1
  sw $t2, -328($fp)
  lw $t0, -328($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -336($fp)
  lw $t0, -336($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -340($fp)
  lw $t0, -444($fp)
  lw $t1, -340($fp)
  bgt $t0, $t1, label2
  j label3
label2:
  lw $t0, -440($fp)
  lw $t1, -448($fp)
  mul $t2, $t0, $t1
  sw $t2, -296($fp)
  lw $t0, -296($fp)
  sw $t0, -440($fp)
  li $t0, 2
  lw $t1, -444($fp)
  mul $t2, $t0, $t1
  sw $t2, -272($fp)
  lw $t0, -272($fp)
  lw $t1, -444($fp)
  sub $t2, $t0, $t1
  sw $t2, -280($fp)
  lw $t0, -280($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -284($fp)
  lw $t0, -284($fp)
  sw $t0, -444($fp)
  j label1
label3:
  lw $v0, -440($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 456
  addi $sp, $sp, 8
  jr $ra

getNumDigits:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 456
  lw $t0, 0($fp)
  sw $t0, -436($fp)
  li $t0, 0
  sw $t0, -432($fp)
  lw $t0, -436($fp)
  li $t1, 0
  blt $t0, $t1, label4
  j label5
label4:
  li $v0, -1
  lw $fp, -8($fp)
  addi $sp, $sp, 456
  addi $sp, $sp, 8
  jr $ra
label5:
label6:
  lw $t0, -436($fp)
  li $t1, 0
  bgt $t0, $t1, label7
  j label8
label7:
  lw $t0, -436($fp)
  li $t1, 10
  div $t0, $t1
  mflo $t2
  sw $t2, -208($fp)
  lw $t0, -208($fp)
  sw $t0, -436($fp)
  lw $t0, -432($fp)
  li $t1, 2
  add $t2, $t0, $t1
  sw $t2, -196($fp)
  lw $t0, -196($fp)
  sw $t0, -432($fp)
  lw $t0, -432($fp)
  li $t1, 2
  add $t2, $t0, $t1
  sw $t2, -184($fp)
  lw $t0, -184($fp)
  sw $t0, -432($fp)
  lw $t0, -432($fp)
  li $t1, 3
  sub $t2, $t0, $t1
  sw $t2, -172($fp)
  lw $t0, -172($fp)
  sw $t0, -432($fp)
  j label6
label8:
  lw $v0, -432($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 456
  addi $sp, $sp, 8
  jr $ra

isNarcissistic:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 456
  lw $t0, 0($fp)
  sw $t0, -428($fp)
  li $t0, 1
  lw $t1, -428($fp)
  add $t2, $t0, $t1
  sw $t2, -148($fp)
  lw $t0, -148($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -152($fp)
  subu $sp, $sp, 4
  lw $t0, -152($fp)
  sw $t0, 0($sp)
  jal getNumDigits
  sw $v0, -156($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 4
  lw $t0, -156($fp)
  sw $t0, -424($fp)
  li $t0, 0
  sw $t0, -420($fp)
  lw $t0, -428($fp)
  sw $t0, -416($fp)
label9:
  lw $t0, -416($fp)
  li $t1, 0
  bgt $t0, $t1, label10
  j label11
label10:
  li $t0, 10
  sw $t0, -112($fp)
  subu $sp, $sp, 8
  lw $t0, -112($fp)
  sw $t0, 4($sp)
  lw $t0, -416($fp)
  sw $t0, 0($sp)
  jal mod
  sw $v0, -116($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 8
  lw $t0, -116($fp)
  sw $t0, -412($fp)
  lw $t0, -416($fp)
  lw $t1, -412($fp)
  sub $t2, $t0, $t1
  sw $t2, -104($fp)
  lw $t0, -104($fp)
  li $t1, 10
  div $t0, $t1
  mflo $t2
  sw $t2, -108($fp)
  lw $t0, -108($fp)
  sw $t0, -416($fp)
  lw $t0, -420($fp)
  sw $t0, -84($fp)
  subu $sp, $sp, 8
  lw $t0, -424($fp)
  sw $t0, 4($sp)
  lw $t0, -412($fp)
  sw $t0, 0($sp)
  jal power
  sw $v0, -80($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 8
  lw $t0, -84($fp)
  lw $t1, -80($fp)
  add $t2, $t0, $t1
  sw $t2, -88($fp)
  lw $t0, -88($fp)
  sw $t0, -420($fp)
  j label9
label11:
  lw $t0, -420($fp)
  lw $t1, -428($fp)
  beq $t0, $t1, label12
  j label13
label12:
  li $v0, 1
  lw $fp, -8($fp)
  addi $sp, $sp, 456
  addi $sp, $sp, 8
  jr $ra
  j label14
label13:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 456
  addi $sp, $sp, 8
  jr $ra
label14:

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 456
  li $t0, 0
  sw $t0, -408($fp)
  li $t0, 300
  sw $t0, -404($fp)
label15:
  lw $t0, -404($fp)
  li $t1, 500
  blt $t0, $t1, label16
  j label17
label16:
  subu $sp, $sp, 4
  lw $t0, -404($fp)
  sw $t0, 0($sp)
  jal isNarcissistic
  sw $v0, -44($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 4
  lw $t0, -44($fp)
  li $t1, 1
  beq $t0, $t1, label18
  j label19
label18:
  lw $t0, -404($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -408($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -36($fp)
  lw $t0, -36($fp)
  sw $t0, -408($fp)
label19:
  lw $t0, -404($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -404($fp)
  j label15
label17:
  lw $t0, -408($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $v0, -408($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 456
  addi $sp, $sp, 8
  jr $ra

