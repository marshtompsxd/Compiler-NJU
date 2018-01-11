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

changeCal:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 904
  lw $t0, 0($fp)
  sw $t0, -912($fp)
  lw $t0, -912($fp)
  li $t1, 345
  add $t2, $t0, $t1
  sw $t2, -828($fp)
  lw $t0, -828($fp)
  li $t1, 345
  sub $t2, $t0, $t1
  sw $t2, -836($fp)
  lw $t0, -912($fp)
  lw $t1, -908($fp)
  mul $t2, $t0, $t1
  sw $t2, -832($fp)
  lw $t0, -836($fp)
  lw $t1, -832($fp)
  add $t2, $t0, $t1
  sw $t2, -844($fp)
  lw $t0, -912($fp)
  lw $t1, -908($fp)
  mul $t2, $t0, $t1
  sw $t2, -840($fp)
  lw $t0, -844($fp)
  lw $t1, -840($fp)
  sub $t2, $t0, $t1
  sw $t2, -852($fp)
  lw $t0, -912($fp)
  lw $t1, -912($fp)
  mul $t2, $t0, $t1
  sw $t2, -848($fp)
  lw $t0, -852($fp)
  lw $t1, -848($fp)
  add $t2, $t0, $t1
  sw $t2, -860($fp)
  lw $t0, -912($fp)
  lw $t1, -912($fp)
  mul $t2, $t0, $t1
  sw $t2, -856($fp)
  lw $t0, -860($fp)
  lw $t1, -856($fp)
  sub $t2, $t0, $t1
  sw $t2, -864($fp)
  lw $t0, -864($fp)
  sw $t0, -908($fp)
  lw $t0, -908($fp)
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -744($fp)
  lw $t0, -908($fp)
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -740($fp)
  lw $t0, -744($fp)
  lw $t1, -740($fp)
  sub $t2, $t0, $t1
  sw $t2, -752($fp)
  lw $t0, -908($fp)
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -748($fp)
  lw $t0, -752($fp)
  lw $t1, -748($fp)
  add $t2, $t0, $t1
  sw $t2, -760($fp)
  lw $t0, -760($fp)
  li $t1, 17
  add $t2, $t0, $t1
  sw $t2, -768($fp)
  lw $t0, -768($fp)
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -776($fp)
  lw $t0, -776($fp)
  li $t1, 20
  sub $t2, $t0, $t1
  sw $t2, -780($fp)
  lw $t0, -780($fp)
  sw $t0, -908($fp)
  li $t0, 2
  sw $t0, -908($fp)
  lw $t0, -912($fp)
  li $t1, 20
  add $t2, $t0, $t1
  sw $t2, -648($fp)
  lw $t0, -648($fp)
  li $t1, 20
  sub $t2, $t0, $t1
  sw $t2, -656($fp)
  lw $t0, -656($fp)
  sw $t0, -908($fp)
  lw $v0, -908($fp)
  lw $fp, -8($fp)
  addi $sp, $sp, 904
  addi $sp, $sp, 8
  jr $ra

main:
  subu $sp, $sp, 8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  addi $fp, $sp, 8
  subu $sp, $sp, 904
  li $t0, 2
  sw $t0, -904($fp)
  li $t0, 4
  sw $t0, -900($fp)
  li $t0, 14
  sw $t0, -896($fp)
  lw $t0, -904($fp)
  lw $t1, -900($fp)
  add $t2, $t0, $t1
  sw $t2, -516($fp)
  lw $t0, -516($fp)
  lw $t1, -896($fp)
  sub $t2, $t0, $t1
  sw $t2, -520($fp)
  lw $t0, -520($fp)
  sw $t0, -892($fp)
  lw $t0, -904($fp)
  lw $t1, -900($fp)
  add $t2, $t0, $t1
  sw $t2, -496($fp)
  lw $t0, -896($fp)
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -492($fp)
  lw $t0, -496($fp)
  lw $t1, -492($fp)
  add $t2, $t0, $t1
  sw $t2, -500($fp)
  lw $t0, -500($fp)
  sw $t0, -888($fp)
  lw $t0, -904($fp)
  lw $t1, -900($fp)
  add $t2, $t0, $t1
  sw $t2, -468($fp)
  lw $t0, -468($fp)
  lw $t1, -896($fp)
  add $t2, $t0, $t1
  sw $t2, -472($fp)
  lw $t0, -472($fp)
  sw $t0, -884($fp)
  li $t0, 42
  sw $t0, -880($fp)
  li $t0, 0
  sw $t0, -876($fp)
  lw $t0, -904($fp)
  lw $t1, -900($fp)
  add $t2, $t0, $t1
  sw $t2, -416($fp)
  lw $t0, -416($fp)
  lw $t1, -896($fp)
  add $t2, $t0, $t1
  sw $t2, -424($fp)
  lw $t0, -424($fp)
  lw $t1, -892($fp)
  sub $t2, $t0, $t1
  sw $t2, -432($fp)
  lw $t0, -432($fp)
  lw $t1, -888($fp)
  sub $t2, $t0, $t1
  sw $t2, -440($fp)
  lw $t0, -440($fp)
  lw $t1, -884($fp)
  add $t2, $t0, $t1
  sw $t2, -444($fp)
  lw $t0, -444($fp)
  sw $t0, -884($fp)
label1:
  lw $t0, -900($fp)
  lw $t1, -904($fp)
  sub $t2, $t0, $t1
  sw $t2, -400($fp)
  lw $t0, -400($fp)
  lw $t1, -884($fp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -876($fp)
  li $t1, 4
  mul $t2, $t0, $t1
  sw $t2, -352($fp)
  lw $t0, -880($fp)
  lw $t1, -352($fp)
  add $t2, $t0, $t1
  sw $t2, -364($fp)
  lw $t0, -364($fp)
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -372($fp)
  lw $t0, -372($fp)
  li $t1, 4
  add $t2, $t0, $t1
  sw $t2, -380($fp)
  lw $t0, -380($fp)
  li $t1, 5
  add $t2, $t0, $t1
  sw $t2, -384($fp)
  lw $t0, -384($fp)
  sw $t0, -880($fp)
  lw $t0, -884($fp)
  sw $t0, -312($fp)
  subu $sp, $sp, 4
  lw $t0, -900($fp)
  sw $t0, 0($sp)
  jal changeCal
  sw $v0, -308($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 4
  lw $t0, -312($fp)
  lw $t1, -308($fp)
  sub $t2, $t0, $t1
  sw $t2, -320($fp)
  lw $t0, -904($fp)
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -316($fp)
  lw $t0, -320($fp)
  lw $t1, -316($fp)
  add $t2, $t0, $t1
  sw $t2, -328($fp)
  lw $t0, -896($fp)
  lw $t1, -892($fp)
  mul $t2, $t0, $t1
  sw $t2, -324($fp)
  lw $t0, -328($fp)
  lw $t1, -324($fp)
  add $t2, $t0, $t1
  sw $t2, -336($fp)
  lw $t0, -336($fp)
  lw $t1, -884($fp)
  sub $t2, $t0, $t1
  sw $t2, -340($fp)
  lw $t0, -340($fp)
  sw $t0, -872($fp)
  lw $t0, -876($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -284($fp)
  lw $t0, -284($fp)
  sw $t0, -876($fp)
  lw $t0, -876($fp)
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -264($fp)
  lw $t0, -264($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -268($fp)
  lw $t0, -268($fp)
  sw $t0, -876($fp)
  lw $t0, -876($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -244($fp)
  lw $t0, -244($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -248($fp)
  lw $t0, -248($fp)
  sw $t0, -876($fp)
  lw $t0, -876($fp)
  li $t1, 3
  div $t0, $t1
  mflo $t2
  sw $t2, -212($fp)
  lw $t0, -212($fp)
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -216($fp)
  lw $t0, -876($fp)
  lw $t1, -216($fp)
  sub $t2, $t0, $t1
  sw $t2, -228($fp)
  lw $t0, -904($fp)
  sw $t0, -164($fp)
  subu $sp, $sp, 4
  lw $t0, -904($fp)
  sw $t0, 0($sp)
  jal changeCal
  sw $v0, -160($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 4
  lw $t0, -164($fp)
  lw $t1, -160($fp)
  sub $t2, $t0, $t1
  sw $t2, -172($fp)
  lw $t0, -172($fp)
  lw $t1, -900($fp)
  add $t2, $t0, $t1
  sw $t2, -180($fp)
  lw $t0, -180($fp)
  lw $t1, -900($fp)
  sub $t2, $t0, $t1
  sw $t2, -188($fp)
  lw $t0, -188($fp)
  lw $t1, -896($fp)
  add $t2, $t0, $t1
  sw $t2, -196($fp)
  lw $t0, -196($fp)
  lw $t1, -896($fp)
  sub $t2, $t0, $t1
  sw $t2, -224($fp)
  lw $t0, -228($fp)
  lw $t1, -224($fp)
  beq $t0, $t1, label4
  j label5
label4:
  lw $t0, -884($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -152($fp)
  lw $t0, -152($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -156($fp)
  lw $t0, -156($fp)
  sw $t0, -884($fp)
label5:
  lw $t0, -884($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -132($fp)
  lw $t0, -132($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -136($fp)
  lw $t0, -136($fp)
  sw $t0, -884($fp)
  j label1
label3:
  lw $t0, -880($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -112($fp)
  lw $t0, -112($fp)
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -116($fp)
  lw $t0, -116($fp)
  sw $t0, -868($fp)
  lw $t0, -868($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -880($fp)
  sw $t0, -876($fp)
label6:
  lw $t0, -880($fp)
  li $t1, 1222
  bge $t0, $t1, label7
  j label8
label7:
  lw $t0, -880($fp)
  li $t1, 1024
  add $t2, $t0, $t1
  sw $t2, -76($fp)
  lw $t0, -76($fp)
  sw $t0, -876($fp)
  subu $sp, $sp, 4
  lw $t0, -880($fp)
  sw $t0, 0($sp)
  jal changeCal
  sw $v0, -60($fp)
  lw $ra, -4($fp)
  addi $sp, $sp, 4
  lw $t0, -60($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -64($fp)
  lw $t0, -64($fp)
  sw $t0, -880($fp)
  lw $t0, -880($fp)
  sw $t0, -876($fp)
  j label6
label8:
  lw $t0, -880($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  lw $t0, -904($fp)
  lw $t1, -900($fp)
  add $t2, $t0, $t1
  sw $t2, -48($fp)
  lw $t0, -48($fp)
  sw $t0, -904($fp)
  lw $t0, -904($fp)
  lw $t1, -900($fp)
  add $t2, $t0, $t1
  sw $t2, -36($fp)
  lw $t0, -36($fp)
  sw $t0, -900($fp)
  lw $t0, -904($fp)
  lw $t1, -900($fp)
  add $t2, $t0, $t1
  sw $t2, -24($fp)
  lw $t0, -24($fp)
  sw $t0, -896($fp)
  lw $t0, -896($fp)
  move $a0, $t0
  jal write
  lw $ra, -4($fp)
  li $v0, 0
  lw $fp, -8($fp)
  addi $sp, $sp, 904
  addi $sp, $sp, 8
  jr $ra

