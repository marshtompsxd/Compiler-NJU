//
// Created by sunxudong on 12/11/17.
//
#include "../common.h"
#include "../semantic/list.h"
#include "../semantic/check.h"

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