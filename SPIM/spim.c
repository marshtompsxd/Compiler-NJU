//
// Created by sunxudong on 12/27/17.
//

#include "spim.h"
#include "../common.h"
#include "../intercode/IC.h"
#include "../intercode/ICTable.h"
#include "../intercode/InterCode.h"

int VSize;
int TSize;
int VBegin;
int TBegin;
int *VOffset;
int *TOffset;

AISE *AISV;
int argNum;

void InitRootInterCodeList() {
  InterCodeEntry *ICVhead, *ICVtail;
  ICVhead = RootInterCodeList->head;
  ICVtail = ICVhead->prev;

  ICVhead->prev = NULL;
  ICVtail->next = NULL;

  AISV = (AISE *)malloc(sizeof(AISE) * 20);
}

void GetVTSize() {
  TSize = TIndex;
  VSize = 0;
  ICVarEntry *ICV;
  for (ICV = RootICVarTable->head; ICV != NULL; ICV = ICV->next) {
    Type *TP = ICV->VariableType;
    if (TP->kind == BASIC)
      VSize++;
    else if (TP->kind == ARRAY) {
      assert(TP->array.dim == 1);
      VSize = VSize + TP->array.DimSize[0];
    } else
      assert(0);
  }

  VOffset = (int *)malloc(sizeof(int) * VIndex);
  TOffset = (int *)malloc(sizeof(int) * TIndex);

  int i;
  int offset = 0;
  VOffset[1] = 0;

  int k = 1;

  for (ICV = RootICVarTable->head; ICV->next != NULL; ICV = ICV->next) {
    k++;
    ICVarEntry *ICVnxt = ICV->next;
    Type *TP = ICV->VariableType;
    if (TP->kind == BASIC) {
      offset++;
      VOffset[ICVnxt->VIndex] = offset;
    } else if (TP->kind == ARRAY) {
      assert(TP->array.dim == 1);
      offset = offset + TP->array.DimSize[0];
      VOffset[ICVnxt->VIndex] = offset;
    } else
      assert(0);
  }
  assert(k == VIndex);

  offset = 0;
  for (i = 1; i <= TIndex; i++) {
    TOffset[i] = offset;
    offset++;
  }

  VBegin = 0; // v_i is at ( $gp + ( VBegin + VOffset[i]*4 )) in stack
  TBegin = VBegin +
           VSize * 4; // t_i is at ( $gp + ( TBegin + TOffset[i]*4 )) in stack

  assert(TSize + VSize <= 8 * 1024);
}

void PrintSize() {
  printf("\nVBegin : %d, Tbegin : %d\n", VBegin, TBegin);
  printf("VNum : %d, TNum : %d\n", VIndex, TIndex);
  printf("offset table:\n");
  int i;
  for (i = 1; i <= VIndex; i++) {
    printf("v%d : %d\n", i, VOffset[i] * 4 + VBegin);
  }
  for (i = 1; i <= TIndex; i++) {
    printf("t%d : %d\n", i, TOffset[i] * 4 + TBegin);
  }
}

int GetVTAddrRelFP(Operand *op) {
  if (op->kind == OVAR)
    return -(VSize + TSize) * 4 - 8 + VBegin + 4 * VOffset[op->VIndex];
  else if (op->kind == OTEMP)
    return -(VSize + TSize) * 4 - 8 + TBegin + 4 * TOffset[op->TIndex];
  else
    assert(0);
}

void MachineCodePreparation(FILE *stream) {

  fprintf(stream, ".data\n"
                  "_prompt: .asciiz \"Enter an integer:\"\n"
                  "_ret: .asciiz \"\\n\"\n"
                  ".globl main\n"
                  ".text\n"
                  "read:\n"
                  "  li $v0, 4\n"
                  "  la $a0, _prompt\n"
                  "  syscall\n"
                  "  li $v0, 5\n"
                  "  syscall\n"
                  "  jr $ra\n\n"
                  "write:\n"
                  "  li $v0, 1\n"
                  "  syscall\n"
                  "  li $v0, 4\n"
                  "  la $a0, _ret\n"
                  "  syscall\n"
                  "  move $v0, $0\n"
                  "  jr $ra\n");
}

InterCodeEntry *ParamGenerator(InterCodeEntry *ICE) {
  assert(ICE->IC->kind == IPARAM);

  InterCodeEntry *entry;
  argNum = 0;
  for (entry = ICE; entry->IC->kind == IPARAM; entry = entry->next) {
    AISV[argNum].op = entry->IC->PARAM.parameter;

    argNum++;
  }
  return entry->prev;
}

InterCodeEntry *FUNGenerator(InterCodeEntry *ICE, FILE *stream) {
  InterCode *IC = ICE->IC;
  assert(IC->kind == IFUNCTION);

  fprintf(stream, "\n%s:\n", IC->FUN.funName);

  if (strcmp(IC->FUN.funName, "main") == 0) {
    assert(argNum == 0);

    fprintf(stream, "  subu $sp, $sp, 8\n");
    fprintf(stream, "  sw $ra, 4($sp)\n");
    fprintf(stream, "  sw $fp, 0($sp)\n");
    fprintf(stream, "  addi $fp, $sp, 8\n");

    fprintf(stream, "  subu $sp, $sp, %d\n", (VSize + TSize) * 4);

    /* now in main function:
     *
     *                         high address
     *         --------------  <- $fp
     *         |  ret addr  |
     *         --------------
     *         |   old fp   |
     *         --------------
     *         |   T data   |
     *         --------------
     *         |   V data   |
     *         -------------- <- $sp
     *                         low address
     */
  } else {
    if (ICE->next->IC->kind == IPARAM) {
      ICE = ParamGenerator(ICE->next);
    }

    fprintf(stream, "  subu $sp, $sp, 8\n");
    fprintf(stream, "  sw $ra, 4($sp)\n");
    fprintf(stream, "  sw $fp, 0($sp)\n");
    fprintf(stream, "  addi $fp, $sp, 8\n");

    fprintf(stream, "  subu $sp, $sp, %d\n", (VSize + TSize) * 4);

    // To-Do: save args into static data segment

    int i;
    for (i = 0; i < argNum; i++) {
      Operand *param = AISV[i].op;
      int paramAddr;
      assert(param->kind == OVAR);
      paramAddr = GetVTAddrRelFP(param);
      fprintf(stream, "  lw $t0, %d($fp)\n", i * 4);
      fprintf(stream, "  sw $t0, %d($fp)\n", paramAddr);
    }

    argNum = 0;

    /* now in xxx function:
     *                         high address
     *         --------------
     *         |            |
     *         | parameters |
     *         |            |
     *         --------------  <- $fp
     *         |  ret addr  |
     *         --------------
     *         |   old fp   |
     *         --------------
     *         |   T data   |
     *         --------------
     *         |   V data   |
     *         -------------- <- $sp
     *                         low address
     */
  }

  return ICE;
}

void AssignGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == IASSIGN);

  Operand *left, *right;
  left = IC->ASSIGN.left;
  right = IC->ASSIGN.right;
  if (right->kind == OICONS) {
    int leftAddr = GetVTAddrRelFP(left);

    fprintf(stream, "  li $t0, %d\n", right->ICons);
    fprintf(stream, "  sw $t0, %d($fp)\n", leftAddr);
  } else {
    int rightAddr = GetVTAddrRelFP(right);
    int leftAddr = GetVTAddrRelFP(left);

    if (right->attr == OREF) {
      // assert(0);
      fprintf(stream, "  lw $t0, %d($fp)\n", rightAddr);
      fprintf(stream, "  lw $t0, 0($t0)\n");

    } else if (right->attr == OADDR) {
      // assert(0);
      fprintf(stream, "  li $t0, %d\n", rightAddr);
      fprintf(stream, "  add $t0, $t0, $fp\n");
    } else {
      fprintf(stream, "  lw $t0, %d($fp)\n", rightAddr);
    }

    if (left->attr == OREF) {
      // assert(0);
      fprintf(stream, "  lw $t1, %d($fp)\n", leftAddr);
      fprintf(stream, "  sw $t0, 0($t1)\n");

    } else {
      fprintf(stream, "  sw $t0, %d($fp)\n", leftAddr);
    }
  }
}

void READGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == IREAD);

  fprintf(stream, "  jal read\n"
                  "  lw $ra, -4($fp)\n"
                  "  move $t0, $v0\n");

  Operand *input = IC->READ.input;
  int inputAddr = GetVTAddrRelFP(input);
  fprintf(stream, "  sw $t0, %d($fp)\n", inputAddr);
}

void WRITEGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == IWRITE);

  Operand *ouput = IC->WRITE.output;
  int outputAddr = GetVTAddrRelFP(ouput);
  fprintf(stream, "  lw $t0, %d($fp)\n", outputAddr);
  fprintf(stream, "  move $a0, $t0\n"
                  "  jal write\n"
                  "  lw $ra, -4($fp)\n");
}

void ReturnGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == IRETURN);

  Operand *ret = IC->RET.ret;

  if (ret->kind == OICONS) {
    fprintf(stream, "  li $v0, %d\n", ret->ICons);
  } else {
    int retAddr = GetVTAddrRelFP(ret);
    fprintf(stream, "  lw $v0, %d($fp)\n", retAddr);
  }

  fprintf(stream, "  lw $fp, -8($fp)\n");
  fprintf(stream, "  addi $sp, $sp, %d\n", (VSize + TSize) * 4);
  fprintf(stream, "  addi $sp, $sp, 8\n");
  fprintf(stream, "  jr $ra\n");
}

void LABELGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == ILABEL);

  fprintf(stream, "label%d:\n", IC->LABELDEC.LIndex);
}

void IFGOTOGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == IIFGOTO);

  Operand *op1, *op2;
  op1 = IC->IFGT.condition->op1;
  op2 = IC->IFGT.condition->op2;

  int op1Addr, op2Addr;

  if (op1->kind == OICONS) {
    fprintf(stream, "  li $t0, %d\n", op1->ICons);
  } else {
    op1Addr = GetVTAddrRelFP(op1);
    fprintf(stream, "  lw $t0, %d($fp)\n", op1Addr);
  }

  if (op2->kind == OICONS) {
    fprintf(stream, "  li $t1, %d\n", op2->ICons);
  } else {
    op2Addr = GetVTAddrRelFP(op2);
    fprintf(stream, "  lw $t1, %d($fp)\n", op2Addr);
  }

  switch (IC->IFGT.condition->relop) {
  case EQ:
    fprintf(stream, "  beq ");
    break;
  case LT:
    fprintf(stream, "  blt ");
    break;
  case GT:
    fprintf(stream, "  bgt ");
    break;
  case NEQ:
    fprintf(stream, "  bne ");
    break;
  case LEQ:
    fprintf(stream, "  ble ");
    break;
  case GEQ:
    fprintf(stream, "  bge ");
    break;
  default:
    assert(0);
  }

  fprintf(stream, "$t0, $t1, label%d\n", IC->IFGT.LIndex);
}

void GOTOGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == IGOTO);

  fprintf(stream, "  j label%d\n", IC->GT.LIndex);
}

void BINOPGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == IADD || IC->kind == ISUB || IC->kind == IMUL ||
         IC->kind == IDIV);

  assert(IC->BINOP.result->kind == OTEMP || IC->BINOP.result->kind == OVAR);
  assert(IC->BINOP.result->attr == OVALUE && IC->BINOP.op1->attr == OVALUE &&
         IC->BINOP.op2->attr == OVALUE);

  Operand *op1, *op2, *result;
  op1 = IC->BINOP.op1;
  op2 = IC->BINOP.op2;
  result = IC->BINOP.result;

  int op1Addr, op2Addr, resultAddr;
  resultAddr = GetVTAddrRelFP(result);

  if (op1->kind == OICONS) {
    fprintf(stream, "  li $t0, %d\n", op1->ICons);
  } else {
    op1Addr = GetVTAddrRelFP(op1);
    fprintf(stream, "  lw $t0, %d($fp)\n", op1Addr);
  }

  if (op2->kind == OICONS) {
    fprintf(stream, "  li $t1, %d\n", op2->ICons);
  } else {
    op2Addr = GetVTAddrRelFP(op2);
    fprintf(stream, "  lw $t1, %d($fp)\n", op2Addr);
  }

  switch (IC->kind) {
  case IADD:
    fprintf(stream, "  add $t2, $t0, $t1\n");
    break;
  case ISUB:
    fprintf(stream, "  sub $t2, $t0, $t1\n");
    break;
  case IMUL:
    fprintf(stream, "  mul $t2, $t0, $t1\n");
    break;
  case IDIV:
    fprintf(stream, "  div $t0, $t1\n  mflo $t2\n");
    break;
  default:
    assert(0);
  }

  fprintf(stream, "  sw $t2, %d($fp)\n", resultAddr);
}

void CallGenerator(InterCode *IC, FILE *stream) {
  assert(IC->kind == ICALL);
  Operand *op = IC->CALL.ret;
  int opAddr = GetVTAddrRelFP(op);

  fprintf(stream, "  jal %s\n", IC->CALL.funName);
  fprintf(stream, "  sw $v0, %d($fp)\n", opAddr);
}

InterCodeEntry *ArgGenerator(InterCodeEntry *ICE, FILE *stream) {
  assert(ICE->IC->kind == IARG);

  InterCodeEntry *entry;
  int num = 0;
  for (entry = ICE; entry->IC->kind == IARG; entry = entry->next) {
    num++;
  }

  fprintf(stream, "  subu $sp, $sp, %d\n", 4 * num);

  int i = 0;
  for (entry = ICE; entry->IC->kind == IARG; entry = entry->next) {
    Operand *op = entry->IC->ARG.argument;
    int opAddr = GetVTAddrRelFP(op);
    fprintf(stream, "  lw $t0, %d($fp)\n", opAddr);
    fprintf(stream, "  sw $t0, %d($sp)\n", 4 * (num - i - 1));
    i++;
  }

  CallGenerator(entry->IC, stream);
  fprintf(stream, "  lw $ra, -4($fp)\n");
  fprintf(stream, "  addi $sp, $sp, %d\n", 4 * num);

  return entry;
}

void MachineCodeGenerator(char *filename) {
  FILE *fp;

  if (filename == NULL) {
    fp = stdout;
  } else {
    fp = fopen(filename, "w");
    assert(fp != NULL);
  }

  InitRootInterCodeList();
  MachineCodePreparation(fp);
  GetVTSize();
  // PrintSize();

  InterCodeEntry *ICE;
  for (ICE = RootInterCodeList->head; ICE != NULL; ICE = ICE->next) {
    InterCode *IC = ICE->IC;
    switch (IC->kind) {
    case IFUNCTION:
      ICE = FUNGenerator(ICE, fp);
      break;
    case IASSIGN:
      AssignGenerator(IC, fp);
      break;
    case IREAD:
      READGenerator(IC, fp);
      break;
    case IWRITE:
      WRITEGenerator(IC, fp);
      break;
    case ILABEL:
      LABELGenerator(IC, fp);
      break;
    case IIFGOTO:
      IFGOTOGenerator(IC, fp);
      break;
    case IGOTO:
      GOTOGenerator(IC, fp);
      break;
    case IADD:
    case ISUB:
    case IMUL:
    case IDIV:
      BINOPGenerator(IC, fp);
      break;
    case IARG:
      ICE = ArgGenerator(ICE, fp);
      break;
    case IRETURN:
      ReturnGenerator(IC, fp);
      break;
    case IDEC:
      break;
    default:
      assert(0);
    }
  }
  fprintf(fp, "\n");

  // free(VOffset);
  // free(TOffset);
}