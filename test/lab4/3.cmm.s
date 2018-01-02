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
  subu $sp, $sp, 368
  li $t0, 0
  sw $t0, -348($fp)
  li $t0, 5
  sw $t0, -344($fp)
  li $t0, 0
  sw $t0, -340($fp)
label1:
  lw $t0, -348($fp)
  li $t1, 5
  blt $t0, $t1, label2
  j label3
label2:
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -308($fp)
  lw $t0, -348($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -304($fp)
  lw $t0, -308($fp)
  lw $t1, -304($fp)
  add $t2, $t0, $t1
  sw $t2, -300($fp)
  lw $t0, -300($fp)
  sw $t0, -316($fp)
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -296($fp)
  lw $t0, -296($fp)
  lw $t1, -316($fp)
  sw $t0, 0($t1)
  lw $t0, -348($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -292($fp)
  lw $t0, -292($fp)
  sw $t0, -348($fp)
  j label1
label3:
  lw $t0, -344($fp)
  sw $t0, -348($fp)
label4:
  lw $t0, -348($fp)
  li $t1, 0
  bgt $t0, $t1, label5
  j label6
label5:
label7:
  lw $t0, -348($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -264($fp)
  lw $t0, -340($fp)
  lw $t1, -264($fp)
  blt $t0, $t1, label8
  j label9
label8:
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -236($fp)
  lw $t0, -340($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -232($fp)
  lw $t0, -236($fp)
  lw $t1, -232($fp)
  add $t2, $t0, $t1
  sw $t2, -228($fp)
  lw $t0, -228($fp)
  sw $t0, -244($fp)
  lw $t0, -244($fp)
  lw $t0, 0($t0)
  sw $t0, -252($fp)
  lw $t0, -340($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -220($fp)
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -216($fp)
  lw $t0, -220($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -212($fp)
  lw $t0, -216($fp)
  lw $t1, -212($fp)
  add $t2, $t0, $t1
  sw $t2, -208($fp)
  lw $t0, -208($fp)
  sw $t0, -224($fp)
  lw $t0, -224($fp)
  lw $t0, 0($t0)
  sw $t0, -248($fp)
  lw $t0, -252($fp)
  lw $t1, -248($fp)
  bgt $t0, $t1, label10
  j label11
label10:
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -184($fp)
  lw $t0, -340($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -180($fp)
  lw $t0, -184($fp)
  lw $t1, -180($fp)
  add $t2, $t0, $t1
  sw $t2, -176($fp)
  lw $t0, -176($fp)
  sw $t0, -192($fp)
  lw $t0, -192($fp)
  lw $t0, 0($t0)
  sw $t0, -196($fp)
  lw $t0, -196($fp)
  sw $t0, -352($fp)
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -164($fp)
  lw $t0, -340($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -160($fp)
  lw $t0, -164($fp)
  lw $t1, -160($fp)
  add $t2, $t0, $t1
  sw $t2, -156($fp)
  lw $t0, -156($fp)
  sw $t0, -172($fp)
  lw $t0, -340($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -144($fp)
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -140($fp)
  lw $t0, -144($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -136($fp)
  lw $t0, -140($fp)
  lw $t1, -136($fp)
  add $t2, $t0, $t1
  sw $t2, -132($fp)
  lw $t0, -132($fp)
  sw $t0, -148($fp)
  lw $t0, -148($fp)
  lw $t0, 0($t0)
  sw $t0, -152($fp)
  lw $t0, -152($fp)
  lw $t1, -172($fp)
  sw $t0, 0($t1)
  lw $t0, -340($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -116($fp)
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -112($fp)
  lw $t0, -116($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -108($fp)
  lw $t0, -112($fp)
  lw $t1, -108($fp)
  add $t2, $t0, $t1
  sw $t2, -104($fp)
  lw $t0, -104($fp)
  sw $t0, -120($fp)
  lw $t0, -352($fp)
  sw $t0, -92($fp)
  lw $t0, -92($fp)
  lw $t1, -120($fp)
  sw $t0, 0($t1)
label11:
  lw $t0, -340($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -88($fp)
  lw $t0, -88($fp)
  sw $t0, -340($fp)
  j label7
label9:
  li $t0, 0
  sw $t0, -340($fp)
  lw $t0, -348($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -72($fp)
  lw $t0, -72($fp)
  sw $t0, -348($fp)
  j label4
label6:
  li $t0, 0
  sw $t0, -348($fp)
label12:
  lw $t0, -348($fp)
  li $t1, 5
  blt $t0, $t1, label13
  j label14
label13:
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -36($fp)
  lw $t0, -348($fp)
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
  lw $t0, -48($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -348($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -348($fp)
  j label12
label14:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 368
  addi $sp, $sp, 8
  jr $ra

