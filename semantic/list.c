//
// Created by sunxudong on 12/11/17.
//

#include "symbol_table.h"
#include "InterCode.h"
#include <stdlib.h>

FieldList* FLTail(FieldList* FL)
{
    while(FL->tail!=NULL)
    {
        FL = FL->tail;
    }
    return FL;
}

void InsertItemIntoSymbolTable(SymbolTableEntry* item, SymbolTableHead* table)
{
    /* you can choose to insert at head but I don't like it...
    item->tail = table->head;
    table->head = item;
    */

    /*I prefer to insert at tail even though it is slower...
    */
    if(table->head == NULL)
    {
        item->tail = NULL;
        table->head = item;
    }
    else
    {
        SymbolTableEntry* SE;
        for(SE = table->head; SE->tail != NULL; SE = SE->tail);
        SE->tail = item;
        item->tail = NULL;
    }
}

void InsertItemIntoStructTypeTable(StructTypeTableEntry* item, StructTypeTableHead* table)
{
    /* you can choose to insert at head but I don't like it...
    item->tail = table->head;
    table->head = item;
    */

    /*I prefer to insert at tail even though it is slower...
    */
    if(table->head == NULL)
    {
        item->tail = NULL;
        table->head = item;
    }
    else
    {
        StructTypeTableEntry* STE;
        for(STE = table->head; STE->tail != NULL; STE = STE->tail);
        STE->tail = item;
        item->tail = NULL;
    }
}

Type* LookUpForStructTypeFromStructTypeTable(char* structname, StructTypeTableHead* table)
{
    StructTypeTableEntry* STE;
    for(STE = table->head; STE != NULL; STE = STE->tail)
    {
        if(strcmp(structname, STE->TP->structure.structname)==0)
        {
            return STE->TP;
        }
    }
    return NULL;
}

Type* LookUpForStructType(char* structname)
{
    int idx = struct_top;
    Type* type;
    if( (type = LookUpForStructTypeFromStructTypeTable(structname, CurrentStructTypeTable)) != NULL)
    {
        return type;
    }
    while(idx >= 0)
    {
        if((type = LookUpForStructTypeFromStructTypeTable(structname, StructTypeTableStack[idx])) != NULL)
            return type;
        idx--;
    }
    return NULL;
}

SymbolTableEntry* LookUpForVarDefFromSymbolTable(char* varname, SymbolTableHead* table)
{
    SymbolTableEntry* SE;
    for(SE = table->head; SE != NULL; SE = SE->tail)
    {
        if(SE->kind == VAR && strcmp(varname, SE->Variable.VariableName)==0)
        {
            return SE;
        }
    }
    return NULL;
}

SymbolTableEntry* LookUpForVarDef(char* varname)
{
    int idx = sym_top;
    SymbolTableEntry* SE;
    if( (SE = LookUpForVarDefFromSymbolTable(varname, CurrentSymbolTable)) != NULL)
    {
        return SE;
    }
    while(idx >= 0)
    {
        if((SE = LookUpForVarDefFromSymbolTable(varname, SymbolTableStack[idx])) != NULL)
            return SE;
        idx--;
    }
    return NULL;
}

SymbolTableEntry* LookUpForFunDefFromSymbolTable(char* funname, SymbolTableHead* table)
{
    SymbolTableEntry* SE;
    //printf("fun name is %s\n", funname);
    for(SE = table->head; SE != NULL; SE = SE->tail)
    {
        if(SE->kind == FUN && strcmp(funname, SE->Function.FunName)==0)
        {
            return SE;
        }
    }
    return NULL;
}

SymbolTableEntry* LookUpForFunDef(char* funname)
{
    SymbolTableEntry* SE;
    if( (SE = LookUpForFunDefFromSymbolTable(funname, RootSymbolTable)) != NULL)
        return SE;
    else return NULL;
}

SymbolTableEntry* LookUpForParam(char* varname, ParamList* PL)
{
    SymbolTableEntry* SE;
    for(SE = PL->head; SE!=NULL; SE = SE->tail)
    {
        if(strcmp(varname, SE->Variable.VariableName)==0)
        {
            return SE;
        }
    }
    return NULL;
}

Type* LookUpForField(char* fieldname, Type* TP)
{
    assert(TP->kind == STRUCTURE);

    FieldList* FL;
    for(FL = TP->structure.member; FL != NULL; FL = FL->tail)
    {
        if(strcmp(fieldname, FL->name) == 0)
        {
            return FL->type;
        }
    }
    return NULL;
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

void PushPrevTable()
{
    sym_top++;
    struct_top++;
    SymbolTableStack[sym_top] = CurrentSymbolTable;
    StructTypeTableStack[struct_top] = CurrentStructTypeTable;

    CurrentSymbolTable = (SymbolTableHead*)malloc(sizeof(SymbolTableHead));
    CurrentSymbolTable->head = NULL;
    CurrentStructTypeTable = (StructTypeTableHead*)malloc(sizeof(StructTypeTableHead));
    CurrentStructTypeTable->head = NULL;

}

void PopPrevTable()
{
    free(CurrentSymbolTable);
    free(CurrentStructTypeTable);
    CurrentSymbolTable = SymbolTableStack[sym_top];
    CurrentStructTypeTable = StructTypeTableStack[struct_top];
    sym_top--;
    struct_top--;
}

