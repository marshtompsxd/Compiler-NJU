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

Josepy:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 672
  lw $t0, 0($fp)
  sw $t0, -680($fp)
  lw $t0, 4($fp)
  sw $t0, -676($fp)
  li $t0, 1
  sw $t0, -272($fp)
  li $t0, 0
  sw $t0, -268($fp)
  li $t0, 0
  sw $t0, -264($fp)
  li $t0, 0
  sw $t0, -260($fp)
label1:
  lw $t0, -272($fp)
  lw $t1, -680($fp)
  ble $t0, $t1, label2
  j label3
label2:
  li $t0, -672
  add $t0, $t0, $fp
  sw $t0, -216($fp)
  lw $t0, -272($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -212($fp)
  lw $t0, -216($fp)
  lw $t1, -212($fp)
  add $t2, $t0, $t1
  sw $t2, -208($fp)
  lw $t0, -208($fp)
  sw $t0, -224($fp)
  li $t0, 1
  sw $t0, -204($fp)
  lw $t0, -204($fp)
  lw $t1, -224($fp)
  sw $t0, 0($t1)
  lw $t0, -272($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -200($fp)
  lw $t0, -200($fp)
  sw $t0, -272($fp)
  j label1
label3:
  li $t0, 1
  sw $t0, -272($fp)
label4:
  lw $t0, -272($fp)
  lw $t1, -680($fp)
  ble $t0, $t1, label5
  j label6
label5:
  li $t0, -672
  add $t0, $t0, $fp
  sw $t0, -160($fp)
  lw $t0, -272($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -156($fp)
  lw $t0, -160($fp)
  lw $t1, -156($fp)
  add $t2, $t0, $t1
  sw $t2, -152($fp)
  lw $t0, -152($fp)
  sw $t0, -168($fp)
  lw $t0, -168($fp)
  lw $t0, 0($t0)
  sw $t0, -176($fp)
  lw $t0, -176($fp)
  li $t1, 1
  beq $t0, $t1, label7
  j label8
label7:
  li $t0, -672
  add $t0, $t0, $fp
  sw $t0, -128($fp)
  lw $t0, -272($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -124($fp)
  lw $t0, -128($fp)
  lw $t1, -124($fp)
  add $t2, $t0, $t1
  sw $t2, -120($fp)
  lw $t0, -120($fp)
  sw $t0, -136($fp)
  lw $t0, -136($fp)
  lw $t0, 0($t0)
  sw $t0, -140($fp)
  lw $t0, -268($fp)
  lw $t1, -140($fp)
  add $t2, $t0, $t1
  sw $t2, -148($fp)
  lw $t0, -148($fp)
  sw $t0, -268($fp)
  lw $t0, -268($fp)
  lw $t1, -676($fp)
  beq $t0, $t1, label9
  j label10
label9:
  lw $t0, -272($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  li $t0, 0
  sw $t0, -268($fp)
  li $t0, -672
  add $t0, $t0, $fp
  sw $t0, -96($fp)
  lw $t0, -272($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -92($fp)
  lw $t0, -96($fp)
  lw $t1, -92($fp)
  add $t2, $t0, $t1
  sw $t2, -88($fp)
  lw $t0, -88($fp)
  sw $t0, -104($fp)
  li $t0, 0
  sw $t0, -84($fp)
  lw $t0, -84($fp)
  lw $t1, -104($fp)
  sw $t0, 0($t1)
  lw $t0, -264($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -80($fp)
  lw $t0, -80($fp)
  sw $t0, -264($fp)
label10:
  lw $t0, -264($fp)
  lw $t1, -680($fp)
  beq $t0, $t1, label11
  j label12
label11:
  lw $t0, -272($fp)
  sw $t0, -260($fp)
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 672
  addi $sp, $sp, 8
  jr $ra
label12:
label8:
  lw $t0, -272($fp)
  lw $t1, -680($fp)
  beq $t0, $t1, label13
  j label14
label13:
  li $t0, 0
  sw $t0, -272($fp)
label14:
  lw $t0, -272($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -40($fp)
  lw $t0, -40($fp)
  sw $t0, -272($fp)
  j label4
label6:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 672
  addi $sp, $sp, 8
  jr $ra

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 672
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -256($fp)
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -20($fp)
  lw $t0, -20($fp)
  sw $t0, -252($fp)
  subu $sp, $sp, 8
  lw $t0, -252($fp)
  sw $t0, 4($sp)
  lw $t0, -256($fp)
  sw $t0, 0($sp)
  jal Josepy
  sw $v0, -16($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 8
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 672
  addi $sp, $sp, 8
  jr $ra

