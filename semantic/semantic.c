#include "semantic.h"
#include "../intercode/IC.h"
#include "check.h"
#include "list.h"
#include "symbol_table.h"
#include <stdlib.h>

static FieldList *VarDecAnalysisInStruct(ParsingNode *node, Type *InheritType);
static FieldList *DecAnalysisInStruct(ParsingNode *node, Type *InheritType);
static FieldList *DecListAnalysisInStruct(ParsingNode *node, Type *InheritType);
static FieldList *DefAnalysisInStruct(ParsingNode *node);
static FieldList *DefListAnalysisInStruct(ParsingNode *node);

static Type *StructSpecifierAnalysis(ParsingNode *node);
static Type *TYPEAnalysis(ParsingNode *node);
static Type *SpecifierAnalysis(ParsingNode *node);
static void VarDecAnalysisGlobal(ParsingNode *node, Type *InheritType);
static void ExtDecListAnalysis(ParsingNode *node, Type *InheritType);

static SymbolTableEntry *VarDecAnalysisInParam(ParsingNode *node,
                                               Type *InheritType);
static SymbolTableEntry *ParamDecAnalysis(ParsingNode *node);
static SymbolTableEntry *VarListAnalysis(ParsingNode *node);
static SymbolTableEntry *
VarDecAnalysisInFunction(ParsingNode *node, ParamList *PL, Type *InheritType);
static void DecAnalysisInFunction(ParsingNode *node, ParamList *PL,
                                  Type *InheritType);
static void DecListAnalysisInFunction(ParsingNode *node, ParamList *PL,
                                      Type *InheritType);
static void DefAnalysisInFunction(ParsingNode *node, ParamList *PL);
static void DefListAnalysisInFunction(ParsingNode *node, ParamList *PL);
static void StmtListAnalysis(ParsingNode *node, Type *RetType, ParamList *PL);
static void CompStAnalysis(ParsingNode *node, Type *RetType, ParamList *PL);
static ParamList *FunDecAnalysis(ParsingNode *node, Type *RetType);

static SymbolTableEntry *ArgsAnalysis(ParsingNode *node, ParamList *PL);
static Type *ExpAnalysis(ParsingNode *node, ParamList *PL);
static void StmtAnalysis(ParsingNode *node, Type *RetType, ParamList *PL);

static void ExtDefAnalysis(ParsingNode *node);
static void ExtDefListAnalysis(ParsingNode *node);
static void ProgramAnalysis(ParsingNode *node);

static void InsertReadWriteIntoSymbolTable();

int sym_top;
int struct_top;

SymbolTableHead *RootSymbolTable;
SymbolTableHead *CurrentSymbolTable;
SymbolTableHead *SymbolTableStack[STACK_SIZE];

StructTypeTableHead *RootStructTypeTable;
StructTypeTableHead *CurrentStructTypeTable;
StructTypeTableHead *StructTypeTableStack[STACK_SIZE];

bool SemanticSwitch;

static void InitTable() {
  SemanticSwitch = true;

  sym_top = -1; // top is -1 means stack is empty
  CurrentSymbolTable = RootSymbolTable =
      (SymbolTableHead *)malloc(sizeof(SymbolTableHead));
  RootSymbolTable->head = NULL;

  struct_top = -1; // top is -1 means stack is empty
  CurrentStructTypeTable = RootStructTypeTable =
      (StructTypeTableHead *)malloc(sizeof(StructTypeTableHead));
  RootStructTypeTable->head = NULL;

  InsertReadWriteIntoSymbolTable();
}

static void InsertReadWriteIntoSymbolTable() {
  Type *IntType = (Type *)malloc(sizeof(Type));
  IntType->kind = BASIC;
  IntType->basic = int_type;

  SymbolTableEntry *READ = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
  READ->kind = FUN;
  READ->lineno = 0;
  READ->Function.FunName = (char *)malloc(sizeof("read"));
  strcpy(READ->Function.FunName, "read");
  READ->Function.RetType = IntType;
  READ->Function.PL = (ParamList *)malloc(sizeof(ParamList));
  READ->Function.PL->head = NULL;
  InsertItemIntoSymbolTable(READ, RootSymbolTable);

  SymbolTableEntry *WRITE =
      (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
  WRITE->kind = FUN;
  WRITE->lineno = 0;
  WRITE->Function.FunName = (char *)malloc(sizeof("write"));
  strcpy(WRITE->Function.FunName, "write");
  WRITE->Function.RetType = IntType;
  WRITE->Function.PL = (ParamList *)malloc(sizeof(ParamList));
  WRITE->Function.PL->head =
      (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
  WRITE->Function.PL->head->lineno = 0;
  WRITE->Function.PL->head->kind = VAR;
  WRITE->Function.PL->head->Variable.VariableType = IntType;
  WRITE->Function.PL->head->Variable.VariableName =
      (char *)malloc(sizeof("???"));
  strcpy(WRITE->Function.PL->head->Variable.VariableName, "???");
  WRITE->Function.PL->head->tail = NULL;
  InsertItemIntoSymbolTable(WRITE, RootSymbolTable);
}

static FieldList *VarDecAnalysisInStruct(ParsingNode *node, Type *InheritType) {
  assert(node->SymbolIndex == AVarDec);

  if (node->childrenNum == 4) {
    ParsingNode *IntNode = thirdchild(node);

    FieldList *FL;
    Type *subType = (Type *)malloc(sizeof(Type));

    subType->kind = ARRAY;
    subType->array.elem = InheritType;
    subType->array.size = IntNode->int_value;
    FL = VarDecAnalysisInStruct(node->firstchild, subType);

    return FL;
  } else {
    ParsingNode *IDNode = node->firstchild;

    FieldList *FL = (FieldList *)malloc(sizeof(FieldList));
    FL->name = (char *)malloc(strlen(IDNode->IDname));
    strcpy(FL->name, IDNode->IDname);
    FL->type = InheritType;
    FL->lineno = IDNode->lineno;
    FL->tail = NULL;

    CheckSameVarNameInSymbolTable(FL->name, FL->lineno, CurrentSymbolTable,
                                  FieldName);
    CheckSameVarNameInStructTypeTable(FL->name, FL->lineno,
                                      CurrentStructTypeTable, FieldName);

    return FL;
  }
}

static FieldList *DecAnalysisInStruct(ParsingNode *node, Type *InheritType) {
  assert(node->SymbolIndex == ADec);

  if (node->childrenNum == 3) {
    FieldList *FL = VarDecAnalysisInStruct(node->firstchild, InheritType);
    // ATTENTION: CHECK ERROR #15 !!!
    SemanticSwitch = false;
    printf(
        "\033[31mError type 15 at Line %d: Initialized field \"%s\".\033[0m\n",
        node->lineno, FL->name);

    return FL;
  } else {
    return VarDecAnalysisInStruct(node->firstchild, InheritType);
  }
}

static FieldList *DecListAnalysisInStruct(ParsingNode *node,
                                          Type *InheritType) {
  assert(node->SymbolIndex == ADecList);

  if (node->childrenNum == 3) {
    FieldList *FL;
    FL = DecAnalysisInStruct(node->firstchild, InheritType);
    FL->tail = DecListAnalysisInStruct(thirdchild(node), InheritType);
    return FL;
  } else {
    return DecAnalysisInStruct(node->firstchild, InheritType);
  }
}

static FieldList *DefAnalysisInStruct(ParsingNode *node) {
  assert(node->SymbolIndex == ADef);

  Type *InheritType = SpecifierAnalysis(node->firstchild);
  return DecListAnalysisInStruct(secondchild(node), InheritType);
}

static FieldList *DefListAnalysisInStruct(ParsingNode *node) {
  assert(node->SymbolIndex == ADefList);

  if (node->kind != Dummy) {
    FieldList *FL;
    FieldList *FLT;
    FL = DefAnalysisInStruct(node->firstchild);
    FLT = FLTail(FL);
    FLT->tail = DefListAnalysisInStruct(node->firstchild->nextsibiling);
    return FL;
  } else {
    return NULL;
  }
}

static char *AnonymousStructSuffix() {
  static int suffix = 0;
  char *s = (char *)malloc(100);
  sprintf(s, "%d", suffix);
  suffix++;
  return s;
}

static Type *StructSpecifierAnalysis(ParsingNode *node) {
  assert(node->SymbolIndex == AStructSpecifier);

  Type *SpecifierType = (Type *)malloc(sizeof(Type));
  SpecifierType->kind = STRUCTURE;

  if (secondchild(node)->SymbolIndex == AOptTag) {
    // set structname
    ParsingNode *OptTagNode = secondchild(node);
    if (OptTagNode->kind != Dummy) {
      ParsingNode *IDNode = OptTagNode->firstchild;
      SpecifierType->structure.structname =
          (char *)malloc(strlen(IDNode->IDname));
      strcpy(SpecifierType->structure.structname, IDNode->IDname);
    } else {
      char *name = AnonymousStructSuffix();
      ParsingNode *IDNode = GenerateIDNode(node->lineno, name);
      OptTagNode->firstchild = IDNode;
      SpecifierType->structure.structname =
          (char *)malloc(strlen(IDNode->IDname));
      strcpy(SpecifierType->structure.structname, IDNode->IDname);
    }

    // set struct field list

    SpecifierType->structure.member =
        DefListAnalysisInStruct(fourthchild(node));

    // ATTENTION: CHECK ERROR #15 !!!

    CheckDuplicatedFieldNameInOneStruct(SpecifierType);

    StructTypeTableEntry *STE =
        (StructTypeTableEntry *)malloc(sizeof(StructTypeTableEntry));
    STE->lineno = node->lineno;
    STE->TP = SpecifierType;
    STE->tail = NULL;

    // ATTENTION: CHECK ERROR #16 !!!
    if (STE->TP->structure.structname != NULL) {
      CheckSameVarNameInSymbolTable(STE->TP->structure.structname, STE->lineno,
                                    CurrentSymbolTable, StructName);
      CheckSameVarNameInStructTypeTable(STE->TP->structure.structname,
                                        STE->lineno, CurrentStructTypeTable,
                                        StructName);
      InsertItemIntoStructTypeTable(STE, CurrentStructTypeTable);
    }

    return SpecifierType;
  } else {

    ParsingNode *TagNode = secondchild(node);
    ParsingNode *IDNode = TagNode->firstchild;

    // Need repair!!!!!
    // repair OK!
    SpecifierType = LookUpForStructType(IDNode->IDname);

    // ATTENTION: CHECK ERROR #17 !!!
    if (SpecifierType == NULL) {
      SemanticSwitch = false;
      printf("\033[31mError type 17 at Line %d: Undefined structure "
             "\"%s\".\033[0m\n",
             node->lineno, IDNode->IDname);
    }

    return SpecifierType;
  }
}

static Type *TYPEAnalysis(ParsingNode *node) {
  assert(node->SymbolIndex == ATYPE);

  Type *SpecifierType = (Type *)malloc(sizeof(Type));
  SpecifierType->kind = BASIC;
  SpecifierType->basic = node->type;

  return SpecifierType;
}

static Type *SpecifierAnalysis(ParsingNode *node) {
  assert(node->SymbolIndex == ASpecifier);

  if (node->firstchild->SymbolIndex == ATYPE) {
    return TYPEAnalysis(node->firstchild);
  } else {
    // for Intermediate code generation, enable struct type
    ICSwitch = false;
    return StructSpecifierAnalysis(node->firstchild);
  }
}

static void VarDecAnalysisGlobal(ParsingNode *node, Type *InheritType) {
  assert(node->SymbolIndex == AVarDec);

  if (node->childrenNum == 4) {
    ParsingNode *TypeNode = thirdchild(node);

    Type *subType = (Type *)malloc(sizeof(Type));
    subType->kind = ARRAY;
    subType->array.elem = InheritType;
    subType->array.size = TypeNode->int_value;

    VarDecAnalysisGlobal(node->firstchild, subType);
  } else {
    ParsingNode *IDNode = node->firstchild;

    SymbolTableEntry *SE = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
    SE->kind = VAR;
    SE->lineno = IDNode->lineno;
    SE->Variable.VariableName = (char *)malloc(strlen(IDNode->IDname));
    strcpy(SE->Variable.VariableName, IDNode->IDname);
    SE->Variable.VariableType = InheritType;
    SE->tail = NULL;

    // ATTENTION: CHECK ERROR #3 !!!
    CheckSameVarNameInSymbolTable(SE->Variable.VariableName, SE->lineno,
                                  CurrentSymbolTable, VarName);
    CheckSameVarNameInStructTypeTable(SE->Variable.VariableName, SE->lineno,
                                      CurrentStructTypeTable, VarName);
    InsertItemIntoSymbolTable(SE, CurrentSymbolTable);
  }
}

static void ExtDecListAnalysis(ParsingNode *node, Type *InheritType) {
  assert(node->SymbolIndex == AExtDecList);

  if (node->childrenNum == 3) {
    VarDecAnalysisGlobal(node->firstchild, InheritType);
    ExtDecListAnalysis(thirdchild(node), InheritType);
  } else {
    VarDecAnalysisGlobal(node->firstchild, InheritType);
  }
}

static SymbolTableEntry *VarDecAnalysisInParam(ParsingNode *node,
                                               Type *InheritType) {
  assert(node->SymbolIndex == AVarDec);

  if (node->childrenNum == 4) {
    ParsingNode *TypeNode = thirdchild(node);

    Type *subType = (Type *)malloc(sizeof(Type));
    subType->kind = ARRAY;
    subType->array.elem = InheritType;
    subType->array.size = TypeNode->int_value;

    return VarDecAnalysisInParam(node->firstchild, subType);
  } else {
    ParsingNode *IDNode = node->firstchild;

    SymbolTableEntry *SE = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
    SE->kind = VAR;
    SE->lineno = IDNode->lineno;
    SE->Variable.VariableName = (char *)malloc(strlen(IDNode->IDname));
    strcpy(SE->Variable.VariableName, IDNode->IDname);
    SE->Variable.VariableType = InheritType;
    SE->tail = NULL;

    return SE;
  }
}

static SymbolTableEntry *ParamDecAnalysis(ParsingNode *node) {
  assert(node->SymbolIndex == AParamDec);

  SymbolTableEntry *SE;
  Type *InheritType = SpecifierAnalysis(node->firstchild);
  SE = VarDecAnalysisInParam(secondchild(node), InheritType);
  return SE;
}

static SymbolTableEntry *VarListAnalysis(ParsingNode *node) {
  assert(node->SymbolIndex == AVarList);

  SymbolTableEntry *SE;

  if (node->childrenNum == 3) {
    SE = ParamDecAnalysis(node->firstchild);
    SE->tail = VarListAnalysis(thirdchild(node));
  } else {
    SE = ParamDecAnalysis(node->firstchild);
  }

  return SE;
}

static ParamList *FunDecAnalysis(ParsingNode *node, Type *RetType) {
  assert(node->SymbolIndex == AFunDec);

  ParsingNode *IDNode = node->firstchild;

  SymbolTableEntry *SE = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
  SE->kind = FUN;
  SE->lineno = IDNode->lineno;
  SE->Function.FunName = (char *)malloc(strlen(IDNode->IDname));
  strcpy(SE->Function.FunName, IDNode->IDname);
  SE->Function.RetType = RetType;
  SE->Function.PL = (ParamList *)malloc(sizeof(ParamList));
  SE->tail = NULL;

  if (node->childrenNum == 4) {
    SE->Function.PL->head = VarListAnalysis(thirdchild(node));
  } else {
    SE->Function.PL->head = NULL;
  }

  // ATTENTION: CHECK ERROR #4 !!!
  CheckSameFunNameInSymbolTable(SE->Function.FunName, SE->lineno,
                                CurrentSymbolTable);
  InsertItemIntoSymbolTable(SE, CurrentSymbolTable);

  return SE->Function.PL;
}

static SymbolTableEntry *
VarDecAnalysisInFunction(ParsingNode *node, ParamList *PL, Type *InheritType) {
  assert(node->SymbolIndex == AVarDec);

  if (node->childrenNum == 4) {
    ParsingNode *TypeNode = thirdchild(node);

    Type *subType = (Type *)malloc(sizeof(Type));
    subType->kind = ARRAY;
    subType->array.elem = InheritType;
    subType->array.size = TypeNode->int_value;

    return VarDecAnalysisInFunction(node->firstchild, PL, subType);
  } else {
    ParsingNode *IDNode = node->firstchild;

    SymbolTableEntry *SE = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
    SE->kind = VAR;
    SE->lineno = IDNode->lineno;
    SE->Variable.VariableName = (char *)malloc(strlen(IDNode->IDname));
    strcpy(SE->Variable.VariableName, IDNode->IDname);
    SE->Variable.VariableType = InheritType;
    SE->tail = NULL;

    // ATTENTION: CHECK ERROR #3 !!!
    CheckSameVarNameInSymbolTable(SE->Variable.VariableName, SE->lineno,
                                  CurrentSymbolTable, VarName);
    CheckSameVarNameInStructTypeTable(SE->Variable.VariableName, SE->lineno,
                                      CurrentStructTypeTable, VarName);
    CheckSameVarNameInParamList(SE->Variable.VariableName, SE->lineno, PL);
    InsertItemIntoSymbolTable(SE, CurrentSymbolTable);

    return SE;
  }
}

static void DecAnalysisInFunction(ParsingNode *node, ParamList *PL,
                                  Type *InheritType) {
  if (node->childrenNum == 3) {
    SymbolTableEntry *SE =
        VarDecAnalysisInFunction(node->firstchild, PL, InheritType);
    Type *VarType = SE->Variable.VariableType;
    Type *ExpType = ExpAnalysis(thirdchild(node), PL);

    if (ExpType == NULL)
      return;

    if (!CheckTypeEquivalence(VarType, ExpType)) {
      SemanticSwitch = false;
      printf("\033[31mError type 5 at Line %d: Type mismatched for "
             "assignment.\033[0m\n",
             secondchild(node)->lineno);
    }
    if (VarType->kind == ARRAY) {
      SemanticSwitch = false;
      printf("\033[31mError type 5 at Line %d: Type mismatched for "
             "assignment(array type should not be assigned).\033[0m\n",
             secondchild(node)->lineno);
    }

  } else {
    VarDecAnalysisInFunction(node->firstchild, PL, InheritType);
  }
}

static void DecListAnalysisInFunction(ParsingNode *node, ParamList *PL,
                                      Type *InheritType) {

  assert(node->SymbolIndex == ADecList);

  if (node->childrenNum == 3) {
    DecAnalysisInFunction(node->firstchild, PL, InheritType);
    DecListAnalysisInFunction(thirdchild(node), PL, InheritType);
  } else {
    DecAnalysisInFunction(node->firstchild, PL, InheritType);
  }
}

static void DefAnalysisInFunction(ParsingNode *node, ParamList *PL) {
  assert(node->SymbolIndex == ADef);

  Type *InheritType = SpecifierAnalysis(node->firstchild);

  if (InheritType == NULL)
    return;

  DecListAnalysisInFunction(secondchild(node), PL, InheritType);
}

static void DefListAnalysisInFunction(ParsingNode *node, ParamList *PL) {
  assert(node->SymbolIndex == ADefList);

  if (node->kind != Dummy) {
    DefAnalysisInFunction(node->firstchild, PL);
    DefListAnalysisInFunction(secondchild(node), PL);
  } else
    return;
}

static SymbolTableEntry *ArgsAnalysis(ParsingNode *node, ParamList *PL) {
  assert(node->SymbolIndex == AArgs);

  Type *ExpType = ExpAnalysis(node->firstchild, PL);
  if (ExpType == NULL)
    return NULL;

  SymbolTableEntry *SE = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
  SE->kind = VAR;
  SE->Variable.VariableType = ExpType;
  SE->Variable.VariableName = NULL;
  SE->tail = NULL;

  if (node->childrenNum == 3)
    SE->tail = ArgsAnalysis(thirdchild(node), PL);
  else
    SE->tail = NULL;

  return SE;
}

static Type *ExpAnalysis(ParsingNode *node, ParamList *PL) {
  assert(node->SymbolIndex == AExp);

  if (node->childrenNum == 1) {
    if (node->firstchild->SymbolIndex == AID) // ID
    {
      SymbolTableEntry *SE = LookUpForParam(node->firstchild->IDname, PL);
      if (SE != NULL)
        return SE->Variable.VariableType;
      SE = LookUpForVarDef(node->firstchild->IDname);

      // ATTENTION: CHECK ERROR #1 !!!
      if (SE != NULL)
        return SE->Variable.VariableType;
      else {
        SemanticSwitch = false;
        printf("\033[31mError type 1 at Line %d: Undefined variable "
               "\"%s\".\033[0m\n",
               node->firstchild->lineno, node->firstchild->IDname);
        return NULL;
      }
    } else // INT or FLOAT
    {
      Type *ExpType;
      ExpType = (Type *)malloc(sizeof(ExpType));
      ExpType->kind = BASIC;
      if (node->firstchild->SymbolIndex == AINT)
        ExpType->basic = int_type;
      else
        ExpType->basic = float_type;

      return ExpType;
    }
  } else if (node->childrenNum == 2) {
    return ExpAnalysis(secondchild(node), PL);
  } else if (node->childrenNum == 3) {
    if (secondchild(node)->SymbolIndex == AASSIGNOP) {
      Type *T1 = ExpAnalysis(node->firstchild, PL);
      Type *T2 = ExpAnalysis(thirdchild(node), PL);
      if (T1 == NULL || T2 == NULL)
        return NULL;

      // ATTENTION: CHECK ERROR #5 !!!
      if (!CheckTypeEquivalence(T1, T2)) {
        SemanticSwitch = false;
        printf("\033[31mError type 5 at Line %d: Type mismatched for "
               "assignment.\033[0m\n",
               secondchild(node)->lineno);
        return NULL;
      }
      if (T1->kind == ARRAY) {
        SemanticSwitch = false;
        printf("\033[31mError type 5 at Line %d: Type mismatched for "
               "assignment(array type should not be assigned).\033[0m\n",
               secondchild(node)->lineno);
        return NULL;
      }

      // ATTENTION: CHECK ERROR #6 !!!
      if (!CheckLvalue(node->firstchild)) {
        SemanticSwitch = false;
        printf("\033[31mError type 6 at Line %d: The left-hand side of an "
               "assignment must be a variable.\033[0m\n",
               secondchild(node)->lineno);
        return NULL;
      }

      return T1;
    } else if (IsArithmeticNode(secondchild(node)) ||
               IsLogicNode(secondchild(node)) ||
               IsRELOPNode(secondchild(node))) {
      Type *T1 = ExpAnalysis(node->firstchild, PL);
      Type *T2 = ExpAnalysis(thirdchild(node), PL);
      if (T1 == NULL || T2 == NULL)
        return NULL;

      // ATTENTION: CHECK ERROR #7 !!!
      if (!CheckTypeEquivalence(T1, T2)) {
        SemanticSwitch = false;
        printf("\033[31mError type 7 at Line %d: Type mismatched for "
               "operands.\033[0m\n",
               secondchild(node)->lineno);
        return NULL;
      }
      if (T1->kind != BASIC) {
        SemanticSwitch = false;
        printf("\033[31mError type 7 at Line %d: Type mismatched for "
               "operands(arithmetic operation only applies to int and "
               "float).\033[0m\n",
               secondchild(node)->lineno);
        return NULL;
      }

      return T1;
    } else if (node->firstchild->SymbolIndex == ALP) {
      return ExpAnalysis(secondchild(node), PL);
    } else if (node->firstchild->SymbolIndex == AID) {
      // check function call
      SymbolTableEntry *SE;
      SE = LookUpForFunDef(node->firstchild->IDname);

      // ATTENTION: CHECK ERROR #2 and #11 !!!
      if (SE == NULL) {
        SemanticSwitch = false;
        if (LookUpForVarDef(node->firstchild->IDname) != NULL) {

          printf("\033[31mError type 11 at Line %d: \"%s\" is not a "
                 "function.\033[0m\n",
                 node->firstchild->lineno, node->firstchild->IDname);

        } else {
          printf("\033[31mError type 2 at Line %d: Undefined function "
                 "\"%s\".\033[0m\n",
                 node->firstchild->lineno, node->firstchild->IDname);
        }
        return NULL;
      }

      ParamList *DPL = SE->Function.PL;
      ParamList *SPL = (ParamList *)malloc(sizeof(ParamList));
      SPL->head = NULL;

      // ATTENTION: CHECK ERROR #9 !!!
      if (!CheckParamEquivalence(SPL, DPL)) {
        SemanticSwitch = false;
        // char* str1 = GenerateParamString(SPL);
        // char* str2 = GenerateParamString(DPL);

        printf("\033[31mError type 9 at Line %d: Function \"%s\" is not "
               "applicable for arguments.\033[0m\n",
               node->firstchild->lineno, SE->Function.FunName);
        return NULL;
      }

      return SE->Function.RetType;
    } else {
      assert(secondchild(node)->SymbolIndex == ADOT);

      // check struct field
      Type *TP = ExpAnalysis(node->firstchild, PL);
      if (TP == NULL)
        return NULL;

      // ATTENTION: CHECK ERROR #12 !!!
      if (!IsTypeStruct(TP)) {
        SemanticSwitch = false;
        printf(
            "\033[31mError type 13 at Line %d: Illegal use of \".\".\033[0m\n",
            secondchild(node)->lineno);
        return NULL;
      }

      // ATTENTION: CHECK ERROR #14 !!!
      Type *FT = LookUpForField(thirdchild(node)->IDname, TP);
      if (FT == NULL) {
        SemanticSwitch = false;
        printf("\033[31mError type 14 at Line %d: Non-existent field "
               "\"%s\".\033[0m\n",
               secondchild(node)->lineno, thirdchild(node)->IDname);
        return NULL;
      }

      return FT;
    }
  } else {
    if (thirdchild(node)->SymbolIndex == AArgs) {
      // check function call
      SymbolTableEntry *SE;
      SE = LookUpForFunDef(node->firstchild->IDname);

      // ATTENTION: CHECK ERROR #2 and #11 !!!
      if (SE == NULL) {
        SemanticSwitch = false;
        if (LookUpForVarDef(node->firstchild->IDname) != NULL) {

          printf("\033[31mError type 11 at Line %d: \"%s\" is not a "
                 "function.\033[0m\n",
                 node->firstchild->lineno, node->firstchild->IDname);

        } else {
          printf("\033[31mError type 2 at Line %d: Undefined function "
                 "\"%s\".\033[0m\n",
                 node->firstchild->lineno, node->firstchild->IDname);
        }
        return NULL;
      }

      ParamList *DPL = SE->Function.PL;
      ParamList *SPL = (ParamList *)malloc(sizeof(ParamList));
      SPL->head = ArgsAnalysis(thirdchild(node), PL);
      if (SPL->head == NULL)
        return NULL;

      // ATTENTION: CHECK ERROR #9 !!!
      if (!CheckParamEquivalence(SPL, DPL)) {
        SemanticSwitch = false;
        // bugs in below two lines
        // char* str1 = GenerateParamString(SPL);
        // char* str2 = GenerateParamString(DPL);

        printf("\033[31mError type 9 at Line %d: Function \"%s\" is not "
               "applicable for arguments.\033[0m\n",
               node->firstchild->lineno, SE->Function.FunName);
        return NULL;
      }

      return SE->Function.RetType;
    } else {
      assert(secondchild(node)->SymbolIndex == ALB);
      Type *ArrayType = ExpAnalysis(node->firstchild, PL);
      Type *IndexType = ExpAnalysis(thirdchild(node), PL);
      if (ArrayType == NULL || IndexType == NULL)
        return NULL;

      // ATTENTION: CHECK ERROR #12 !!!
      if (!IsTypeInt(IndexType)) {
        SemanticSwitch = false;
        printf("\033[31mError type 12 at Line %d: index is not an "
               "integer.\033[0m\n",
               thirdchild(node)->lineno);
        return NULL;
      }

      // ATTENTION: CHECK ERROR #10 !!!
      if (!IsArray(ArrayType)) {
        SemanticSwitch = false;
        printf(
            "\033[31mError type 10 at Line %d: exp is not an array.\033[0m\n",
            node->firstchild->lineno);
        return NULL;
      }

      return ArrayType->array.elem;
    }
  }
}

static void StmtAnalysis(ParsingNode *node, Type *RetType, ParamList *PL) {
  assert(node->SymbolIndex == AStmt);

  if (node->childrenNum == 1) // CompSt
  {
    CompStAnalysis(node->firstchild, RetType, PL);
  } else if (node->childrenNum == 2) {
    ExpAnalysis(node->firstchild, PL);
  } else if (node->childrenNum == 3) // RETURN
  {
    assert(node->firstchild->SymbolIndex == ARETURN);
    Type *ExpType = ExpAnalysis(secondchild(node), PL);
    if (ExpType == NULL)
      return;

    // ATTENTION: CHECK ERROR #8 !!!
    if (!CheckTypeEquivalence(RetType, ExpType)) {
      SemanticSwitch = false;
      printf("\033[31mError type 8 at Line %d: Type mismatched for "
             "return.\033[0m\n",
             node->firstchild->lineno);
    }
  } else if (node->childrenNum == 5) {
    assert(node->firstchild->SymbolIndex == AWHILE ||
           node->firstchild->SymbolIndex == AIF);
    Type *ExpType = ExpAnalysis(thirdchild(node), PL);
    if (ExpType == NULL)
      return;

    // ATTENTION: CHECK ERROR #7 !!!
    if (!IsTypeInt(ExpType)) {
      SemanticSwitch = false;
      printf("\033[31mError type 7 at Line %d: Type mismatched for operands(if "
             "and while condition should be int type).\033[0m\n",
             node->firstchild->lineno);
    }

    StmtAnalysis(fifthchild(node), RetType, PL);
  } else {
    assert(node->firstchild->SymbolIndex == AIF);
    Type *ExpType = ExpAnalysis(thirdchild(node), PL);
    if (ExpType == NULL)
      return;

    // ATTENTION: CHECK ERROR #7 !!!
    if (!IsTypeInt(ExpType)) {
      SemanticSwitch = false;
      printf("\033[31mError type 7 at Line %d: Type mismatched for operands(if "
             "and while condition should be int type).\033[0m\n",
             node->firstchild->lineno);
    }

    StmtAnalysis(fifthchild(node), RetType, PL);
    StmtAnalysis(seventhchild(node), RetType, PL);
  }
}

static void StmtListAnalysis(ParsingNode *node, Type *RetType, ParamList *PL) {
  assert(node->SymbolIndex == AStmtList);

  if (node->kind == Dummy)
    return;
  else {
    StmtAnalysis(node->firstchild, RetType, PL);
    StmtListAnalysis(secondchild(node), RetType, PL);
  }
}

static void CompStAnalysis(ParsingNode *node, Type *RetType, ParamList *PL) {
  assert(node->SymbolIndex == ACompSt);

  // PushPrevTable();

  DefListAnalysisInFunction(secondchild(node), PL);

  StmtListAnalysis(thirdchild(node), RetType, PL);

  // printf("check elem in CurrentSymbolTable\n");
  // CheckElemInTable(CurrentSymbolTable);

  // PopPrevTable();
}

static void ExtDefAnalysis(ParsingNode *node) {
  assert(node->SymbolIndex == AExtDef);

  Type *InheritType = SpecifierAnalysis(node->firstchild);

  if (node->childrenNum == 3) {
    if (secondchild(node)->SymbolIndex == AExtDecList) {
      if (InheritType == NULL)
        return;
      ExtDecListAnalysis(secondchild(node), InheritType);
    } else if (secondchild(node)->SymbolIndex == AFunDec) {
      ParamList *PL = FunDecAnalysis(secondchild(node), InheritType);
      CompStAnalysis(thirdchild(node), InheritType, PL);
    }
  }
}

static void ExtDefListAnalysis(ParsingNode *node) {
  assert(node->SymbolIndex == AExtDefList);

  if (node->kind != Dummy) {
    ExtDefAnalysis(node->firstchild);
    ExtDefListAnalysis(secondchild(node));
  } else
    return;
}

static void ProgramAnalysis(ParsingNode *node) {
  assert(node->SymbolIndex == AProgram);
  ExtDefListAnalysis(node->firstchild);
}

void SemanticAnalysis(ParsingNode *node) {
  assert(CurrentSymbolTable == RootSymbolTable);
  assert(CurrentStructTypeTable == RootStructTypeTable);

  InitTable();
  ProgramAnalysis(node);

  assert(CurrentSymbolTable == RootSymbolTable);
  assert(CurrentStructTypeTable == RootStructTypeTable);

  // printf("check elem in root table\n");
  // CheckElemInTable(CurrentSymbolTable);
}
