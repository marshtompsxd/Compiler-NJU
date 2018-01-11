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
  subu $sp, $sp, 268
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -268($fp)
  lw $t0, -268($fp)
  sw $t0, -272($fp)
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -264($fp)
  lw $t0, -264($fp)
  sw $t0, -276($fp)
  lw $t0, -272($fp)
  li $t1, 100
  div $t0, $t1
  mflo $t2
  sw $t2, -252($fp)
  lw $t0, -252($fp)
  li $t1, 100
  mul $t2, $t0, $t1
  sw $t2, -256($fp)
  lw $t0, -272($fp)
  lw $t1, -256($fp)
  beq $t0, $t1, label1
  j label2
label1:
  lw $t0, -272($fp)
  li $t1, 400
  div $t0, $t1
  mflo $t2
  sw $t2, -228($fp)
  lw $t0, -228($fp)
  li $t1, 400
  mul $t2, $t0, $t1
  sw $t2, -232($fp)
  lw $t0, -272($fp)
  lw $t1, -232($fp)
  beq $t0, $t1, label4
  j label5
label4:
  lw $t0, -276($fp)
  li $t1, 2
  beq $t0, $t1, label7
  j label8
label7:
  li $t0, 29
  sw $t0, -204($fp)
  lw $t0, -204($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label9
label8:
  lw $t0, -276($fp)
  li $t1, 2
  div $t0, $t1
  mflo $t2
  sw $t2, -192($fp)
  lw $t0, -192($fp)
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -196($fp)
  lw $t0, -276($fp)
  lw $t1, -196($fp)
  beq $t0, $t1, label10
  j label11
label10:
  li $t0, 30
  sw $t0, -176($fp)
  lw $t0, -176($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label12
label11:
  li $t0, 31
  sw $t0, -172($fp)
  lw $t0, -172($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
label12:
label9:
  j label6
label5:
  lw $t0, -276($fp)
  li $t1, 2
  beq $t0, $t1, label13
  j label14
label13:
  li $t0, 28
  sw $t0, -160($fp)
  lw $t0, -160($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label15
label14:
  lw $t0, -276($fp)
  li $t1, 2
  div $t0, $t1
  mflo $t2
  sw $t2, -148($fp)
  lw $t0, -148($fp)
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -152($fp)
  lw $t0, -276($fp)
  lw $t1, -152($fp)
  beq $t0, $t1, label16
  j label17
label16:
  li $t0, 30
  sw $t0, -132($fp)
  lw $t0, -132($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label18
label17:
  li $t0, 31
  sw $t0, -128($fp)
  lw $t0, -128($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
label18:
label15:
label6:
  j label3
label2:
  lw $t0, -272($fp)
  li $t1, 4
  div $t0, $t1
  mflo $t2
  sw $t2, -116($fp)
  lw $t0, -116($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -120($fp)
  lw $t0, -272($fp)
  lw $t1, -120($fp)
  beq $t0, $t1, label19
  j label20
label19:
  lw $t0, -276($fp)
  li $t1, 2
  beq $t0, $t1, label22
  j label23
label22:
  li $t0, 29
  sw $t0, -92($fp)
  lw $t0, -92($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label24
label23:
  lw $t0, -276($fp)
  li $t1, 2
  div $t0, $t1
  mflo $t2
  sw $t2, -80($fp)
  lw $t0, -80($fp)
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -84($fp)
  lw $t0, -276($fp)
  lw $t1, -84($fp)
  beq $t0, $t1, label25
  j label26
label25:
  li $t0, 30
  sw $t0, -64($fp)
  lw $t0, -64($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label27
label26:
  li $t0, 31
  sw $t0, -60($fp)
  lw $t0, -60($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
label27:
label24:
  j label21
label20:
  lw $t0, -276($fp)
  li $t1, 2
  beq $t0, $t1, label28
  j label29
label28:
  li $t0, 28
  sw $t0, -48($fp)
  lw $t0, -48($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label30
label29:
  lw $t0, -276($fp)
  li $t1, 2
  div $t0, $t1
  mflo $t2
  sw $t2, -36($fp)
  lw $t0, -36($fp)
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -40($fp)
  lw $t0, -276($fp)
  lw $t1, -40($fp)
  beq $t0, $t1, label31
  j label32
label31:
  li $t0, 30
  sw $t0, -20($fp)
  lw $t0, -20($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  j label33
label32:
  li $t0, 31
  sw $t0, -16($fp)
  lw $t0, -16($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
label33:
label30:
label21:
label3:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 268
  addi $sp, $sp, 8
  jr $ra

