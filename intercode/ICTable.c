//
// Created by sunxudong on 12/11/17.
//
#include <ParsingNode.h>
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

void InsertEntryIntoICVarTable(ICVarEntry* entry, ICVarTableHead* table)
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

void InsertEntryIntoICFunTable(ICFunEntry* entry, ICFunTableHead* table)
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
            VE->VIndex = ++VIndex;
            InsertEntryIntoICVarTable(VE, RootICVarTable);
        }
        else
        {
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

ICVarEntry* LookUpForICVarEntry(char* VariableName)
{
    ICVarEntry* VE;
    for(VE = RootICVarTable->head;VE!=NULL; VE = VE->next)
    {
        if(strcmp(VariableName, VE->VariableName) == 0)return VE;
    }
    return NULL;
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

InterCode* NewInterCodeBINOP(int kind, Operand* op1, Operand* op2, Operand* result)
{
    InterCode* IC = (InterCode*)malloc(sizeof(InterCode));
    IC->kind = kind;
    memcpy(IC->BINOP.op1, op1, sizeof(Operand));
    memcpy(IC->BINOP.op2, op2, sizeof(Operand));
    memcpy(IC->BINOP.result, result, sizeof(Operand));
}
