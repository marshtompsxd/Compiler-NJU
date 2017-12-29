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
  sw $t0, -304($fp)
  lw $t0, -348($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -300($fp)
  lw $t0, -304($fp)
  lw $t1, -300($fp)
  add $t2, $t0, $t1
  sw $t2, -296($fp)
  lw $t0, -296($fp)
  sw $t0, -312($fp)
  jal read
  lw $ra, -4($fp)
  move $t0, $v0
  sw $t0, -292($fp)
  lw $t0, -292($fp)
  lw $t1, -312($fp)
  sw $t0, 0($t1)
  lw $t0, -348($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -288($fp)
  lw $t0, -288($fp)
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
  sw $t2, -260($fp)
  lw $t0, -340($fp)
  lw $t1, -260($fp)
  blt $t0, $t1, label8
  j label9
label8:
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -232($fp)
  lw $t0, -340($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -228($fp)
  lw $t0, -232($fp)
  lw $t1, -228($fp)
  add $t2, $t0, $t1
  sw $t2, -224($fp)
  lw $t0, -224($fp)
  sw $t0, -240($fp)
  lw $t0, -240($fp)
  lw $t0, 0($t0)
  sw $t0, -248($fp)
  lw $t0, -340($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -216($fp)
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -212($fp)
  lw $t0, -216($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -208($fp)
  lw $t0, -212($fp)
  lw $t1, -208($fp)
  add $t2, $t0, $t1
  sw $t2, -204($fp)
  lw $t0, -204($fp)
  sw $t0, -220($fp)
  lw $t0, -220($fp)
  lw $t0, 0($t0)
  sw $t0, -244($fp)
  lw $t0, -248($fp)
  lw $t1, -244($fp)
  bgt $t0, $t1, label10
  j label11
label10:
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -180($fp)
  lw $t0, -340($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -176($fp)
  lw $t0, -180($fp)
  lw $t1, -176($fp)
  add $t2, $t0, $t1
  sw $t2, -172($fp)
  lw $t0, -172($fp)
  sw $t0, -188($fp)
  lw $t0, -188($fp)
  lw $t0, 0($t0)
  sw $t0, -192($fp)
  lw $t0, -192($fp)
  sw $t0, -352($fp)
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -160($fp)
  lw $t0, -340($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -156($fp)
  lw $t0, -160($fp)
  lw $t1, -156($fp)
  add $t2, $t0, $t1
  sw $t2, -152($fp)
  lw $t0, -152($fp)
  sw $t0, -168($fp)
  lw $t0, -340($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -140($fp)
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -136($fp)
  lw $t0, -140($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -132($fp)
  lw $t0, -136($fp)
  lw $t1, -132($fp)
  add $t2, $t0, $t1
  sw $t2, -128($fp)
  lw $t0, -128($fp)
  sw $t0, -144($fp)
  lw $t0, -144($fp)
  lw $t0, 0($t0)
  sw $t0, -148($fp)
  lw $t0, -148($fp)
  lw $t1, -168($fp)
  sw $t0, 0($t1)
  lw $t0, -340($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -112($fp)
  li $t0, -376
  add $t0, $t0, $fp
  sw $t0, -108($fp)
  lw $t0, -112($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -104($fp)
  lw $t0, -108($fp)
  lw $t1, -104($fp)
  add $t2, $t0, $t1
  sw $t2, -100($fp)
  lw $t0, -100($fp)
  sw $t0, -116($fp)
  lw $t0, -352($fp)
  sw $t0, -88($fp)
  lw $t0, -88($fp)
  lw $t1, -116($fp)
  sw $t0, 0($t1)
label11:
  lw $t0, -340($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -84($fp)
  lw $t0, -84($fp)
  sw $t0, -340($fp)
  j label7
label9:
  li $t0, 0
  sw $t0, -340($fp)
  lw $t0, -348($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -68($fp)
  lw $t0, -68($fp)
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
  sw $t0, -32($fp)
  lw $t0, -348($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -28($fp)
  lw $t0, -32($fp)
  lw $t1, -28($fp)
  add $t2, $t0, $t1
  sw $t2, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -40($fp)
  lw $t0, -40($fp)
  lw $t0, 0($t0)
  sw $t0, -44($fp)
  lw $t0, -44($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -348($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -20($fp)
  lw $t0, -20($fp)
  sw $t0, -348($fp)
  j label12
label14:
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 368
  addi $sp, $sp, 8
  jr $ra

