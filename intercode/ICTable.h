//
// Created by sunxudong on 12/11/17.
//
#ifndef COMPILER_ICTABLE_H
#define COMPILER_ICTABLE_H

#include "InterCode.h"
#include "ParsingNode.h"

extern void InsertEntryIntoICVarTable(ICVarEntry* entry, ICVarTableHead* table);

extern void InsertEntryIntoICFunTable(ICFunEntry* entry, ICFunTableHead* table);

extern void GenerateICVarTable(SymbolTableHead* table);

extern void GenerateICFunTable(SymbolTableHead* table);

extern void CheckElemInICVarTable(ICVarTableHead* table);

extern void CheckElemInICFunTable(ICFunTableHead* table);

extern ICVarEntry* LookUpForICVarEntry(char* VariableName);

extern Operand* NewVOperand(int attr, int VIndex);

extern Operand* NewTOperand(int attr);

extern Operand* NewICOperand(int ICons);

extern Operand* NewFCOperand(float FCons);


#endif //COMPILER_ICTABLE_H
