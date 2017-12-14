//
// Created by sunxudong on 12/11/17.
//
#include <ParsingNode.h>
#include <symbol_table.h>
#include "../common.h"
#include "../semantic/list.h"
#include "../semantic/check.h"
#include "InterCode.h"

void CheckElemInICVarTable(ICVarTableHead* table)
{
    ICVarEntry* VE;
    printf("---------------------------------------------------\n");
    for(VE = table->head; VE != NULL; VE = VE->next)
    {

        printf("VAR : %s , index : %d, type : ", VE->VariableName, VE->VIndex);
        PrintType(VE->VariableType);
        printf("----------------------------------------------------\n");

    }
    printf("\n\n");
}

void CheckElemInICFunTable(ICFunTableHead* table)
{
    ICFunEntry* FE;
    printf("---------------------------------------------------\n");
    for(FE = table->head; FE != NULL; FE = FE->next)
    {

        printf("FUN : %s\n", FE->FunName);
        printf("----------------------------------------------------\n");

    }
    printf("\n\n");
}

static void InsertEntryIntoICVarTable(ICVarEntry* entry, ICVarTableHead* table)
{
    if(table->head == NULL)
    {
        entry->next = NULL;
        table->head = entry;
    }
    else
    {
        ICVarEntry* VE;
        for(VE = table->head; VE->next != NULL; VE = VE->next);
        VE->next = entry;
        entry->next = NULL;
    }
}

static void InsertEntryIntoICFunTable(ICFunEntry* entry, ICFunTableHead* table)
{
    if(table->head == NULL)
    {
        entry->next = NULL;
        table->head = entry;
    }
    else
    {
        ICFunEntry* FE;
        for(FE = table->head; FE->next != NULL; FE = FE->next);
        FE->next = entry;
        entry->next = NULL;
    }
}

void ProcessArrayType(Type* type)
{
    assert(type->kind == ARRAY);

    int dim = 0;
    Type* subarray = type;
    while (subarray->kind == ARRAY)
    {
        dim++;
        subarray = subarray->array.elem;
    }
    type->array.dim = dim;
    type->array.DimSize = (int*)malloc((unsigned)dim);
    int i = 0;
    for(subarray = type; subarray->kind == ARRAY; subarray = subarray->array.elem)
    {
        type->array.DimSize[i] = subarray->array.size;
        i++;
    }

}

void GenerateICVarTable(SymbolTableHead* table)
{
    SymbolTableEntry* SE;
    SymbolTableEntry* TE;
    for(SE = table->head; SE != NULL; SE = SE->tail)
    {
        if(SE->kind == VAR)
        {
            ICVarEntry* VE = (ICVarEntry*)malloc(sizeof(ICVarEntry));
            VE->VariableName = (char*)malloc(strlen(SE->Variable.VariableName));
            strcpy(VE->VariableName, SE->Variable.VariableName);
            VE->VariableType = SE->Variable.VariableType;

            if(VE->VariableType->kind == ARRAY)ProcessArrayType(VE->VariableType);

            VE->VIndex = ++VIndex;
            InsertEntryIntoICVarTable(VE, RootICVarTable);
        }
        else
        {
            if(strcmp(SE->Function.FunName, "read") == 0 || strcmp(SE->Function.FunName, "write") == 0)
                continue;
            SymbolTableEntry* PSE;
            for(PSE = SE->Function.PL->head; PSE!=NULL; PSE = PSE->tail)
            {
                ICVarEntry* VE = (ICVarEntry*)malloc(sizeof(ICVarEntry));
                VE->VariableName = (char*)malloc(strlen(PSE->Variable.VariableName));
                strcpy(VE->VariableName, PSE->Variable.VariableName);
                VE->VariableType = PSE->Variable.VariableType;
                VE->VIndex = ++VIndex;
                InsertEntryIntoICVarTable(VE, RootICVarTable);
            }
        }
    }
}

void GenerateICFunTable(SymbolTableHead* table)
{
    SymbolTableEntry* SE;
    for(SE = table->head; SE != NULL; SE = SE->tail)
    {
        if(SE->kind == FUN)
        {
            ICFunEntry* FE = (ICFunEntry*)malloc(sizeof(ICFunEntry));
            FE->FunName = (char*)malloc(strlen(SE->Function.FunName));
            strcpy(FE->FunName, SE->Function.FunName);
            InsertEntryIntoICFunTable(FE, RootICFunTable);
        }
    }
}

void PushEntryIntoArgList(ArgEntry* entry, ArgListHead* list)
{
    assert(entry != NULL);
    entry->next = list->head;
    list->head = entry;
}

ICVarEntry* LookUpForICVarEntry(char* VariableName)
{
    ICVarEntry* VE;
    for(VE = RootICVarTable->head;VE!=NULL; VE = VE->next)
    {
        if(strcmp(VariableName, VE->VariableName) == 0)return VE;
    }
    return NULL;
}

int NewLabelIndex()
{
    return ++LIndex;
}

Operand* NewVOperand(int attr, int VIndex)
{
    Operand* OP = (Operand*)malloc(sizeof(Operand));
    OP->kind = OVAR;
    OP->attr = attr;
    OP->VIndex = VIndex;
    return OP;
}

Operand* NewTOperand(int attr)
{
    Operand* OP = (Operand*)malloc(sizeof(Operand));
    OP->kind = OTEMP;
    OP->attr = attr;
    OP->TIndex = ++TIndex;
    return OP;
}

Operand* NewICOperand(int ICons)
{
    Operand* OP = (Operand*)malloc(sizeof(Operand));
    OP->kind = OICONS;
    OP->attr = OVALUE;
    OP->ICons = ICons;
    return OP;
}

Operand* NewFCOperand(float FCons)
{
    Operand* OP = (Operand*)malloc(sizeof(Operand));
    OP->kind = OFCONS;
    OP->attr = OVALUE;
    OP->FCons = FCons;
    return OP;
}

int arithmeticConvert(int arithmetic)
{
    switch (arithmetic)
    {
        case APLUS: return IADD;
        case AMINUS: return ISUB;
        case ASTAR: return IMUL;
        case ADIV: return IDIV;
        default: assert(0);
    }
}

Operand* GetLvalueIDOperand(ParsingNode* node)
{
    assert(skind(firstchild(node)) == AID);

    ICVarEntry* VE = LookUpForICVarEntry(firstchild(node)->IDname);
    assert(VE!=NULL);
    Operand* OP = NewVOperand(OVALUE, VE->VIndex);
    return OP;

}

void InsertEntryIntoInterCodeList(InterCodeEntry* entry, InterCodeListHead* list)
{
    assert(entry != NULL);
    if(list->head == NULL)
    {
        list->head = entry;
        entry->prev = entry->next = entry;
    }
    else
    {
        InterCodeEntry *ICEHead, *ICETail;
        ICEHead = list->head;
        ICETail = list->head->prev;
        ICEHead->prev = entry;
        ICETail->next = entry;
        entry->prev = ICETail;
        entry->next = ICEHead;
    }
}

void InsertInterCodeEntry(InterCodeEntry* entry)
{
    InsertEntryIntoInterCodeList(entry, RootInterCodeList);
}

void MergeInterCodeList(InterCodeListHead* sublist, InterCodeListHead* list)
{
    if(sublist->head == NULL)return;
    InterCodeEntry* ICEHead = sublist->head;
    InterCodeEntry* ICETail = ICEHead->prev;
    ICETail->next = NULL;
    InterCodeEntry* ICE = ICEHead;
    while(ICE!=NULL)
    {
        InterCodeEntry* NICE = ICE->next;
        InsertEntryIntoInterCodeList(ICE, list);
        ICE = NICE;
    }
    sublist->head = NULL;
}

InterCodeEntry* NewInterCodeEntryBINOP(int kind, Operand* result, Operand* op1, Operand* op2)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = kind;
    IC->BINOP.op1 = (Operand*)malloc(sizeof(Operand));
    IC->BINOP.op2 = (Operand*)malloc(sizeof(Operand));
    IC->BINOP.result = (Operand*)malloc(sizeof(Operand));

    memcpy(IC->BINOP.op1, op1, sizeof(Operand));
    memcpy(IC->BINOP.op2, op2, sizeof(Operand));
    memcpy(IC->BINOP.result, result, sizeof(Operand));
    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryASSIGN(Operand* left, Operand* right)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IASSIGN;
    IC->ASSIGN.left = (Operand*)malloc(sizeof(Operand));
    IC->ASSIGN.right = (Operand*)malloc(sizeof(Operand));

    memcpy(IC->ASSIGN.left, left, sizeof(Operand));
    memcpy(IC->ASSIGN.right, right, sizeof(Operand));
    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

static Cond* NewCond(Operand* op1, Operand* op2, int relop)
{
    Cond* CD = (Cond*)malloc(sizeof(Cond));

    CD->op1 = (Operand*)malloc(sizeof(Operand));
    CD->op2 = (Operand*)malloc(sizeof(Operand));

    memcpy(CD->op1, op1, sizeof(Operand));
    memcpy(CD->op2, op2, sizeof(Operand));
    CD->relop = relop;
    return CD;
}

InterCodeEntry* NewInterCodeEntryIFGT(Operand* op1, Operand* op2, int relop, int LIndex)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IIFGOTO;

    Cond* CD = NewCond(op1, op2, relop);
    IC->IFGT.condition = CD;
    IC->IFGT.LIndex = LIndex;
    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}


InterCodeEntry* NewInterCodeEntryGT(int LIndex)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IGOTO;

    IC->GT.LIndex = LIndex;
    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryLABELDEC(int LIndex)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = ILABEL;

    IC->LABELDEC.LIndex = LIndex;
    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryCALL(Operand* ret, char* funName)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = ICALL;

    IC->CALL.ret = (Operand*)malloc(sizeof(Operand));
    memcpy(IC->CALL.ret, ret, sizeof(Operand));
    IC->CALL.funName = (char*)malloc(sizeof(strlen(funName)));
    strcpy(IC->CALL.funName, funName);

    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryRET(Operand* ret)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IRETURN;

    IC->RET.ret = (Operand*)malloc(sizeof(Operand));
    memcpy(IC->CALL.ret, ret, sizeof(Operand));


    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryREAD(Operand* input)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IREAD;

    IC->READ.input = (Operand*)malloc(sizeof(Operand));
    memcpy(IC->READ.input, input, sizeof(Operand));


    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryWRITE(Operand* output)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IWRITE;

    IC->WRITE.output = (Operand*)malloc(sizeof(Operand));
    memcpy(IC->WRITE.output, output, sizeof(Operand));


    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryARG(Operand* arg)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IARG;

    IC->ARG.argument = (Operand*)malloc(sizeof(Operand));
    memcpy(IC->ARG.argument, arg, sizeof(Operand));


    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryDEC(Operand* address, int size)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IDEC;

    IC->DEC.address = (Operand*)malloc(sizeof(Operand));
    memcpy(IC->DEC.address, address, sizeof(Operand));
    IC->DEC.size = size;

    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryFUN(char* funName)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IFUNCTION;

    IC->FUN.funName = (char*)malloc(sizeof(funName));
    strcpy(IC->FUN.funName, funName);

    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}

InterCodeEntry* NewInterCodeEntryPARAM(Operand* parameter)
{
    InterCodeEntry* ICE = (InterCodeEntry*)malloc(sizeof(InterCodeEntry));
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));

    IC->kind = IPARAM;

    IC->PARAM.parameter = (Operand*)malloc(sizeof(Operand));
    memcpy(IC->PARAM.parameter, parameter, sizeof(Operand));


    ICE->IC = IC;
    ICE->prev = ICE->next = NULL;
    return ICE;
}


ArgEntry* NewArgEntry(Operand* op)
{
    ArgEntry* AE = (ArgEntry*)malloc(sizeof(ArgEntry));
    AE->arg = (Operand*)malloc(sizeof(Operand));
    memcpy(AE->arg, op, sizeof(Operand));
    AE->next = NULL;

    return AE;
}


static void PrintOperand(Operand* op)
{
    if(op->attr == OADDR)printf("*");
    else if(op->attr == OREF)printf("&");
    if(op->kind == OVAR)
    {
        printf("v%d", op->VIndex);
    }
    else if(op->kind == OTEMP)
    {
        printf("t%d", op->TIndex);
    }
    else if(op->kind == OICONS)
    {
        printf("#%d", op->ICons);
    }
    else if(op->kind == OFCONS)
    {
        printf("#%f", op->FCons);
    }
    else assert(0);
}

static void PrintCond(Cond* condition)
{
    printf("IF ");
    PrintOperand(condition->op1);
    printf(" %s ", relopTable[condition->relop]);
    PrintOperand(condition->op2);

}

static void PrintInterCodeEntry(InterCodeEntry* ICE)
{
    InterCode* code = ICE->IC;
    switch (code->kind)
    {
        case IASSIGN:{
            PrintOperand(code->ASSIGN.left);
            printf(" := ");
            PrintOperand(code->ASSIGN.right);
            break;
        }
        case IADD:{
            PrintOperand(code->BINOP.result);printf(" := ");
            PrintOperand(code->BINOP.op1);printf(" + ");PrintOperand(code->BINOP.op2);
            break;
        }
        case ISUB:{
            PrintOperand(code->BINOP.result);printf(" := ");
            PrintOperand(code->BINOP.op1);printf(" - ");PrintOperand(code->BINOP.op2);
            break;
        }
        case IMUL:{
            PrintOperand(code->BINOP.result);printf(" := ");
            PrintOperand(code->BINOP.op1);printf(" * ");PrintOperand(code->BINOP.op2);
            break;
        }
        case IDIV:{
            PrintOperand(code->BINOP.result);printf(" := ");
            PrintOperand(code->BINOP.op1);printf(" / ");PrintOperand(code->BINOP.op2);
            break;
        }
        case ILABEL:{
            printf("LABEL L%d :",code->LABELDEC.LIndex);
            break;
        }
        case IGOTO:{
            printf("GOTO L%d",code->LABELDEC.LIndex);
            break;
        }
        case IIFGOTO:{
            PrintCond(code->IFGT.condition);
            printf(" GOTO L%d", code->IFGT.LIndex);
            break;
        }
        case ICALL:{
            PrintOperand(code->CALL.ret);
            printf(" := CALL %s", code->CALL.funName);
            break;
        }
        case IRETURN:{
            printf("RETURN ");
            PrintOperand(code->RET.ret);
            break;
        }
        case IREAD:{
            printf("READ ");
            PrintOperand(code->READ.input);
            break;
        }
        case IWRITE:{
            printf("WRITE ");
            PrintOperand(code->WRITE.output);
            break;
        }
        case IARG:{
            printf("ARG ");
            PrintOperand(code->ARG.argument);
            break;
        }
        case IDEC: {
            printf("DEC ");
            PrintOperand(code->DEC.address);
            printf(" %d", code->DEC.size);
            break;
        }
        case IPARAM:{
            printf("PARAM ");
            PrintOperand(code->PARAM.parameter);
            break;
        }
        case IFUNCTION:{
            printf("FUNCTION %s : ", code->FUN.funName);
            break;
        }
        default:assert(0);
    }

    printf("\n");
}

void PrintInterCodeList(InterCodeListHead* list)
{
    InterCodeEntry* ICE;
    PrintInterCodeEntry(list->head);
    for(ICE = list->head->next; ICE!=list->head; ICE = ICE->next)
    {
        PrintInterCodeEntry(ICE);
    }
}







